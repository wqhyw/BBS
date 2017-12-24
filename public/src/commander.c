//
// Created by leo on 2017/12/17.
//

#include "commander.h"

static char INPUT_BUFFER[MAX_BUF_LEN];                            //input buffer
static MSG* INPUT_MSG;                                            //msg in input buffer

int check_input() {
    INPUT_MSG = parse_msg(INPUT_BUFFER, MAX_BUF_LEN);

    if(INPUT_MSG != NULL && INPUT_MSG->opercode != -1) {
        return 1;
    }

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

        if (c != '\n' && count < MAX_BUF_LEN) {
            INPUT_BUFFER[count++] = c;
        }

        if (c == '\n' && count < MAX_BUF_LEN) {
            INPUT_BUFFER[count] = '\0';
            if(check_input()) {
                return count;
            } else {
                printf("INPUT MUST BE LIKE THIS FORMATE:\n");
                printf("    COMMAND [CONTEXT]\n");
                printf("COMMANDS (COMMAND IN LOWER CASE IS FINE):\n");
                printf("\tREGISTER [YOUR NAME]\n\tLOGIN\n\tSEND [A MESSAGE]\n\tLOGOUT\n\tQUIT\n");
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


void commander() {
    while (user_input("command>") != EOF) {
        if(INPUT_MSG->opercode == -1) {
            printf("%s: cammand not define.\n", msg_to_str(INPUT_MSG));
        } else {
            run_cmd(INPUT_MSG);
        }
    }
}
