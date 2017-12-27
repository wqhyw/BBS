//
// Created by leo on 2017/12/22.
//

#include "handler.h"

int main() {
    recv_loop(SERVER_IP, SERVER_PORT, server_msg_handle);
}

