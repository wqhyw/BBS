cmake_minimum_required(VERSION 3.8)
project(BBS)

set(CMAKE_C_FLAGS "-lncurses -lpanel")

SET(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(public)

set(CLIENT_MAIN client/client_main.c)
set(SERVER_MAIN server/server_main.c)

set(INCLUDE_DIRS public/include client/include server/include)

aux_source_directory(client/src CLIENT_SRCS)
aux_source_directory(public/src PUBLIC_STCS)
aux_source_directory(server/src SERVER_SRCS)

include_directories(${INCLUDE_DIRS})

set(CMAKE_C_STANDARD 99)

# test_main
add_executable(BBS main.c ${PUBLIC_SRCS} ${INCLUDE_DIRS})

# client_main
add_executable(client ${CLIENT_MAIN} ${CLIENT_SRCS})
target_link_libraries(client public)

# server_main
add_executable(server ${SERVER_MAIN} ${SERVER_SRCS})
target_link_libraries(server public)