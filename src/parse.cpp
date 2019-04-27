// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
//  RcppTOML -- Rcpp bindings to TOML via cpptoml
//
//  Copyright (C) 2015 - 2018  Dirk Eddelbuettel
//
//  This file is part of RcppTOML
//
//  RcppTOML is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 2 of the License, or
//  (at your option) any later version.
//
//  RcppTOML is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with RcppTOML.  If not, see <http://www.gnu.org/licenses/>.

#include <cpptoml.h>
#include <unistd.h>

// include for the includize stream preprocessor
// but don't use codecvt (g++-5 or later)
#define INCLUDIZE_NO_CODECVT 1
#include <toml.hpp>

// use the new vector which will be default by late 2017
#define RCPP_NEW_DATE_DATETIME_VECTORS 1
#include <Rcpp.h>

// this function is borrowed with credits from cpptoml :)
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
    } else if (auto v = base->as<cpptoml::offset_datetime>()) {
        o << "{\"type\":\"offset_datetime\",\"value\":\"" << v->get() << "\"}";
    } else if (auto v = base->as<cpptoml::local_datetime>()) {
        o << "{\"type\":\"local_datetime\",\"value\":\"" << v->get() << "\"}";
    } else if (auto v = base->as<cpptoml::local_date>()) {
        o << "{\"type\":\"local_date\",\"value\":\"" << v->get() << "\"}";
    } else if (auto v = base->as<bool>()) {
        o << "{\"type\":\"bool\",\"value\":\""
        //v->print(o);
          << v.get()
          << "\"}";
    }
}

// cf 'man timegm' for the workaround on non-Linux systems
inline time_t local_timegm(struct tm *tm) {
#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    // and there may be more OSs that have timegm() ...
    return timegm(tm);
#elif defined(__MINGW32__) || defined(__MINGW64__)
    return Rcpp::mktime00(*tm);  // Rcpp exports a copy of the R-internal function
#else
    char *tz = getenv("TZ");
    if (tz) tz = strdup(tz);
    setenv("TZ", "", 1);
    tzset();
    time_t ret = mktime(tm);
    if (tz) {
        setenv("TZ", tz, 1);
        free(tz);
    } else
        unsetenv("TZ");
    tzset();
    return ret;
#endif
}

