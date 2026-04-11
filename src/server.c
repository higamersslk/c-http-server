#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "http_parser.h"
#include "http_response.h"


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
    listen(server_fd, 5);

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &addr_len);
        
        if (client_fd < 0) continue;

        printf("estabilished connection with client.\n");

        int pid = fork();
        if (pid < 0) {
            printf("Failed to create a new process.\n");
        }
        
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

    printf("%s\n", buffer);

    http_request *http_req = http_parser(buffer);
    if(!http_req) return;

    char *http_res = build_response(http_req);
    printf("response:\n%s\n", http_res);
    send(client_fd, http_res, strlen(http_res), 0);

    free(http_req);
}
