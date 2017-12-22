//
// Created by leo on 2017/12/17.
//

#ifndef BBS_COMMAND_PRASER_H
#define BBS_COMMAND_PRASER_H

#include "constants.h"

int user_input(char*);       //fill user input into buffer
int get_token(char**);       //get token from input buffer
int run_cmd(char** args);    //run command got from input
int check_input(char* s);    //check input format
void proc_line();            //deal user input line


void commander();                   //main loop



#endif //BBS_COMMAND_PRASER_H
