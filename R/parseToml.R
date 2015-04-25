
parseToml <- function(filename, verbose=FALSE) {
    ## TODO tildeexpand filename
    fullfile <- path.expand(filename)
    toml <- tomlparseImpl(fullfile, verbose)
    class(toml) <- c("toml", "list")
    attr(toml, "file") <- filename
    toml
}

## alias for now, to be renamed
tomlparse <- function(...) parseToml(...)

print.toml <- function(x, ...) {
    print(str(x, give.attr=FALSE))           # convenient shortcut
    #klass <- oldClass(x)
    #oldClass(x) <- klass[klass != "toml"]
    #NextMethod("print")
    invisible(x) 
}

summary.toml <- function(object, ...) {
    cat("toml object with top-level slots:\n")
    cat("  ", paste(names(object), collapse=", "), "\n")
    cat("read from", attr(object, "file"), "\n")
    invisible(NULL)
}
