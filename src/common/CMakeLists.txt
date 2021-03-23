set(libalelecommon_SRCS
    zeromq.cpp
)

add_library(alelecommon ${libalelecommon_SRCS})
target_link_libraries(alelecommon
    PUBLIC
    libzmq::libzmq
)
target_include_directories(alelecommon
    INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)
