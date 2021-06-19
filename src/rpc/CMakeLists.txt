set(rpc_SRCS
    server.cpp
    zeromq.cpp
)

add_library(alelerpc SHARED ${rpc_SRCS})
target_link_libraries(alelerpc
    PUBLIC
    Qt5::Core
    libzmq::libzmq
)
