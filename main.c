#include "msg.h"

int main() {
//    MSG* msg = init_msg(OPER_SEND, "I am msg body.", 15);
    MSG* msg = parse_msg("   SE ND   ", 30);

    if(msg == NULL) {
        printf("ERROR CMD\n");
    } else {
        printf("%s\n", msg_to_str(msg));
    }
    
    return 0;
}