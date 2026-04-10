#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"


bool setup_server(int port, int *server_fd) {
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(port)
    };

    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*server_fd < 0) return false;

    int bind_result = bind(*server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if (bind_result < 0) return false;

    return true;
}


void listen_clients(int server_fd) {
    printf("Listening for clients.\n");
    listen(server_fd, 5);

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &addr_len);

        if (client_fd < 0) continue;

        int pid = fork();
        if (pid < 0) continue;

        if (pid == 0) {
            read_message(client_fd);
            close(client_fd);
            exit(0);
        } else {
            close(client_fd);
        }
    }
}


void read_message(int client_fd) {
    char buffer[BUFFER_LEN] = {0};
    ssize_t bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes > 0) buffer[bytes] = '\0';

    //temp, move to http reader.
    printf("%s\n", buffer);
    char message[BUFFER_LEN] = "Hello there";
    write(client_fd, message, sizeof(message));
}
