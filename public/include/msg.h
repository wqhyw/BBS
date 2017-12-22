//
// Created by leo on 2017/11/30.
//

#ifndef BBS_MSG_H
#define BBS_MSG_H

#include "constants.h"

/**Message Definition**/
typedef struct {
    int opercode;
    char* context;
} MSG;


MSG* init_msg(char*, char*, int);
char* get_op(MSG*);

char* to_str(MSG*);


#endif //BBS_MSG_H
