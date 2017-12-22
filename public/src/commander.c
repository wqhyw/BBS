//
// Created by leo on 2017/12/17.
//

#include "../include/commander.h"

static char in_buf[MAXBUF];                                     //input buffer
static char* ptr = in_buf;                                      //input buffer ptr
static int fuc_tok_flag = 1;                                    //input buffer ptr

int check_input(char* const s) {
    int p = 0;
    //ignore begining blank chars
    while (s[p] == ' ' || s[p] == '\t') {
        p++;
    }

    for(int i = p; i < MAXARG; i++) {
        if(s[i] == ' ') {
            return 1;
        }
    }

    return 0;
}

int user_input(char* prompt) {
    char c;
    int count;

    printf("%s ", prompt);

    for (count = 0;;) {
        if ((c = (char) getchar()) == EOF) {
            return EOF;
        }

        if (count < MAXBUF) {
            in_buf[count++] = c;
        }


        if (c == '\n' && count < MAXBUF) {
            in_buf[count] = '\0';
            if(check_input(in_buf)) {
                return count;
            } else {
                printf("input must be in this format:\n");
                printf("    COMMAND CONTEXT\n");
                printf("example:\n");
                printf("    send I am a pig.\n");
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

int get_token(char** outptr) {
    //token type
    int type;

    //token buffer
    char* tokbuf = (char*) malloc(sizeof(char) * (MAXBUF + 1));
    char* tok = tokbuf;

    //ignore begining blank chars
    while (*ptr == ' ' || *ptr == '\t') {
        ptr++;
    }

    //obtain one token
    *tok++ = *ptr;
    switch (*ptr++) {
        case '\n':
            type = EOL;
            break;
        default:
            type = VCR;
            while ((fuc_tok_flag && *ptr != ' ') || (!fuc_tok_flag && *ptr != '\0' && *ptr != '\n')) {
                *tok++ = *ptr++;
            }

            fuc_tok_flag = 0;
            //add '\0' to end of token string
            *tok++ = '\0';
    }

    //return token buffer
    *outptr = tokbuf;

    return type;
}

int run_cmd(char** args) {
    for (char** x = args; *x != NULL; x++) {
        printf("%s\n", *x);
    }

    return 0;
}

void proc_line() {
    char* arg[MAXARG + 1];
    int narg;

    for (narg = 0;;) {
        switch (get_token(arg + narg)) {
            case VCR:
                if (narg < MAXARG)
                    narg++;
                break;
            case EOL:
                if (narg != 0) {
                    arg[narg] = NULL;

                    run_cmd(arg); // 亦可改造为消息序列化

                    //reset input buffer ptr and fuc_tok_flag
                    ptr = in_buf;
                    memset((void*) ptr, '\0', MAXBUF * sizeof(char));
                    fuc_tok_flag = 1;
                }
                return;
            default:
                break;
        }
    }
}


void commander() {
    while (user_input("command>") != EOF) {
        proc_line();
    }
}


