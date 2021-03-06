#  This file is distributed under the BSD 3-Clause License. See LICENSE for details.
cc_library(
    name = "elab",
    srcs = glob(
        ["*.cpp"],
        exclude = ["*test*.cpp"],
        ),
    hdrs = glob(["*.hpp"]),
    includes = ["."],
    linkopts = ["-lpthread"],
    visibility = ["//visibility:public"],
    deps = [
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "//mmap_lib:headers",
        "@fmt",
        "@iassert",
        "//lbench:headers",
        ],
    )

filegroup(
    name = "pyrope_test",
    srcs = ["tests/synth1.eprp"],
    )

filegroup(
    name = "verilog_test",
    srcs = ["tests/hierarchy.v"],
    )

cc_test(
    name = "ast_test",
    srcs = ["tests/ast_test.cpp"],
    deps = [
        "@gtest//:gtest_main",
        ":elab",
        ],
    )

cc_test(
    name = "elab_scanner_test",
    srcs = ["tests/elab_scanner_test.cpp"],
    args = ["$(location :pyrope_test)"],
    data = [
        ":pyrope_test",
        ],
    deps = [
        ":elab",
        ],
    )

cc_test(
    name = "elab_scanner_unit_test",
    srcs = ["tests/elab_scanner_unit_test.cpp"],
    deps = [
        ":elab",
        "@gtest//:gtest_main",
        ],
    )

cc_test(
    name = "elab_verilog_test",
    srcs = ["tests/elab_verilog_test.cpp"],
    args = ["$(location :verilog_test)"],
    data = [
        ":verilog_test",
        ],
    deps = [
        ":elab",
        ],
    )

# cc_test(
#     name = "lnast_parser_unit_test",
#     srcs = ["tests/lnast_parser_unit_test.cpp"],
#     data = ["//inou/cfg:cfg_pts"],
#     tags = ["fixme"],
#     deps = [
#         ":elab",
#         "@gtest//:gtest_main",
#         ],
#     )

# cc_binary(
#     name = "lnast_parser_test",
#     srcs = ["tests/lnast_parser_test.cpp"],
#     data = ["//inou/cfg:cfg_pts"],
#     deps = [
#         ":elab",
#         "@gtest//:gtest_main",
#         ],
#     )

cc_binary(
    name = "elab_pyrope_test",
    srcs = ["elab_pyrope_test.cpp"],
    args = ["$(location :pyrope_test)"],
    deps = [
        ":elab",
        ],
    data = [
        ":pyrope_test",
        ],
    )
