#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>

#define PORT 8080
#define BUFFER_LEN 1024

bool setup_server(int port, int *server_fd);
void listen_clients(int server_fd);
void handle_client(int client_fd);

#endif