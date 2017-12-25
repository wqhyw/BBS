//
// Created by leo on 2017/12/22.
//

#ifndef BBS_PUBLIC_H
#define BBS_PUBLIC_H

#include "constants.h"

/**Message Definition**/
typedef struct _msg {
    int opercode;
    char *context;
    int context_size;
} MSG;


MSG *init_msg(int, const char *, int);            //initialization
MSG *parse_msg(const char *, int);                //parse MSG from str


/**Utils**/
char *msg_to_str(MSG *);

char *get_op_str(int);                           //got operation str from opercode

int get_op_code(const char *, int);               //got opercode from operstr

char *upper(const char *, int);                   //uppercase str

struct sockaddr_in init_addr(const char *, int);  //init ip addr and port

void ret_checker(int, const char *);              //check status of socket functions

int async_sender(MSG *, const char *, int);

int async_recver(const char *, int, char *);

void LOG(const char *);

#endif //BBS_PUBLIC_H