## RcppTOML [![Build Status](https://travis-ci.org/eddelbuettel/rcpptoml.svg)](https://travis-ci.org/eddelbuettel/rcpptoml) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html) [![CRAN](http://www.r-pkg.org/badges/version/RcppTOML)](http://cran.rstudio.com/package=RcppTOML) [![Downloads](http://cranlogs.r-pkg.org/badges/RcppTOML?color=brightgreen)](http://www.r-pkg.org/pkg/RcppTOML)

Rcpp bindings for [TOML](https://github.com/toml-lang/toml)

### What is TOML?

[TOML](https://github.com/toml-lang/toml) is a configuration file grammar for
humans. It is easier to read and edit than the alternatives yet arguably more
useful as it is stronly types: values come back as integer, double,
(multiline-) character (strings), boolean or Datetime. Moreover, complex
nesting and arrays are supported as well.

This package uses the C++11 implementation written by Chase Geigle in
[cpptoml](https://github.com/skystrife/cpptoml) to implement a parser used by
R.

### Installation

The package is now on [CRAN](http://cran.r-project.org) and can be installed
from every mirror via

```{.r}
install.packages("RcppTOML")
```

Development releases will continue to be provided by the
[ghrr](http://ghrr.github.io/drat) repository which can accessed using via

```{.r}
## if needed, first do:  install.packages("drat")
drat::addRepo("ghrr")
```

### Status

Feature-complete with
[TOML v0.4.0](https://github.com/toml-lang/toml/blob/master/versions/en/toml-v0.4.0.md),
see the [tests/](https://github.com/eddelbuettel/rcpptoml/tree/master/tests)
directory.  It parses everything that the underlying 
[cpptoml](https://github.com/skystrife/cpptoml) parses with the same (sole)
exception of unicode escape characters in strings.

It does not work on Windows for R as the `g++-4.6.2` compiler in Rtools is way
too old for the C++11 used by [cpptoml](https://github.com/skystrife/cpptoml).

### Author

Dirk Eddelbuettel

### License

GPL (>= 2)


