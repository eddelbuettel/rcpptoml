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
  parseTOML(input, verbose = FALSE, fromFile=TRUE, includize=FALSE, escape=TRUE)

  \S3method{print}{toml} (x, ...)
  \S3method{summary}{toml} (object, ...)
}
\arguments{
  \item{input}{A character object either denoting a path and
    file (where tilde-expansion is performed as well) from parsing from
    file, or a containing a suitable \sQuote{TOML} expression that is
    parsed from this expression.}
  \item{verbose}{A logical switch to turn on (very) verbose operation
    which can be useful in debugging a parsing issue in a file.}
  \item{fromFile}{A logical switch indicating whether \code{input} is
    interpreted as a filename (with path) which is to be parsed, or a
    whether the \sQuote{TOML} expression in the string is parsed;
    default is file mode.}
  \item{includize}{A logical switch indicating whether the
    \code{includize} stream buffer class for (non-standard but very
    useful) include statements should be used.}
  \item{escape}{A logical switch indicating whether special characters
  in strings (namely new line, double quotation mark and backslash)
  should be escaped in both printed output (when verbose = TRUE) and
  returned values or only in the printed output. Defaults to TRUE for
  the sake of backward compatibility.}
  \item{x}{A toml object.}
  \item{object}{A toml object.}
  \item{...}{Furter arguments.}
}
\details{
  The package uses the \sQuote{cpptoml} C++11 parser by Charles
  Geigle. This requires a recent-enough C++11 compiler which excludes
  one deployed by Rtools on Windows at the time the package was
  initially put together.

  Following TOML specification this package assumes that any file input
  is a UTF-8 encoded text file. Any non-file input (when \code{fromFile
    = FALSE}) is converted to UTF-8 if necessary (using R's
  \code{enc2utf()}. Note that the conversion to UTF-8 may fail for input
  with "unknown" declared encoding if the true encoding does not match
  system's locale.
}
\value{
  A \code{toml} object is returned, which is really just a list object
  with a class attribute to allow for \code{print} and \code{summary}
  methods.
}
\references{
  TOML: \url{https://toml.io/en/}
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

  txt <- "value='''\nHello\nWorld!'''"      # input with \n is ..
  parseTOML(input = txt, fromFile = FALSE)  # ... (doubly) escaped by default
  parseTOML(input = txt, fromFile = FALSE, escape = FALSE) # ... kept 'as is'

}
\keyword{package}
