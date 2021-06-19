set(protocol_SRCS
    clientserviceinterface.h
)

add_library(aleleservices SHARED ${protocol_SRCS})
target_link_libraries(aleleservices
    PUBLIC
    alelecommon
    Qt5::Core
    QCoro::QCoro
)

