\name{NEWS}
\title{News for Package \pkg{RcppTOML}}
\newcommand{\ghpr}{\href{https://github.com/eddelbuettel/rcpptoml/pull/#1}{##1}}
\newcommand{\ghit}{\href{https://github.com/eddelbuettel/rcpptoml/issues/#1}{##1}}

\section{Changes in version 0.1.3 (2017-04-25)}{
  \itemize{
    \item Nested TableArray types are now correctly handled (\ghit{16})
  }
}

\section{Changes in version 0.1.2 (2017-03-26)}{
  \itemize{
    \item Dates and Datetimes in arrays in the input now preserve their
    types instead of converting to numeric vectors (\ghit{13})
    \item Boolean vectors are also correctly handled (\ghit{14})
    \item TableArray types are now stored as lists in a single named
    list (\ghit{15})
    \item The README.md file was expanded with an example and
    screenshot.
    \item Added file \code{init.c} with calls to \code{R_registerRoutines()}
    \code{and R_useDynamicSymbols()}; also use \code{.registration=TRUE}
    in \code{useDynLib} in \code{NAMESPACE}
    \item Two example files were updated.
  }
}

\section{Changes in version 0.1.1 (2017-02-12)}{
  \itemize{
    \item Synchronized multiple times with ccptoml upstream adding
    support for local datetime and local date and more (PR \ghpr{9},
    \ghpr{10}, PR \ghpr{11})
    \item Dates are now first class types, some support for local versus
    UTC times was added (though it may be adviseable to stick with UTC)
    \item Parsing from (R) character variables is now supported as well
    \item Output from \code{print.toml} no longer prints extra newlines
  }
}

\section{Changes in version 0.1.0 (2017-01-05)}{
  \itemize{
    \item Added Windows support by relying on \code{Rcpp::mktime00()}
    (PR s\ghpr{6} and \ghpr{8} closing \ghit{5} and \ghit{3})
    \item Synchronized with \code{cpptoml} upstream (\ghpr{9})
    \item Updated Travis CI support via newer \code{run.sh} 
  }
}

\section{Changes in version 0.0.5 (2015-12-19)}{
  \itemize{
    \item Synchronized with \code{cpptoml} upstream (PR \ghpr{4})
    \item Improved and extended examples
  }
}

\section{Changes in version 0.0.4 (2015-07-16)}{
  \itemize{
    \item Minor update of upstream \code{cpptoml.h}
    \item More explicit call of \code{utils::str()}
    \item Properly cope with empty lists (\ghpr{2})
  }
}

\section{Changes in version 0.0.3 (2015-04-27)}{
  \itemize{
    \item First CRAN release after four weeks of initial development
  }
}


