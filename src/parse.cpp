
#include <cpptoml.h>
#include <unistd.h>
#include <Rcpp.h>

std::string escapeString(const std::string& str) {
    std::string res;
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it == '\\')
            res += "\\\\";
        else if (*it == '"')
            res += "\\\"";
        else if (*it == '\n')
            res += "\\n";
        else
            res += *it;
    }
    return res;
}

void printValue(std::ostream& o, const std::shared_ptr<cpptoml::base>& base) {
    if (auto v = base->as<std::string>()) {
        o << "{\"type\":\"string\",\"value\":\"" << escapeString(v->get())
          << "\"}";
    } else if (auto v = base->as<int64_t>()) {
        o << "{\"type\":\"integer\",\"value\":\"" << v->get() << "\"}";
    } else if (auto v = base->as<double>()) {
        o << "{\"type\":\"float\",\"value\":\"" << v->get() << "\"}";
    } else if (auto v = base->as<cpptoml::datetime>()) {
        o << "{\"type\":\"datetime\",\"value\":\"" << v->get() << "\"}";
    } else if (auto v = base->as<bool>()) {
        o << "{\"type\":\"bool\",\"value\":\"";
        v->print(o);
        o << "\"}";
    }
}

SEXP getValue(const std::shared_ptr<cpptoml::base>& base) {
    if (auto v = base->as<std::string>()) {
        std::string s(escapeString(v->get()));
        return Rcpp::wrap(s);
    } else if (auto v = base->as<int64_t>()) {
        std::int64_t s(v->get());
        int t = static_cast<int>(s); // we need int for wrap to work
        return Rcpp::wrap(t);
    } else if (auto v = base->as<double>()) {
        double s(v->get());
        return Rcpp::wrap(s);
    } else if (auto v = base->as<bool>()) {
        bool s(v->get());
        return Rcpp::wrap(s);
    } else if (auto v = base->as<cpptoml::datetime>()) {
        cpptoml::datetime s(v->get());
        struct tm tm;
        tm.tm_year = s.year - 1900;
        tm.tm_mon  = s.month - 1;
        tm.tm_mday = s.day;
        tm.tm_hour = s.hour;
        tm.tm_min  = s.minute;
        tm.tm_sec  = s.second;
        time_t tt = mktime(&tm);
        Rcpp::Datetime r(tt + s.microsecond * 1.0e-6);
        return Rcpp::wrap(r);
    } else {
        Rcpp::warning("Unparsed value, returning null");
        return R_NilValue;
    }
}

void printArray(std::ostream& o, cpptoml::array& arr) {
    o << "{\"type\":\"array\",\"value\":[";
    auto it = arr.get().begin();
    while (it != arr.get().end()) {
        if ((*it)->is_array())
            printArray(o, *(*it)->as_array());
        else
            printValue(o, *it);
        
        if (++it != arr.get().end())
            o << ", ";
    }
    o << "]}";
}

SEXP collapsedList(Rcpp::List ll) {
    Rcpp::List::iterator it = ll.begin(); 
    switch(TYPEOF(*it)) {
        case REALSXP: {
            Rcpp::NumericVector v(ll.begin(), ll.end());
            return v;
            break;              // not reached ...
        }
        case INTSXP: {
            Rcpp::IntegerVector v(ll.begin(), ll.end());
            return v;
            break;              // not reached ...
        }
        case STRSXP: {              // minor code smell that this is different :-/
            int n = ll.size();
            Rcpp::CharacterVector v(n);
            for (int i=0; i<n; i++) {
                std::string s = Rcpp::as<std::string>(ll[i]);
                v[i] = s;
            }
            return v;
            break;              // not reached ...
        }
    }
    return ll;
}

