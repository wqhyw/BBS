//
// Created by leo on 2017/12/25.
//

#ifndef BBS_UI_H
#define BBS_UI_H

#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include "commander.h"

WINDOW *create_newwin(int, int, int, int);

void destroy_win(WINDOW *);

void draw();

void quit();

#endif //BBS_UI_H
