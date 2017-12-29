//
// Created by leo on 2017/12/26.
//

#include "handler.h"

void server_msg_handle(MSG* msg) {
    if(msg->opercode == OPER_QUIT) {
        RECV_QUIT = 1;
    } else {
        LOG(INFO_LOG, msg->context);
    }
}

void LOG(const char* prompt, const char* s) {
    printf("%s %s\n", prompt, s);
}

