//
// Created by leo on 2017/12/17.
//

#include "commander.h"

static char INPUT_BUFFER[MAX_BUF_LEN];                            //input buffer
static MSG *INPUT_MSG;                                            //msg in input buffer

int check_input() {
    INPUT_MSG = parse_msg(INPUT_BUFFER, MAX_BUF_LEN);

    if (INPUT_MSG != NULL && INPUT_MSG->opercode != -1) {
        return 1;
    }

    return 0;
}

int user_input(char *buf, const char *prompt) {
    char c;
    int count;

    printf("%s ", prompt);

    for (count = 0;;) {
        if ((c = (char) getchar()) == EOF) {
            return EOF;
        }

        if (c != '\n' && count < MAX_BUF_LEN) {
            buf[count++] = c;
        }

        if (c == '\n' && count < MAX_BUF_LEN) {
            buf[count] = '\0';
            if (check_input()) {
                return count;
            } else {
                LOG(INFO_LOG, "INPUT MUST BE LIKE THIS FORMATE:");
                LOG(INFO_LOG, "\tCOMMAND [CONTEXT]");
                LOG(INFO_LOG, "COMMANDS (COMMAND IN LOWER CASE IS FINE):");
                LOG(INFO_LOG, "\tREGISTER [YOUR NAME]");
                LOG(INFO_LOG, "\tLOGIN");
                LOG(INFO_LOG, "\tSEND [A MESSAGE]");
                LOG(INFO_LOG, "\tLOGOUT");
                LOG(INFO_LOG, "\tQUIT");

                count = 0;

                LOG(INFO_LOG, prompt);

                continue;
            }
        }

        //input too long, re-input
        if (c == '\n') {
            LOG(ERROR_LOG, "input line is too long!!!!");
            count = 0;
            LOG(INFO_LOG, prompt);
        }
    }
}


void commander() {
    char buf[MAX_BUF_LEN];

    while (user_input(INPUT_BUFFER, "command>") != EOF) {
        if (INPUT_MSG->opercode == -1) {
            sprintf(buf, "%s: cammand not define.", msg_to_str(INPUT_MSG));
            LOG(INFO_LOG, buf);
        } else {
            run_cmd(INPUT_MSG);
        }
    }
}
