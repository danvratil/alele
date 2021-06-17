set(common_tests_SRCS
    main.cpp
    id_test.cpp
)

include(Catch)
include(ParseAndAddCatchTests)

add_executable(common_tests ${common_tests_SRCS})
target_link_libraries(common_tests
    alelecommon
    Catch2::Catch2)

catch_discover_tests(common_tests TEST_PREFIX "Common::")
