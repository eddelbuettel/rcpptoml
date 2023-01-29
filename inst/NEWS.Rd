\name{NEWS}
\title{News for Package \pkg{RcppTOML}}
\newcommand{\ghpr}{\href{https://github.com/eddelbuettel/rcpptoml/pull/#1}{##1}}
\newcommand{\ghit}{\href{https://github.com/eddelbuettel/rcpptoml/issues/#1}{##1}}

\section{Changes in version 0.2.2 (2023-01-29)}{
  \itemize{
    \item New \pkg{toml++} version 3.3.0 with fix to permit compilation on
    ancient macOS systems as used by CRAN for the Intel-based builds.
  }
}

\section{Changes in version 0.2.1 (2023-01-25)}{
  \itemize{
    \item Explicitly set \code{-DTOML_ENABLE_FLOAT16=0} to permit compilation
    on some architectures stumbling of the type.
  }
}

\section{Changes in version 0.2.0 (2023-01-10)}{
  \itemize{
    \item Rewritten in C++17 using \pkg{toml++} for TOML v1.0.0 compliance
    \item Unchanged interface from R, unchanged (and expanded tests)
    \item Several small continuous integration upgrades since last release
  }
}

\section{Changes in version 0.1.7 (2020-12-01)}{
  \itemize{
    \item Add \code{#include <limits>} to header file, also contributed
    upstream, to permit compilation under the (unreleased) \code{g++-11}.
    \item Switch the simple \code{cleanup} script to \code{sh}.
    \item Switch CI use to \href{https://eddelbuettel.github.io/r-ci/}{r-ci}
    for focal and \pkg{bspm}.
    \item Update several TOML URLs to \code{https://toml.io/en/}.
  }
}

\section{Changes in version 0.1.6 (2019-06-25)}{
  \itemize{
    \item Propagate the \code{escape} switch to calls of
    \code{getTable()} and \code{getArray()} (Václav Hausenblas in
    \ghpr{32} completing \ghpr{26}).
    \item The \code{README.md} file now mentions TOML v0.5.0 support
    (Watal Iwasaki in \ghpr{35} addressing \ghit{33}).
    \item Encodings in arrays is to UTF-8 for character (Václav
    Hausenblas in \ghpr{36} completing \ghpr{28})
    \item The package now uses \pkg{tinytest} (Dirk in \ghpr{38} fixing
    \ghit{37}, also Václav in \ghpr{39}).
  }
}

\section{Changes in version 0.1.5 (2018-10-31)}{
  \itemize{
    \item Escape characters treatment now has toggle (Václav Hausenblas
    in \ghpr{27} fixing \ghpr{26})
    \item The TOML 0.5.0 'time' type is now supported (somewhat) by
    returning a formatted string (\ghpr{29})
    \item Encodings are now supported by defaulting to UTF-8 (Václav Hausenblas
    in \ghpr{30} fixing \ghpr{28})
  }
}

\section{Changes in version 0.1.4 (2018-10-23)}{
  \itemize{
    \item Spelling / grammar fixes to README (Jon Calder in \ghpr{18})
    \item Cast from \code{StretchyList} to \code{List} ensures lists
    appear as \code{List} objects in R
    \item Support optional \code{includize} pre-processor for recursive
    includes by Dan Dillon as a header-only library (\ghpr{21} and \ghpr{22})
    \item Support \code{includize} argument in R and C++ parser interface
    \item Added a few more \code{#nocov} tags for coverage (\ghpr{23})
    \item Synchronized with new upstream
    \href{https://github.com/skystrife/cpptoml}{cpptoml} version supporting the
    \href{https://toml.io/en/v0.5.0}{TOML v0.5.0} specification. (\ghpr{25})
  }
}

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
