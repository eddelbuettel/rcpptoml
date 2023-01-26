## RcppTOML: Rcpp bindings for [TOML](https://toml.io/en/)

[![CI](https://github.com/eddelbuettel/rcpptoml/workflows/ci/badge.svg)](https://github.com/eddelbuettel/rcpptoml/actions?query=workflow%3Aci)
[![License](https://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](https://www.gnu.org/licenses/gpl-2.0.html)
[![CRAN](https://www.r-pkg.org/badges/version/RcppTOML)](https://cran.r-project.org/package=RcppTOML)
[![Dependencies](https://tinyverse.netlify.com/badge/RcppTOML)](https://cran.r-project.org/package=RcppTOML)
[![Downloads](https://cranlogs.r-pkg.org/badges/RcppTOML?color=brightgreen)](https://www.r-pkg.org/pkg/RcppTOML)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rcpptoml)](https://github.com/eddelbuettel/rcpptoml)

### What is TOML?

[TOML](https://toml.io/en/) is a configuration file grammar for humans. It is easier to read and
edit than the alternatives yet arguably more useful as it is strongly typed: values come back as
integer, double, (multiline-) character (strings), boolean or Datetime. Moreover, complex nesting
and arrays are supported as well.

For several years, this package used the C++11 library
[cpptoml](https://github.com/skystrife/cpptoml) written by [Chase
Geigle](https://github.com/skystrife).  However, as that library is no longer maintained, current
versions now use the newer C++17 library [toml++](https://github.com/marzer/tomlplusplus) by [Mark
Gillard](https://github.com/marzer).


### Example

Consider the following [TOML](https://toml.io/en/) input example input:

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

It can be read in _one statement_ and once parsed, R now has properly _typed_ input as shown in
default print method:

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

See the other examples and the [upstream documentation](https://toml.io/en/) for more.
Also note that most decent editors have proper [TOML](https://toml.io/en/) support
which makes editing and previewing a breeze:

![](https://raw.githubusercontent.com/eddelbuettel/rcpptoml/master/local/emacsAndTOML.png)

### Installation

Installation from source requires a C++17 compiler, and `g++` versions 8 and onward should suffice.

#### From CRAN

The package is on [CRAN](https://cran.r-project.org) and can be installed
from every mirror via

```{.r}
install.packages("RcppTOML")
```

#### From the ghrr-drat

Development releases may be provided by the
[ghrr](https://ghrr.github.io/drat/) repository which can accessed via

```{.r}
## if needed, first do:  install.packages("drat")
drat::addRepo("ghrr")
```

after which `install.packages("RcppTOML)` which access this repo.

Alternatively, set the repo information on the fly as _e.g._ in

```r
repos <- c("https://ghrr.github.io/drat", "https://cloud.r-project.org")
install.packages("RcppTOML", repos=repos)
```

which points to the [ghrr](https://ghrr.github.io/drat/) repository as well as a standard CRAN
mirror, but just for the length of this installation step.

### Status

Earlier versions relied upon [cpptoml](https://github.com/skystrife/cpptoml) and were feature-complete with
[TOML v0.5.0](https://toml.io/en/v0.5.0) (see the
[tests/](https://github.com/eddelbuettel/rcpptoml/tree/master/tests) directory).  They already parsed
everything that the underlying [cpptoml](https://github.com/skystrife/cpptoml) parsed with the same
(sole) exception of unicode escape characters in strings.

Since switching to [toml++](https://github.com/marzer/tomlplusplus) the package takes advantage of its  comprehensive TOML v1.0.0 support and should now be fully 1.0.0 compliant. Some new tests were added to demonstrate this.

As [toml++](https://github.com/marzer/tomlplusplus) also offers export to JSON and YAML as well as
TOML writing, we may add support to some of these features going forward.


### Continued Testing

As we rely on the [tinytest](https://cran.r-project.org/package=tinytest) package, the
already-installed package can also be verified via

```r
tinytest::test_package("RcppTOML")
```

at any point in time.

### Author

Dirk Eddelbuettel

### License

GPL (>= 2)
