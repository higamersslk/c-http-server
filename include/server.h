#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>
#include "handlers.h"

#define PORT 8080
#define BUFFER_LEN 1024

bool setup_server(int port, int *server_fd);
void listen_clients(int server_fd);
void handle_client(int client_fd);
void send_response(int client_fd, handler_response response);

#endif