//
// Created by leo on 2017/12/17.
//

#ifndef BBS_COMMANDER_H
#define BBS_COMMANDER_H

#include "constants.h"
#include "public.h"

int user_input(char *, const char *);      //fill user input into buffer
int check_input();                      //checkand parse input

void commander();                       //main loop

#endif //BBS_COMMANDER_H
