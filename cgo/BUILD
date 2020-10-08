load("@io_bazel_rules_go//go:def.bzl", "go_library", "go_test")

go_library(
    name = "go_default_library",
    srcs = [
        "wrap.go",
    ],
    cdeps = [
        "//:lib",
    ],
    cgo = True,
    importpath = "github.com/antonovvk/agglomerative_clustering/cgo",
    visibility = ["//visibility:public"],
)

go_test(
    name = "go_default_test",
    srcs = ["wrap_test.go"],
    embed = [":go_default_library"],
)
