//
// Created by leo on 2017/12/17.
//

#include "commander.h"

static char in_buf[MAX_BUF_LEN];                                //input buffer
static char* ptr = in_buf;                                      //input buffer ptr

int check_input(const char*  s) {

    return 0;
}

int user_input(const char* prompt) {
    char c;
    int count;

    printf("%s ", prompt);

    for (count = 0;;) {
        if ((c = (char) getchar()) == EOF) {
            return EOF;
        }

        if (count < MAX_BUF_LEN) {
            in_buf[count++] = c;
        }


        if (c == '\n' && count < MAX_BUF_LEN) {
            in_buf[count] = '\0';
            if(check_input(in_buf)) {
                return count;
            } else {
                printf("input must be in this format:\n");
                printf("    COMMAND [CONTEXT]\n");
                printf("COMMANDS:\n");
                printf("    REGISTER\nLOGIN\nSEND\nLOGOUT\nQUIT\n");
                count = 0;
                printf("%s ", prompt);

                continue;
            }
        }

        //input too long, re-input
        if (c == '\n') {
            printf("input line is too long!!!!\n");
            count = 0;
            printf("%s ", prompt);
        }
    }
}

int run_cmd(MSG* msg) {

    return 0;
}

void commander() {
    while (user_input("command>") != EOF) {
        
    }
}


