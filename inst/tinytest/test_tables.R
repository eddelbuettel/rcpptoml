
library(RcppTOML)

toml <- parseToml("tables.toml")

expect_true(setequal(names(toml), c("table", "x")))

expect_true(setequal(names(toml$table), c("key", "subtable", "inline")))

expect_equal(toml$table$key, "value")

expect_equal(toml$table$subtable$key, "another value")

expect_equal(toml$table$x$y$z$w, NULL)  # not list()

expect_equal(names(toml$table$inline), c("name", "point"))
expect_equal(toml$table$inline$name, list(first="Tom", last="Preston-Werner"))
expect_equal(toml$table$inline$point, list(x=1L, y=2L))
