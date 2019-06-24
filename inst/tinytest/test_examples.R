
library(RcppTOML)

isWindows <- Sys.info()[["sysname"]] == "Windows"
isSolaris <- Sys.info()[["sysname"]] == "SunOS"

## basic toml-lang::tests/example.toml
toml <- parseToml("toml_example.toml")

expect_true(setequal(names(toml), c("title", "owner", "database", "servers",
                                    "clients", "products")))

expect_equal(toml$title, "TOML Example")

expect_true(setequal(names(toml$owner), c("name", "organization", "bio", "dob")))
expect_equal(toml$owner$name, "Tom Preston-Werner")
expect_equal(toml$owner$organization, "GitHub")
expect_equal(toml$owner$bio, "GitHub Cofounder & CEO\\nLikes tater tots and beer.")
if (!isSolaris) expect_equal(toml$owner$dob, as.POSIXct("1979-05-27 07:32:00", tz="UTC", usetz=TRUE))

expect_true(setequal(names(toml$database), c("server", "ports", "connection_max", "enabled")))
expect_equal(toml$database$server, "192.168.1.1")
expect_equal(toml$database$ports, c(8001L, 8001L, 8002L))
expect_equal(toml$database$connection_max, 5000L)
expect_equal(toml$database$enabled, TRUE)

expect_true(setequal(names(toml$servers), c("alpha", "beta")))
expect_true(setequal(names(toml$servers$alpha), c("ip", "dc")))
expect_equal(toml$servers$alpha$ip, "10.0.0.1")
expect_equal(toml$servers$alpha$dc, "eqdc10")
expect_true(setequal(names(toml$servers$beta), c("ip", "dc", "country")))
expect_equal(toml$servers$beta$ip, "10.0.0.2")
expect_equal(toml$servers$beta$dc, "eqdc10")
expect_equal(toml$servers$beta$country, "\u4e2d\u56fd")

expect_true(setequal(names(toml$clients), c("data", "hosts")))
expect_true(setequal(toml$clients$data, list(c("gamma", "delta"), c(1L, 2L))))
expect_true(setequal(toml$clients$hosts, c("alpha", "omega")))

expect_true(setequal(toml$products[[1]], list(name="Hammer", sku=738594937L)))
expect_true(setequal(toml$products[[2]], list(color="gray", name="Nail", sku=284758393L)))



## harder toml-lang::tests/hard_example.toml
toml <- parseToml("toml_hard_example.toml")

expect_equal(names(toml), "the")

expect_true(setequal(names(toml$the), c("test_string", "hard")))
expect_equal(toml$the$test_string, "You'll hate me after this - #")

expect_true(setequal(names(toml$the$hard), c("test_array", "test_array2", "another_test_string",
                                             "harder_test_string", "bit#")))
expect_equal(toml$the$hard$test_array, c("] ", " # "))
expect_equal(toml$the$hard$test_array2, c("Test #11 ]proved that", "Experiment #9 was a success"))
expect_equal(toml$the$hard$another_test_string, " Same thing, but with a string #")
expect_equal(toml$the$hard$harder_test_string, " And when \\\"'s are in the string, along with # \\\"")
expect_equal(toml$the$hard$`bit#`$`what?`, "You don't think some user won't do that?")
expect_equal(toml$the$hard$`bit#`$multi_line_array, "]")


## example toml-lang::examples/example-v0.4.0.toml
##
## note that we edited line 56 which cannot be parsed by cpptoml
##
## also note that there is some redunancy as we had used these tests for the first
## iteration in tests/ which are now tests files here
toml <- parseToml("toml_example-v0.4.0.toml")

expect_true(setequal(names(toml), c("table", "string", "integer", "float",
                                    "boolean", "datetime", "array", "products",
                                    "fruit", "x")))

expect_equal(toml$table$key, "value")
expect_equal(toml$table$subtable$key, "another value")
expect_equal(toml$table$inline$name, list(first="Tom", last="Preston-Werner"))
expect_equal(toml$table$inline$point, list(x=1L, y=2L))

expect_equal(toml$x$y$y$z$w, NULL)

expect_equal(toml$string$basic$basic,
             "I'm a string. \\\"You can quote me\\\". Name\tJose\\nLocation\tSF.")
