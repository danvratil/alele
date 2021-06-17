set(protocol_SRCS
    client.cpp
)

add_library(aleleprotocol SHARED ${protocol_SRCS})
target_link_libraries(aleleprotocol
    PUBLIC
    alelecommon
    msgpackc-cxx
)

