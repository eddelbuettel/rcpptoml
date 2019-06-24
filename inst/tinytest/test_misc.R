
isSolaris <- Sys.info()[["sysname"]] == "SunOS"

toml <- RcppTOML::parseToml("

title = \"TOML Example\"

[owner]
name = \"Tom Preston-Werner\"
dob = 1979-05-27T07:32:00-08:00 # First class dates

[database]
server = \"192.168.1.1\"
ports = [ 8001, 8001, 8002 ]
connection_max = 5000
enabled = true

", fromFile=FALSE)

expect_true(setequal(names(toml), c("title", "owner", "database")))

expect_true(setequal(names(toml$owner), c("name", "dob")))
expect_equal(toml$owner$name, "Tom Preston-Werner")
if (!isSolaris) expect_equal(toml$owner$dob, as.POSIXct("1979-05-27 15:32:00", tz="UTC", usetz=TRUE))

expect_true(setequal(names(toml$database), c("server", "ports", "connection_max", "enabled")))
expect_equal(toml$database$server, "192.168.1.1")
expect_equal(toml$database$ports, c(8001L, 8001L, 8002L))
expect_equal(toml$database$connection_max, 5000L)
expect_equal(toml$database$enabled, TRUE)
