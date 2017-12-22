//
// Created by leo on 2017/11/30.
//


#include "../include/msg.h"

char* get_op(MSG* msg) {
    switch (msg->opercode) {
        case OPER_REGISTER:
            return "REGISTER";
        case OPER_LOGIN:
            return "LOGIN";
        case OPER_SEND:
            return "SEND";
        case OPER_LOGOUT:
            return "LOGOUT";
        case OPER_QUIT:
            return "QUIT";
        default:
            exit(1);
    }
}

MSG* init_msg(char* opercode, char* context, int context_size) {
    return NULL;
}

char* serialization(MSG* msg) {
    char* buf = (char*) malloc(sizeof(char) * MAXBUF);
    sscanf(buf, "%s %s", get_op(msg), msg->context);
    return buf;
}

MSG* deserialization(char* s) {
    return NULL;
}



