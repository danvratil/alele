set(alelecommon_SRCS
    id.cpp
)

add_library(alelecommon SHARED ${alelecommon_SRCS})
target_link_libraries(alelecommon
    PUBLIC
    Qt5::Core
    tl-expected::tl-expected
)
target_include_directories(alelecommon
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)
