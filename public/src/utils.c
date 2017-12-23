//
// Created by leo on 2017/12/22.
//


#include "utils.h"

char* get_op_str(int opercode) {
    switch (opercode) {
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
            return "NOT_A_COMMAND";
    }
}

int get_op_code(const char* operstr, int size) {
    // make operstr upper case
    char* operstr_big = upper(operstr, size);

    if(!strncmp(operstr_big, "REGISTER", (size_t) size)) {
        return OPER_REGISTER;
    } else if(!strncmp(operstr_big, "LOGIN", (size_t) size)) {
        return OPER_LOGIN;
    } else if(!strncmp(operstr_big, "SEND", (size_t) size)) {
        return OPER_SEND;
    } else if(!strncmp(operstr_big, "LOGOUT", (size_t) size)) {
        return OPER_LOGOUT;
    } else if(!strncmp(operstr_big, "QUIT", (size_t) size)) {
        return OPER_QUIT;
    } else {
        return -1;
    }
}

char* upper(const char* s, int size) {
    char* ret = (char *) malloc(sizeof(char) * size);
    char* p = ret;

    for(int i = 0; i < size; i++) {
        if('a' <= s[i] && s[i] <= 'z') {
            *p++ = (char) (s[i] - 35);
        } else if(s[i] == '\0') {
            break;
        } else {
            *p++ = s[i];
        };
    }

    *p = '\0';

    return ret;
}