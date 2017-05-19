## RcppTOML [![Build Status](https://travis-ci.org/eddelbuettel/rcpptoml.svg)](https://travis-ci.org/eddelbuettel/rcpptoml) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html) [![CRAN](http://www.r-pkg.org/badges/version/RcppTOML)](https://cran.r-project.org/package=RcppTOML) [![Downloads](http://cranlogs.r-pkg.org/badges/RcppTOML?color=brightgreen)](http://www.r-pkg.org/pkg/RcppTOML)

Rcpp bindings for [TOML](https://github.com/toml-lang/toml)

### What is TOML?

[TOML](https://github.com/toml-lang/toml) is a configuration file grammar for
humans. It is easier to read and edit than the alternatives yet arguably more
useful as it is strongly typed: values come back as integer, double,
(multiline-) character (strings), boolean or Datetime. Moreover, complex
nesting and arrays are supported as well.

This package uses the C++11 implementation written by Chase Geigle in
[cpptoml](https://github.com/skystrife/cpptoml) to implement a parser used by
R.

### Example

Consider the following [TOML](https://github.com/toml-lang/toml) input example input:

```toml
# This is a TOML document.

title = "TOML Example"

[owner]
name = "Tom Preston-Werner"
dob = 1979-05-27T07:32:00-08:00 # First class dates

[database]
server = "192.168.1.1"
ports = [ 8001, 8001, 8002 ]
connection_max = 5000
enabled = true

[servers]

  # Indentation (tabs and/or spaces) is allowed but not required
  [servers.alpha]
  ip = "10.0.0.1"
  dc = "eqdc10"

  [servers.beta]
  ip = "10.0.0.2"
  dc = "eqdc10"

[clients]
data = [ ["gamma", "delta"], [1, 2] ]

# Line breaks are OK when inside arrays
hosts = [
  "alpha",
  "omega"
]
```

Once parsed, note how R has properly typed input:

```r
R> library(RcppTOML)
R> parseTOML("inst/toml/example.toml")
List of 5
 $ clients :List of 2
  ..$ data :List of 2
  .. ..$ : chr [1:2] "gamma" "delta"
  .. ..$ : int [1:2] 1 2
  ..$ hosts: chr [1:2] "alpha" "omega"
 $ database:List of 4
  ..$ connection_max: int 5000
  ..$ enabled       : logi TRUE
  ..$ ports         : int [1:3] 8001 8001 8002
  ..$ server        : chr "192.168.1.1"
 $ owner   :List of 2
  ..$ dob : POSIXct[1:1], format: "1979-05-27 15:32:00"
  ..$ name: chr "Tom Preston-Werner"
 $ servers :List of 2
  ..$ alpha:List of 2
  .. ..$ dc: chr "eqdc10"
  .. ..$ ip: chr "10.0.0.1"
  ..$ beta :List of 2
  .. ..$ dc: chr "eqdc10"
  .. ..$ ip: chr "10.0.0.2"
 $ title   : chr "TOML Example"
R> 
```

See the other examples and the [upstream documentation](https://github.com/toml-lang/toml) for more.
Also note that most decent editors have proper [TOML](https://github.com/toml-lang/toml) support
which makes editing and previewing a breeze:

![](https://raw.githubusercontent.com/eddelbuettel/rcpptoml/master/local/emacsAndTOML.png)

### Installation

The package is on [CRAN](https://cran.r-project.org) and can be installed
from every mirror via

```{.r}
install.packages("RcppTOML")
```

Development releases may be provided by the
[ghrr](http://ghrr.github.io/drat) repository which can accessed via

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

### Author

Dirk Eddelbuettel

### License

GPL (>= 2)


