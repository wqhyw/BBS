//
// Created by leo on 2017/11/30.
//

#ifndef BBS_MSG_H
#define BBS_MSG_H

#include "utils.h"

/**Message Definition**/
typedef struct {
    int opercode;
    char* context;
    int context_size;
} MSG;


MSG* init_msg(int, const char*, int);   //initialization
MSG* parse_msg(const char*, int);            //parse MSG from str

char* msg_to_str(MSG*);


#endif //BBS_MSG_H
