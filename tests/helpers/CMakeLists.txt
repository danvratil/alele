add_library(aleletesthelpers INTERFACE)
target_include_directories(aleletesthelpers
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests>
)
