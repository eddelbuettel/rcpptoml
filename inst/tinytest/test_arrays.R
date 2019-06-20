
library(RcppTOML)

toml <- parseToml("arrays.toml")

expect_equal(names(toml), c("array", "fruit", "products"))
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

expect_equal(toml$fruit[[1]]$name, "apple")
expect_equal(toml$fruit[[1]]$physical, list(color="red", shape="round"))
expect_equal(toml$fruit[[1]]$variety, list(list(name="red delicious"),
                                           list(name="granny smith")))
expect_equal(toml$fruit[[2]]$name, "banana")
expect_equal(toml$fruit[[2]]$variety, list(list(name="plantain")))

expect_equal(toml$products[[1]], list(name="Hammer", sku=738594937L))
expect_equal(toml$products[[2]], list())
expect_equal(toml$products[[3]], list(color="gray", name="Nail", sku=284758393L))
