cc_library(
    name = "lib",
    hdrs = [
        "lib/clustering.h",
    ],
    srcs = [
        "lib/clustering.cpp",
        "lib/dsu.cpp",
        "lib/dsu.h",
        "lib/set_stats.h",
    ],
    copts = [
        "-std=c++14",
        "-Wall",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "cli",
    srcs = [
        "args.cpp",
        "args.h",
        "main.cpp",
        "timer.h",
    ],
    deps = [":lib"],
    copts = [
        "-std=c++14",
        "-Wall",
    ],
    visibility = ["//visibility:public"],
)
