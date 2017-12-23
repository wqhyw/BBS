cmake_minimum_required(VERSION 3.8)
project(BBS)

add_subdirectory(public)

#set(CLIENT_MAIN client/client_main.c)
#set(SERVER_MAIN server/server_main.c)
#
set(INCLUDE_DIRS public/include client/include server/include)
#
#aux_source_directory(client/src CLIENT_SRCS)
#aux_source_directory(server/src SERVER_SRCS)

include_directories(${INCLUDE_DIRS})

set(CMAKE_C_STANDARD 99)

#set(SOURCE_FILES main.c ${CLIENT_SRCS} ${SERVER_SRCS} ${INCLUDE_DIRS})
set(SOURCE_FILES main.c ${INCLUDE_DIRS})

# test_main
add_executable(BBS ${SOURCE_FILES})
target_link_libraries(BBS public)

## client_main
#add_executable(client ${CLIENT_MAIN} ${CLIENT_SRCS})
#target_link_libraries(client public)
#
## server_main
#add_executable(server ${SERVER_MAIN} ${SERVER_SRCS})
#target_link_libraries(server public)