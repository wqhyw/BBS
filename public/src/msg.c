//
// Created by leo on 2017/11/30.
//

#include "msg.h"

MSG* init_msg(int opercode, const char* context, int context_size) {
    MSG* msg = (MSG*) malloc(sizeof(MSG));

    msg->opercode = opercode;
    msg->context = (char*) malloc(sizeof(char) * context_size);
    msg->context_size = context_size;

    char* p = msg->context;
    for (int i = 0; i < context_size; i++) {
        *p++ = context[i];
    }

    *p = '\0';

    return msg;
}

char* msg_to_str(MSG* msg) {
    char* buf = (char*) malloc(sizeof(char) * msg->context_size);
    sprintf(buf, "%s %s", get_op_str(msg->opercode), msg->context);

    return buf;
}

MSG* parse_msg(const char* s, int size) {
    MSG* msg = (MSG*) malloc(sizeof(MSG));

    char* opstr = (char*) malloc(sizeof(opstr) * MAX_ARG_LEN);
    char* context = (char*) malloc(sizeof(opstr) * MAX_BUF_LEN);

    char* p_opstr = opstr;
    char* p_context = context;

    int is_blank_ignore = 1;
    int is_fuc_flag = 1;
    int i = 0, count = 0;

    for (; i < size; i++) {
        if (is_blank_ignore && (s[i] == ' ' || s[i] == '\t')) { //ignore blank of beginning
            continue;
        } else if (is_fuc_flag) { //read operstr
            if (is_blank_ignore) {
                is_blank_ignore = 0;
            }

            if ((s[i] == ' ' || s[i] == '\t')) {
                *p_opstr = '\0';
                is_fuc_flag = 0;
            } else if (s[i] == '\0') {
                *p_opstr = '\0';
                *p_context = '\0';
                break;
            } else {
                *p_opstr++ = s[i];
            }

        } else { //read context
            if (s[i] != '\0') {
                *p_context++ = s[i];
                count++;
            } else {
                *p_context = '\0';
                break;
            }
        }
    }

    if (*p_context != '\0' || *p_opstr != '\0') {
        return NULL;
    }

    int op_code = get_op_code(opstr, size);

    if (op_code != -1) {
        msg->opercode = op_code;
    } else {
        return NULL;
    }

    msg->context = context;
    msg->context_size = count + 1;

    return msg;
}