SEXP getArray(cpptoml::array& arr) {
    Rcpp::StretchyList sl;
    bool nonested = true;       // ie no embedded array
    auto it = arr.get().begin();
    while (it != arr.get().end()) {
        if ((*it)->is_array()) {
            sl.push_back(getArray(*(*it)->as_array())); 
            nonested = false;
        } else {
            sl.push_back(getValue(*it));
            nonested = true;
        }
        it++;
    } 
    if (nonested) {
        return collapsedList(Rcpp::as<Rcpp::List>(sl));
    } else {
        return Rcpp::as<Rcpp::List>(sl);
    }
}


SEXP getTable(const std::shared_ptr<cpptoml::table>& t, bool verbose=false) {
    Rcpp::StretchyList sl;
    for (auto & p : *t) {
        // if (p.second->is_table_array()) {
        //     if (verbose) Rcpp::Rcout << "TableArray: " << p.first << "..." << std::endl;
        //     Rcpp::Rcout << "]" << std::endl;
        // } else 
        if (p.second->is_table()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::table>(p.second);
            if (verbose) Rcpp::Rcout << "Table: " << p.first << std::endl;
            sl.push_front(Rcpp::Named(p.first) = getTable(ga, verbose));
        } else if (p.second->is_array()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::array>(p.second);
            if (verbose) {
                Rcpp::Rcout << "Array: " << p.first << std::endl;
                printArray(Rcpp::Rcout, *ga);
            }
            sl.push_front(Rcpp::Named(p.first) = getArray(*ga)); 
        } else if (p.second->is_value()) {
            if (verbose) {
                Rcpp::Rcout << "Value: " << p.first << "\n  :";
                printValue(Rcpp::Rcout, p.second);
                Rcpp::Rcout << std::endl;
            }
            sl.push_front(Rcpp::Named(p.first) = getValue(p.second)); 
            
        } else {
            Rcpp::Rcout << "Other: " << p.first << std::endl;
            sl.push_front(p.first); 
        }
    }
    return Rcpp::as<Rcpp::List>(sl);
}


// [[Rcpp::export]]
Rcpp::List tomlparse(std::string filename, bool verbose=false) {

    if (access(filename.c_str(), R_OK)) {
        Rcpp::stop("Cannot read given file '" + filename + "'.");
    }
            
    cpptoml::table g = cpptoml::parse_file(filename);

    if (verbose) {
        Rcpp::Rcout << "<default print method>\n" 
                    << g 
                    << "</default print method>\n" 
                    << std::endl;
    }

    Rcpp::StretchyList sl;
    for (auto & p : g) {

        if (p.second->is_table_array()) {
            if (verbose) Rcpp::Rcout << "TableArray: " << p.first << std::endl;
            //auto ga = std::dynamic_pointer_cast<cpptoml::table_array>(p.second);
            auto arr = g.get_table_array(p.first)->get();
            auto ait = arr.begin();
            while (ait != arr.end()) {
                auto ta = std::dynamic_pointer_cast<cpptoml::table>(*ait);
                sl.push_front (Rcpp::Named(p.first) = getTable(ta, verbose));
                ++ait;
            }

        } else if (p.second->is_table()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::table>(p.second);
            if (verbose) Rcpp::Rcout << "Table: " << p.first << std::endl;
            sl.push_front(Rcpp::Named(p.first) = getTable(ga, verbose));

        } else if (p.second->is_array()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::array>(p.second);
            if (verbose) Rcpp::Rcout << "Array: " << p.first << std::endl;
            sl.push_front(Rcpp::Named(p.first) = getArray(*ga)); 

        } else if (p.second->is_value()) {
            if (verbose) {
                Rcpp::Rcout << "Value: " << p.first << "\n  :";
                printValue(Rcpp::Rcout, p.second);
                Rcpp::Rcout << std::endl;
            }
            sl.push_front(Rcpp::Named(p.first) = getValue(p.second)); 
            
        } else {
            Rcpp::Rcout << "Other: " << p.first << std::endl;
            sl.push_front(p.first); 
        }
    }
    
    return Rcpp::as<Rcpp::List>(sl);
}