SEXP getValue(const std::shared_ptr<cpptoml::base>& base, bool escape=true) {
    if (auto v = base->as<std::string>()) {
        std::string s(v->get());
        if (escape) {
            s = escapeString(s);
        }
        Rcpp::String se(s, CE_UTF8);
        return Rcpp::wrap(se);
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
    } else if (auto v = base->as<cpptoml::local_date>()) {
        cpptoml::local_date s(v->get());
        Rcpp::Date d(s.year,s.month,s.day);
        return Rcpp::wrap(d);
    } else if (auto v = base->as<cpptoml::local_datetime>()) {
        cpptoml::local_datetime s(v->get());
        struct tm tm;
        tm.tm_year = s.year - 1900;
        tm.tm_mon  = s.month - 1;
        tm.tm_mday = s.day;
        tm.tm_hour = s.hour;
        tm.tm_min  = s.minute;
        tm.tm_sec  = s.second;
        time_t tt = local_timegm(&tm);
        //tt = tt - s.hour_offset*60*60 - s.minute_offset*60;
        Rcpp::DatetimeVector dt(1, "UTC");
        dt[0] = tt + s.microsecond * 1.0e-6;
        return Rcpp::wrap(dt);
    } else if (auto v = base->as<cpptoml::offset_datetime>()) {
        cpptoml::offset_datetime s(v->get());
        struct tm tm;
        tm.tm_year = s.year - 1900;
        tm.tm_mon  = s.month - 1;
        tm.tm_mday = s.day;
        tm.tm_hour = s.hour;
        tm.tm_min  = s.minute;
        tm.tm_sec  = s.second;
        time_t tt = local_timegm(&tm);
        tt = tt - s.hour_offset*60*60 - s.minute_offset*60;
        Rcpp::DatetimeVector dt(1, "UTC");
        dt[0] =  tt + s.microsecond * 1.0e-6;
        return Rcpp::wrap(dt);
    } else if (auto v = base->as<cpptoml::local_time>()) {
        cpptoml::local_time t(v->get());
        char txt[32];
        if (t.microsecond != 0) {
            snprintf(txt, 31, "%02d:%02d:%02d.%d",
                     t.hour, t.minute, t.second, t.microsecond);
        } else {
            snprintf(txt, 31, "%02d:%02d:%02d",
                     t.hour, t.minute, t.second);
        }
        std::string s(txt);
        return Rcpp::wrap(s);
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
    if (ll.length() == 0) return R_NilValue;
    Rcpp::List::iterator it = ll.begin();
    switch(TYPEOF(*it)) {
        case REALSXP: {
            Rcpp::NumericVector v(ll.begin(), ll.end());
            Rcpp::RObject ro = ll[0];
            if (ro.hasAttribute("class")) {
                Rcpp::CharacterVector cv = ro.attr("class");
                if ((cv.size() == 1) && std::string(cv[0]) == "Date") {
                    Rcpp::DateVector dv(v);
                    return dv;
                }
                if ((cv.size() == 2) && std::string(cv[1]) == "POSIXt") {
                    Rcpp::DatetimeVector dtv(v);
                    return dtv;
                }
            }
            return v;
            break;              // not reached ...
        }
        case INTSXP: {
            Rcpp::IntegerVector v(ll.begin(), ll.end());
            return v;
            break;              // not reached ...
        }
        case LGLSXP: {
            Rcpp::LogicalVector v(ll.begin(), ll.end());
            return v;
            break;              // not reached ...
        }
        case STRSXP: {              // minor code smell that this is different :-/
            int n = ll.size();
            Rcpp::CharacterVector v(n);
            for (int i=0; i<n; i++) {
                std::string s = Rcpp::as<std::string>(ll[i]);
                Rcpp::String se(s, CE_UTF8);
                v[i] = se;
            }
            return v;
            break;              // not reached ...
        }
    }
    return ll;
}

SEXP getArray(const cpptoml::array& arr, bool escape=true) {
    Rcpp::StretchyList sl;
    bool nonested = true;       // ie no embedded array
    auto it = arr.get().begin();
    while (it != arr.get().end()) {
        if ((*it)->is_array()) {
            sl.push_back(getArray(*(*it)->as_array(), escape));
            nonested = false;
        } else {
            sl.push_back(getValue(*it, escape));
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


SEXP getTable(const std::shared_ptr<cpptoml::table>& t, bool verbose=false, bool escape=true) {
    Rcpp::StretchyList sl;
    for (auto & p : *t) {
        if (p.second->is_table()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::table>(p.second);
            if (verbose) Rcpp::Rcout << "Table: " << p.first << std::endl;
            sl.push_back(Rcpp::Named(p.first) = getTable(ga, verbose, escape));
        } else if (p.second->is_array()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::array>(p.second);
            if (verbose) {
                Rcpp::Rcout << "Array: " << p.first << std::endl;
                printArray(Rcpp::Rcout, *ga);
            }
            sl.push_back(Rcpp::Named(p.first) = getArray(*ga, escape));
        } else if (p.second->is_value()) {
            if (verbose) {
                Rcpp::Rcout << "Value: " << p.first << "\n  :";
                printValue(Rcpp::Rcout, p.second);
                Rcpp::Rcout << std::endl;
            }
            sl.push_back(Rcpp::Named(p.first) = getValue(p.second, escape));
        } else if (p.second->is_table_array()) {
            if (verbose) Rcpp::Rcout << "TableArray: " << p.first << std::endl;
            Rcpp::StretchyList l;
            auto arr = t->get_table_array(p.first)->get();
            auto ait = arr.begin();
            while (ait != arr.end()) {
                auto ta = std::dynamic_pointer_cast<cpptoml::table>(*ait);
                l.push_back (getTable(ta, verbose, escape));
                ++ait;
            }
            sl.push_back(Rcpp::Named(p.first) = Rcpp::as<Rcpp::List>(l));
        } else {
            if (verbose) Rcpp::Rcout << "Other: " << p.first << std::endl;
            sl.push_back(p.first);
        }
    }
    return Rcpp::as<Rcpp::List>(sl);
}


// [[Rcpp::export]]
Rcpp::List tomlparseImpl(const std::string input,
                         bool verbose=false,
                         bool fromfile=true,
                         bool includize=false,
                         bool escape=true) {

    if (fromfile && access(input.c_str(), R_OK)) {
        Rcpp::stop("Cannot read given file '" + input + "'.");
    }

    std::shared_ptr<cpptoml::table> g;

    if (fromfile) {
        if (includize) {
            includize::toml_preprocessor pp(input.c_str());
            cpptoml::parser included_parser(pp);
            g = included_parser.parse();
        } else {
            g = cpptoml::parse_file(input.c_str());
        }
    } else {
        std::stringstream strstream(input);
        cpptoml::parser p(strstream);
        g = p.parse();
    }

    if (verbose) {
        Rcpp::Rcout << "<default print method>\n"
                    << (*g)
                    << "</default print method>\n"
                    << std::endl;
    }

    Rcpp::StretchyList sl;
    for (auto & p : (*g)) {

        if (p.second->is_table_array()) {
            if (verbose) Rcpp::Rcout << "TableArray: " << p.first << std::endl;
            //auto ga = std::dynamic_pointer_cast<cpptoml::table_array>(p.second);
            Rcpp::StretchyList l;
            auto arr = g->get_table_array(p.first)->get();
            auto ait = arr.begin();
            while (ait != arr.end()) {
                auto ta = std::dynamic_pointer_cast<cpptoml::table>(*ait);
                l.push_back (getTable(ta, verbose, escape));
                ++ait;
            }
            sl.push_back(Rcpp::Named(p.first) = Rcpp::as<Rcpp::List>(l));

        } else if (p.second->is_table()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::table>(p.second);
            if (verbose) Rcpp::Rcout << "Table: " << p.first << std::endl;
            sl.push_back(Rcpp::Named(p.first) = getTable(ga, verbose, escape));

        } else if (p.second->is_array()) {
            auto ga = std::dynamic_pointer_cast<cpptoml::array>(p.second);
            if (verbose) Rcpp::Rcout << "Array: " << p.first << std::endl;
            sl.push_back(Rcpp::Named(p.first) = getArray(*ga, escape));

        } else if (p.second->is_value()) {
            if (verbose) {
                Rcpp::Rcout << "Value: " << p.first << "\n  :";
                printValue(Rcpp::Rcout, p.second);
                Rcpp::Rcout << std::endl;
            }
            sl.push_back(Rcpp::Named(p.first) = getValue(p.second, escape));
        } else {
            if (verbose) Rcpp::Rcout << "Other: " << p.first << std::endl;
            sl.push_front(p.first);
        }
    }

    return Rcpp::as<Rcpp::List>(sl);
}
