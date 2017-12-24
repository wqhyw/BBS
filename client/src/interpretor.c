//
// Created by leo on 2017/11/30.
//

#include "interpretor.h"

int run_cmd(MSG* msg){
    switch(msg->opercode) {
        case OPER_REGISTER:
        case OPER_LOGIN:
        case OPER_SEND:
        case OPER_LOGOUT:
            return async_sender(msg, SERVER_IP, SERVER_PROT);
        case OPER_QUIT:
            async_sender(init_msg(OPER_QUIT, "", 5), SERVER_IP, SERVER_PROT);
            quit();
        default:
            return 0;
    }
}

void quit() {
    printf("do some cleanning.\n");
    exit(0);
}
