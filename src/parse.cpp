
#include <cpptoml.h>

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
        return Rcpp::wrap(s);
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


// [[Rcpp::export]]
Rcpp::List tomlparse(std::string filename, bool verbose=false) {

    cpptoml::table g = cpptoml::parse_file(filename);
    if (verbose) {
        Rcpp::Rcout << "<print method>\n" 
                    << g 
                    << "</print method>\n" 
                    << std::endl;
    }

    Rcpp::StretchyList sl;
    for (auto & p : g) {

        if (p.second->is_table_array()) {
            Rcpp::Rcout << "TableArray: " << p.first << std::endl;
            sl.push_front(p.first); 
            auto ga = std::dynamic_pointer_cast<cpptoml::table_array>(p.second);
            //ga->print(stream, depth, p.first);
        } else if (p.second->is_table()) {
            Rcpp::Rcout << "Table: " << p.first << std::endl;
            sl.push_front(p.first); 
        } else if (p.second->is_array()) {
            Rcpp::Rcout << "Array: " << p.first << std::endl;
            sl.push_front(p.first); 
        } else if (p.second->is_value()) {
            if (verbose) {
                Rcpp::Rcout << "Value: " << p.first << "\n  :";
                printValue(std::cout, p.second);
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

