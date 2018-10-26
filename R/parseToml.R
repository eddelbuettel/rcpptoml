## RcppTOML -- Rcpp bindings to TOML via cpptoml
##
## Copyright (C) 2015 - 2017  Dirk Eddelbuettel
##
## This file is part of RcppTOML.
##
## RcppTOML is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## RcppTOML is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with RcppTOML.  If not, see <http://www.gnu.org/licenses/>.

parseTOML <- function(input, verbose=FALSE, fromFile=TRUE, includize=FALSE, escape=TRUE) {
    if (fromFile) {
        toml <- tomlparseImpl(path.expand(input), verbose, fromFile, includize, escape)
    } else {
        toml <- tomlparseImpl(enc2utf8(input), verbose, fromFile, includize, escape)
    }
    class(toml) <- c("toml", "list")
    attr(toml, "file") <- input
    toml
}

## alias for now, to be renamed
tomlparse <- function(...) parseTOML(...)

## alias for now, to be renamed
parseToml <- function(...) parseTOML(...)


print.toml <- function(x, ...) {
    cat(utils::str(x, give.attr=FALSE))		           # convenient shortcut
    invisible(x)
}

summary.toml <- function(object, ...) {
    cat("toml object with top-level slots:\n")
    cat("  ", paste(names(object), collapse=", "), "\n")
    cat("read from '", attr(object, "file"), "'\n")
    invisible(NULL)
}
