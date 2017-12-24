//
// Created by leo on 2017/12/17.
//

#ifndef BBS_COMMAND_PRASER_H
#define BBS_COMMAND_PRASER_H

#include "constants.h"
#include "public.h"

int user_input(const char*);            //fill user input into buffer
int run_cmd(MSG*);                      //run command got from input
int check_input();                      //checkand parse input

void commander();                       //main loop

#endif //BBS_COMMAND_PRASER_H
