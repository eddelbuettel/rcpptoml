\name{parseTOML}
\alias{parseTOML}
\alias{tomlparse}
\alias{parseToml}
\alias{print.toml}
\alias{summary.toml}
\title{
  Parse a TOML configuration file
}
\description{
  The \code{parseTOML} function parses \sQuote{TOML} (for \sQuote{Tom's
    Obvious Markup Language}) files.  The TOML format both highly
  readable and expressive, allows comments, indentation and other
  aspects suitable for \emph{human} readers, contains typed objects yet
  allows everything similar configuration languages permit.
}
\usage{
  parseTOML(filename, verbose = FALSE)

  \S3method{print}{toml} (x, ...)
  \S3method{summary}{toml} (object, ...)
}
\arguments{
  \item{filename}{A character object denoting a path and
    file (where tilde-expansion is performed as well).}
  \item{verbose}{A logical switch to turn on (very) verbose operation
    which can be useful in debugging a parsing issue in a file.}
  \item{x}{A toml object.}
  \item{object}{A toml object.}
  \item{...}{Furter arguments.}
}
\details{
  The package uses the \sQuote{cpptoml} C++11 parser by Charles
  Geigle. This requires a recent-enough C++11 compiler which excludes
  one deployed by Rtools on Windows at the time the package was
  initially put together.
}
\value{
  A \code{toml} object is returned, which is really just a list object
  with a class attribute to allow for \code{print} and \code{summary} methods.
}
\references{
  TOML: \url{https://github.com/toml-lang/toml}
  cpptoml: \url{https://github.com/skystrife/cpptoml}
}
\author{
  Dirk Eddelbuettel put togther the R package. Charles Geigle wrote the
  cpptoml parser. Tom Preston-Werner is the Tom behind TOML.

  Maintainer: Dirk Eddelbuettel <edd@debian.org>
}
\examples{
  library(RcppTOML)

  file <- system.file("toml", "example.toml", package="RcppTOML")

  toml <- parseTOML(file)  # given file, return parsed object

  summary(toml)            # really sparse summary method
  print(toml)              # print is a wrapper around str()
}
\keyword{package}
