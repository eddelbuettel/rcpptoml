
library(RcppTOML)

toml <- parseToml("float.toml")

expect_equal(names(toml), c("float"))
expect_equal(names(toml$float), c("both", "exponent", "fractional", "underscores"))

expect_equal(toml$float$both$key, 6.626e-34)

expect_equal(toml$float$exponent$key1, 5e22)
expect_equal(toml$float$exponent$key2, 1e+06)
expect_equal(toml$float$exponent$key3, -0.02)

expect_equal(toml$float$fractional$key1, 1)
expect_equal(toml$float$fractional$key2, 3.1415)
expect_equal(toml$float$fractional$key3, -0.01)

expect_equal(toml$float$underscores$key1, 9224617.445991228313)
