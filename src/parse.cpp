
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

// [[Rcpp::export]]
Rcpp::List tomlparse(std::string filename) {

    cpptoml::table g = cpptoml::parse_file(filename);
    Rcpp::Rcout << "<print method>\n" 
                << g 
                << "</print method>\n" 
                << std::endl;

    Rcpp::StretchyList sl;

    //for (cpptoml::table::iterator it = g.begin(); it != g.end(); it++) {
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
            //std::shared_ptr<cpptoml::base> bp = p.second;
            Rcpp::Rcout << "Value: " << p.first 
                        << "\n  :";
            printValue(std::cout, p.second);
            Rcpp::Rcout << std::endl;
            sl.push_front(p.first); 
            
        } else {
            Rcpp::Rcout << "Other: " << p.first << std::endl;
            sl.push_front(p.first); 
        }
        //     else
        //     {
        //         stream << std::string(depth, '\t') << p.first << " = ";
        //         if (p.second->is_table())
        //         {
        //             auto g = static_cast<table*>(p.second.get());
        //             stream << '\n';
        //             g->print(stream, depth + 1);
        //         }
        //         else
        //         {
        //             p.second->print(stream);
        //             stream << '\n';
        //         }
        //     }


    }
    
    return Rcpp::as<Rcpp::List>(sl);
}

