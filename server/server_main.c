//
// Created by leo on 2017/12/22.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define PORT 54321

struct sockaddr_in init_addr(const char* ip_add, int port) {
    struct sockaddr_in ret;

    ret.sin_family = AF_INET;
    ret.sin_port = htons(port);
    ret.sin_addr.s_addr = inet_addr(ip_add);

    bzero(&ret.sin_zero, 8);

    return ret;
}

void checked(int ret, const char* prompt) {
    if(ret == -1) {
        printf("%s error, %s (errno: %d)\n", prompt, strerror(errno), errno);
        exit(1);
    }

}

int main() {
    int client_fd;
    int server_fd;
    int opt = 1;
    int len = sizeof(opt);

    ssize_t send_count;

    checked(server_fd = socket(AF_INET, SOCK_STREAM, 0), "socket");
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, (socklen_t) &len);

    printf("new server cokect.\n");

    struct sockaddr_in my_addr = init_addr("127.0.0.1", PORT);
    struct sockaddr_in their_addr;

    checked(bind(server_fd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr)) == -1, "bind");
    printf("binded.\n");

    checked(listen(server_fd, 10) == -1, "listen");
    printf("listening.\n");

    while(1) {
        char buf[1024];

        socklen_t sin_size = sizeof(struct sockaddr_in);

        checked(client_fd = accept(server_fd, (struct sockaddr*)&their_addr, &sin_size), "accept");
        printf("accepted client %s:%d.\n", inet_ntoa(their_addr.sin_addr), their_addr.sin_port);

        if(recv(client_fd, buf, 1024, 0) > 0) {

            close(client_fd);
            printf("recv '%s'\n", buf);


            if(!strncmp(buf, "QUIT", 1024)) {
                printf("do quit.\n");
                break;
            }

        } else {
            close(server_fd);
            exit(1);
        }

        memset((void *)&buf, 0, 1024);
        printf("\nready for next.\n");
    }

    close(server_fd);

    return 0;
}
