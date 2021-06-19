set(common_tests_SRCS
    id_test.cpp
)

add_executable(common_tests ${common_tests_SRCS})
target_link_libraries(common_tests
    alelecommon
    GTest::gtest
    GTest::gtest_main)
target_compile_definitions(common_tests PUBLIC UNIT_TESTS)

gtest_discover_tests(common_tests TEST_PREFIX "common.")

