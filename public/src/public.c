//
// Created by leo on 2017/12/22.
//


#include "public.h"

/***************************Msg Definitons***************************/
MSG *init_msg(int opercode, const char *context, int context_size) {
    MSG *msg = (MSG *) malloc(sizeof(MSG));

    msg->opercode = opercode;
    msg->context = (char *) malloc(sizeof(char) * context_size);
    msg->context_size = context_size + 1;

    char *p = msg->context;
    for (int i = 0; i < context_size; i++) {
        *p++ = context[i];
    }

    *p = '\0';

    return msg;
}

char *msg_to_str(MSG *msg) {
    if (msg != NULL) {
        char *buf = (char *) malloc(sizeof(char) * msg->context_size);
        sprintf(buf, "%s%c%s", get_op_str(msg->opercode), (msg->context[0] == '\0') ? '\0' : ' ', msg->context);

        return buf;
    }

    return "";
}

MSG *parse_msg(const char *s, int size) {
    MSG *msg = (MSG *) malloc(sizeof(MSG));

    char *opstr = (char *) malloc(sizeof(opstr) * MAX_ARG_LEN);
    char *context = (char *) malloc(sizeof(opstr) * MAX_BUF_LEN);

    char *p_opstr = opstr;
    char *p_context = context;

    int is_blank_ignore = 1;
    int is_fuc_flag = 1;
    int i = 0, count = 0;

    for (; i < size; i++) {
        if (is_blank_ignore && (s[i] == ' ' || s[i] == '\t')) { //ignore blank of beginning
            continue;
        } else if (is_fuc_flag) { //read operstr
            if (is_blank_ignore) {
                is_blank_ignore = 0;
            }

            if ((s[i] == ' ' || s[i] == '\t')) {
                *p_opstr = '\0';
                is_fuc_flag = 0;
            } else if (s[i] == '\0') {
                *p_opstr = '\0';
                *p_context = '\0';
                break;
            } else {
                *p_opstr++ = s[i];
            }

        } else { //read context
            if (s[i] != '\0') {
                *p_context++ = s[i];
                count++;
            } else {
                *p_context = '\0';
                break;
            }
        }
    }

    if (*p_context != '\0' || *p_opstr != '\0') {
        return NULL;
    }

    int op_code = get_op_code(opstr, size);

    msg->opercode = op_code;
    msg->context = context;
    msg->context_size = count + 1;

    return msg;
}

/*******************************************************************/

char *get_op_str(int opercode) {
    switch (opercode) {
        case OPER_REGISTER:
            return "REGISTER";
        case OPER_LOGIN:
            return "LOGIN";
        case OPER_SEND:
            return "SEND";
        case OPER_LOGOUT:
            return "LOGOUT";
        case OPER_QUIT:
            return "QUIT";
        default:
            return "";
    }
}

int get_op_code(const char *operstr, int size) {
    // make operstr upper case
    char *operstr_big = upper(operstr, size);

    if (!strncmp(operstr_big, "REGISTER", (size_t) size)) {
        return OPER_REGISTER;
    } else if (!strncmp(operstr_big, "LOGIN", (size_t) size)) {
        return OPER_LOGIN;
    } else if (!strncmp(operstr_big, "SEND", (size_t) size)) {
        return OPER_SEND;
    } else if (!strncmp(operstr_big, "LOGOUT", (size_t) size)) {
        return OPER_LOGOUT;
    } else if (!strncmp(operstr_big, "QUIT", (size_t) size)) {
        return OPER_QUIT;
    } else {
        return -1;
    }
}

char *upper(const char *s, int size) {
    char *ret = (char *) malloc(sizeof(char) * size);
    char *p = ret;

    for (int i = 0; i < size; i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            *p++ = (char) (s[i] - 32);
        } else if (s[i] == '\0') {
            break;
        } else {
            *p++ = s[i];
        };
    }

    *p = '\0';

    return ret;
}

void ret_checker(int ret, const char *prompt) {
    char buf[MAX_BUF_LEN];

    if (ret == -1) {
        sprintf(buf, "%s error. errmsg[%s], errno[%d].\n", prompt, strerror(errno), errno);
        LOG(buf);
        exit(errno);
    }
}

struct sockaddr_in init_addr(const char *ip_add, int port) {
    struct sockaddr_in ret;

    ret.sin_family = AF_INET;
    ret.sin_port = htons(port);
    ret.sin_addr.s_addr = inet_addr(ip_add);

    bzero(&ret.sin_zero, 8);

    return ret;
}

int async_sender(MSG *msg, const char *dest_ip, int dest_port) {
    int server_fd;

    struct sockaddr_in server_add = init_addr(dest_ip, dest_port);

    ret_checker(
            server_fd = socket(AF_INET, SOCK_STREAM, 0),
            "Create Socket"
    );

    ret_checker(
            connect(server_fd, (struct sockaddr *) &server_add, sizeof(struct sockaddr)),
            "Connect server"
    );

    char *msg_str = msg_to_str(msg);

    char buf[MAX_BUF_LEN];

    ssize_t send_count = send(server_fd, msg_str, strlen(msg_str), 0);
    sprintf(buf, "sended [len=%d] [message='%s']\n", (int) send_count, msg_str);
    LOG(buf);

    close(server_fd);

    return (int) send_count;
}

int async_recver(const char *local_ip, int local_port, char *buf) {
    int server_fd;
    int client_fd;

    buf = (char *) malloc(sizeof(char) * MAX_BUF_LEN);

    struct sockaddr_in server_add = init_addr(local_ip, local_port);
    struct sockaddr_in client_add;

    ret_checker(
            server_fd = socket(AF_INET, SOCK_STREAM, 0),
            "socket"
    );

    //server socket setting
    int opt = 1;
    int len = sizeof(opt);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, (socklen_t) len);

    ret_checker(
            bind(server_fd, (struct sockaddr *) &server_add, sizeof(struct sockaddr)),
            "bind"
    );

    ret_checker(
            listen(server_fd, 5),
            "listen"
    );

    socklen_t sin_size = sizeof(struct sockaddr);
    ret_checker(
            client_fd = accept(server_fd, (struct sockaddr *) &client_add, &sin_size),
            "accept"
    );

    ssize_t recv_size = recv(client_fd, buf, MAX_BUF_LEN, 0);

    close(client_fd);
    close(server_fd);

    return (int) recv_size;
}
