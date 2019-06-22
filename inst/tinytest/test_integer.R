
library(RcppTOML)

toml <- parseToml("integer.toml")

expect_equal(names(toml), c("integer"))
expect_equal(names(toml$integer), c("key1", "key2", "key3", "key4", "underscores"))

expect_equal(toml$integer$key1, 99L)
expect_equal(toml$integer$key2, 42L)
expect_equal(toml$integer$key3, 0L)
expect_equal(toml$integer$key4, -17L)

expect_equal(toml$integer$underscores$key1, 1000L)
expect_equal(toml$integer$underscores$key2, 5349221L)
expect_equal(toml$integer$underscores$key3, 12345L)
