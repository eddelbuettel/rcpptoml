
library(RcppTOML)

toml <- parseToml("strings.toml")

expect_equal(names(toml), "string")
expect_true(setequal(names(toml$string), c("basic", "literal", "multiline")))

expect_equal(names(toml$string$basic), "basic")
expect_equal(toml$string$basic$basic, "I'm a string. \\\"You can quote me\\\". Name\tJose\\nLocation\tSF.")

expect_true(setequal(names(toml$string$multiline), c("key1", "key2", "key3", "continued")))
expect_equal(toml$string$multiline$key1, "One\\nTwo")
expect_equal(toml$string$multiline$key2, "One\\nTwo")
expect_equal(toml$string$multiline$key3, "One\\nTwo")
expect_true(setequal(names(toml$string$multiline$continued), c("key1", "key2", "key3")))
expect_equal(toml$string$multiline$continued$key1, "The quick brown fox jumps over the lazy dog.")
expect_equal(toml$string$multiline$continued$key2, "The quick brown fox jumps over the lazy dog.")
expect_equal(toml$string$multiline$continued$key3, "The quick brown fox jumps over the lazy dog.")


expect_true(setequal(names(toml$string$literal), c("winpath", "winpath2", "quoted", "regex", "multiline")))
expect_equal(toml$string$literal$winpath, "C:\\\\Users\\\\nodejs\\\\templates")
expect_equal(toml$string$literal$winpath2, "\\\\\\\\ServerX\\\\admin$\\\\system32\\\\")
expect_equal(toml$string$literal$quoted, "Tom \\\"Dubs\\\" Preston-Werner")
expect_equal(toml$string$literal$regex, "<\\\\i\\\\c*\\\\s*>")
expect_true(setequal(names(toml$string$literal$multiline), c("regex2", "lines")))
expect_equal(toml$string$literal$multiline$regex2, "I [dw]on't need \\\\d{2} apples")
expect_equal(toml$string$literal$multiline$lines, "The first newline is\\ntrimmed in raw strings.\\n   All other whitespace\\n   is preserved.\\n")
