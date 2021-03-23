set(aleleserver_SRCS
    main.cpp
)

add_executable(aleleserver ${aleleserver_SRCS})
target_link_libraries(aleleserver
    Threads::Threads
    alelecommon
)

