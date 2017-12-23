//
// Created by leo on 2017/12/22.
//

#ifndef BBS_UTILS_H
#define BBS_UTILS_H

#include <string.h>
#include "constants.h"


char* get_op_str(int);                     //got operation str from opercode
int get_op_code(const char*, int);         //got opercode from operstr

char* upper(const char*, int);             //uppercase str

#endif //BBS_UTILS_H