expect_equal(toml$string$multiline$key1, "One\\nTwo")
expect_equal(toml$string$multiline$key2, "One\\nTwo")
expect_equal(toml$string$multiline$key3, "One\\nTwo")
expect_equal(toml$string$multiline$continued$key1, "The quick brown fox jumps over the lazy dog.")
expect_equal(toml$string$multiline$continued$key2, "The quick brown fox jumps over the lazy dog.")
expect_equal(toml$string$multiline$continued$key3, "The quick brown fox jumps over the lazy dog.")
expect_equal(toml$string$literal$winpath, "C:\\\\Users\\\\nodejs\\\\templates")
expect_equal(toml$string$literal$winpath2, "\\\\\\\\ServerX\\\\admin$\\\\system32\\\\")
expect_equal(toml$string$literal$quoted, "Tom \\\"Dubs\\\" Preston-Werner")
expect_equal(toml$string$literal$regex, "<\\\\i\\\\c*\\\\s*>")
expect_equal(toml$string$literal$multiline$regex2, "I [dw]on't need \\\\d{2} apples")
expect_equal(toml$string$literal$multiline$lines,
             paste0("The first newline is\\ntrimmed in raw strings.\\n",
                    "   All other whitespace\\n   is preserved.\\n"))

expect_equal(names(toml$integer), c("key1", "key2", "key3", "key4", "underscores"))
expect_equal(toml$integer$key1, 99L)
expect_equal(toml$integer$key2, 42L)
expect_equal(toml$integer$key3, 0L)
expect_equal(toml$integer$key4, -17L)
expect_equal(toml$integer$underscores$key1, 1000L)
expect_equal(toml$integer$underscores$key2, 5349221L)
expect_equal(toml$integer$underscores$key3, 12345L)

expect_equal(names(toml$float), c("both", "exponent", "fractional", "underscores"))
expect_equal(toml$float$both$key, 6.626e-34)
expect_equal(toml$float$exponent$key1, 5e22)
expect_equal(toml$float$exponent$key2, 1e+06)
expect_equal(toml$float$exponent$key3, -0.02)
expect_equal(toml$float$fractional$key1, 1)
expect_equal(toml$float$fractional$key2, 3.1415)
expect_equal(toml$float$fractional$key3, -0.01)
expect_equal(toml$float$underscores$key1, 9224617.445991228313)


expect_true(toml$boolean$True)
expect_false(toml$boolean$False)

ref1 <- as.POSIXct("1979-05-27 07:32:00", tz="UTC", usetz=TRUE)
ref2 <- as.POSIXct("1979-05-27 07:32:00.999999", tz="UTC", usetz=TRUE)
if (!isSolaris) expect_equal(toml$datetime$key1, ref1)
if (!isSolaris) expect_equal(toml$datetime$key2, ref1)
if (!isSolaris) expect_equal(toml$datetime$key3, ref2)


expect_equal(names(toml$array), paste0("key", 1:6))
expect_equal(toml$array$key1, 1:3)
expect_equal(class(toml$array$key1), "integer")
expect_equal(toml$array$key2, c("red", "yellow", "green"))
expect_equal(toml$array$key3[[1]], 1:2)
expect_equal(toml$array$key3[[2]], 3:5)
expect_equal(toml$array$key4[[1]], 1:2)
expect_equal(toml$array$key4[[2]], letters[1:3])
expect_equal(toml$array$key5, 1:3)
expect_equal(toml$array$key6, 1:2)
expect_equal(toml$products[[1]], list(name="Hammer", sku=738594937L))
expect_equal(toml$products[[2]], list())
expect_equal(toml$products[[3]], list(color="gray", name="Nail", sku=284758393L))
expect_equal(toml$fruit[[1]]$name, "apple")
expect_equal(toml$fruit[[1]]$physical, list(color="red", shape="round"))
expect_equal(toml$fruit[[1]]$variety, list(list(name="red delicious"),
                                           list(name="granny smith")))
expect_equal(toml$fruit[[2]]$name, "banana")
expect_equal(toml$fruit[[2]]$variety, list(list(name="plantain")))
