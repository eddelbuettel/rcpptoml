## RcppTOML [![Build Status](https://travis-ci.org/eddelbuettel/rcpptoml.png)](https://travis-ci.org/eddelbuettel/rcpptoml) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html)

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

### Status

Pretty feaature-complete, see the unit tests.

Does not work on Windows for R as the `g++-4.6.2` compiler in Rtools is way
too old for the C++11 used by [cpptoml](https://github.com/skystrife/cpptoml).

### Author

Dirk Eddelbuettel

### License

GPL (>= 2)


