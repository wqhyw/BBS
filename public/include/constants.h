//
// Created by leo on 2017/11/30.
//

#ifndef BBS_CONSTANTS_H
#define BBS_CONSTANTS_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_BUF_LEN      (512)                   //max buffer size
#define MAX_ARG_LEN      (16)                    //max arg length

/**Client Operation CODE**/
//operation: client register
#define OPER_REGISTER   (0xC00)
//operation: client login
#define OPER_LOGIN      (0xC01)
//operation: client send
#define OPER_SEND       (0xC02)
//operation: client logout
#define OPER_LOGOUT     (0xC03)
//operation: client quit
#define OPER_QUIT       (0xC04)

#endif //BBS_CONSTANTS_H
