#include <unistd.h>
#include "server.h"


int main(void) {
    int server_fd = -1;
    if(!setup_server(PORT, &server_fd)) return 1;
    
    listen_clients(server_fd);
    
    close(server_fd);
    return 0;
}