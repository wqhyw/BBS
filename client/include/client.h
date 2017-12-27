//
// Created by leo on 2017/12/25.
//

#ifndef BBS_UI_H
#define BBS_UI_H

#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "commander.h"
#include "config.h"

#define LISTEN_PORT 55555

WINDOW *create_newwin(int, int, int, int);

void destroy_win(WINDOW *);

void ui();                  //frontend

void listener();            //backgroud

void quit();

#endif //BBS_UI_H
