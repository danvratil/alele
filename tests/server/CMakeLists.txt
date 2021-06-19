set(servertests_SRCS
    ../../src/server/clientservice.cpp
    ../../src/server/storage.cpp
    ../../src/server/storage/directorystorage.cpp
    clientservice_test.cpp
    main.cpp
)

add_executable(server_tests ${servertests_SRCS})
target_link_libraries(server_tests
    aleletesthelpers
    alelecommon
    QCoro::QCoro
    GTest::gtest
    GTest::gmock
)
target_compile_definitions(server_tests PUBLIC UNIT_TESTS)

gtest_discover_tests(server_tests TEST_PREFIX "server.")
