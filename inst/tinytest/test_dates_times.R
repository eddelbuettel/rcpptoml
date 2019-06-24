
isSolaris <- Sys.info()[["sysname"]] == "SunOS"

library(RcppTOML)

## v0.5 brings more date and time supprt
toml <- parseToml("dates_and_times.toml")

## reference results
pt1 <- as.POSIXct("1979-05-27 07:32:00", tz="UTC", usetz=TRUE)
pt2 <- as.POSIXct("1979-05-27 07:32:00.999999", tz="UTC", usetz=TRUE)
pt3 <- as.POSIXct("1979-05-27 00:32:00.999999", tz="UTC", usetz=TRUE)

if (!isSolaris) expect_equal(toml$odt1, pt1)
expect_true(inherits(toml$odt1, "POSIXct"))

if (!isSolaris) expect_equal(toml$odt2, pt1)
expect_true(inherits(toml$odt2, "POSIXct"))

if (!isSolaris) expect_equal(toml$odt3, pt2)
expect_true(inherits(toml$odt3, "POSIXct"))

if (!isSolaris) expect_equal(toml$odt4, pt1)
expect_true(inherits(toml$odt4, "POSIXct"))

if (!isSolaris) expect_equal(toml$ldt1, pt1)
expect_true(inherits(toml$ldt1, "POSIXct"))

if (!isSolaris) expect_equal(toml$ldt2, pt3)
expect_true(inherits(toml$ldt1, "POSIXct"))

expect_equal(class(toml$ld1), "Date")
expect_equal(toml$ld1, as.Date("1979-05-27"))
