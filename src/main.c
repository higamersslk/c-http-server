#include <stdio.h>
#include <unistd.h>

#include "server.h"


int main(void) {
    printf("starting server...\n");

    int server_fd = -1;
    if(!setup_server(PORT, &server_fd)) {
        printf("failed to create server.");
        return 1;
    }

    printf("listening to clients...\n");
    listen_clients(server_fd);
    
    printf("closing server...\n");
    close(server_fd);
    return 0;
}