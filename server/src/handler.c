//
// Created by leo on 2017/12/26.
//

#include "handler.h"

void fake_server() {
    int client_fd;
    int server_fd;
    int opt = 1;
    int len = sizeof(opt);
    char buffer[MAX_BUF_LEN];

    ret_checker(
            server_fd = socket(AF_INET, SOCK_STREAM, 0),
            "socket");

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, (socklen_t) len);

    LOG("new server cokect.\n");

    struct sockaddr_in my_addr = init_addr("127.0.0.1", SERVER_PORT);
    struct sockaddr_in their_addr;

    ret_checker(
            bind(server_fd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr)) == -1,
            "bind");

    LOG("binded.\n");

    ret_checker(
            listen(server_fd, 10) == -1,
            "listen");

    LOG("listening.\n");

    while(1) {
        char buf[1024];

        socklen_t sin_size = sizeof(struct sockaddr_in);

        ret_checker(
                client_fd = accept(server_fd, (struct sockaddr*)&their_addr, &sin_size),
                "accept");


        sprintf(buffer, "accepted client %s:%d.\n", inet_ntoa(their_addr.sin_addr), their_addr.sin_port);
        LOG(buffer);

        if(recv(client_fd, buf, 1024, 0) > 0) {

            close(client_fd);

            sprintf(buffer, "recv '%s'\n", buf);
            LOG(buffer);

            if(!strncmp(buf, "QUIT", 1024)) {
                LOG("do quit.\n");
                break;
            }

        } else {
            close(server_fd);
            exit(1);
        }

        memset((void *)&buf, 0, 1024);
        LOG("\nready for next.\n");
    }

    close(server_fd);
}

void LOG(const char* s) {
    printf("%s", s);
}

