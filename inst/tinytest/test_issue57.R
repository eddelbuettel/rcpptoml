
## issue #57 noted that mixed type arrays should be supported, as well as dictionaries

library(RcppTOML)

expect_silent(val <- parseTOML('foo = [1,"bar"]', fromFile = FALSE))
expect_equal(length(val), 1L)
expect_equal(names(val), "foo")
expect_true(inherits(val, "list"))

lst <- val[[1]]
expect_equal(length(lst), 2L)
expect_equal(lst[[1]], 1L)
expect_equal(lst[[2]], "bar")

txt <- r"( contributors = [ "Foo Bar <foo@example.com>", { name = "Baz Qux", email = "bazqux@example.com", url = "https://example.com/bazqux" } ] )"
expect_silent(val <- parseTOML(txt, fromFile=FALSE))
expect_equal(length(val), 1L)
expect_equal(names(val), "contributors")
expect_true(inherits(val, "list"))

lst <- val[[1]]
expect_equal(length(lst), 2L)
expect_equal(lst[[1]], "Foo Bar <foo@example.com>")
expect_true(inherits(lst[[2]], "list"))

lst2 <- lst[[2]]
expect_equal(length(lst2), 3L)
expect_equal(names(lst2), c("email", "name", "url"))  # reordered
expect_equal(lst2$name, "Baz Qux")
expect_equal(lst2$email, "bazqux@example.com")
expect_equal(lst2$url, "https://example.com/bazqux")
