//  RcppTomlPlusPlus -- Rcpp bindings to TOML via cpptomlplusplus
//                      (based on earlier work in RcppTOML using cpptoml)
//
//  Copyright (C) 2015 - 2023  Dirk Eddelbuettel
//
//  This file is part of RcppTomlPlusPlus
//
//  RcppTomlPlusPlus is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 2 of the License, or
//  (at your option) any later version.
//
//  RcppTomlPlusPlus is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with RcppTomlPlusPlus.  If not, see <http://www.gnu.org/licenses/>.

void visitTable(const toml::table& tbl, const std::string& ind);
void visitArray(const toml::array& arr, const std::string& ind);
SEXP getTable(const toml::table& tbl, bool escape);
SEXP getArray(const toml::array& array, bool escape);
SEXP getValue(const toml::node& node, bool escape);

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

// this function is borrowed with love and full credits from cpptoml :)
inline std::string escapeString(const std::string& str) {
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

// also used in RcppTOML
inline SEXP collapsedList(Rcpp::List ll) {
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
