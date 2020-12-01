\name{RcppTOML-package}
\alias{RcppTOML-package}
\alias{RcppTOML}
\docType{package}
\title{
  R Access to Parser for TOML (Tom's Obvious Markup Language)
}
\description{
  TOML (\dQuote{Tom's Obvious Markup Language}) is a configuration file grammar for
  humans. It is easier to read and edit than the alternatives yet arguably more
  useful as it is stronly types: values come back as integer, double,
  (multiline-) character (strings), boolean or Datetime. Moreover, complex
  nesting and arrays are supported as well.
}
\details{
  At present, a single parsing function \code{parseTOML} (with
  convenience aliases \code{tomlparse} and \code{parseToml}) is implemented.
  It returns a list object corresponding to the configuration from
  the supplied file.
}
\author{
  Dirk Eddelbuettel put togther the R package. Charles Geigle wrote the
  cpptoml parser. Tom Preston-Werner is the Tom behind TOML.

  Maintainer: Dirk Eddelbuettel <edd@debian.org>
}
\references{
  TOML: \url{https://toml.io/en/}
}
\keyword{package}
\examples{
  library(RcppTOML)

  file <- system.file("toml", "example.toml", package="RcppTOML")

  toml <- parseTOML(file)  # given file, return parsed object

  summary(toml)            # really sparse summary method
  print(toml)              # print is a wrapper around str()
}
