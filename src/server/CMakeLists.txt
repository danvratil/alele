set(aleleserver_SRCS
    clientservice.cpp
    storage.cpp
    storage/directorystorage.cpp
)

add_executable(aleleserver ${aleleserver_SRCS})
target_link_libraries(aleleserver
    Threads::Threads
    alelecommon
    aleleservices
)

