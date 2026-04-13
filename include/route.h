#ifndef ROUTE_H
#define ROUTE_H

#include <stdbool.h>
#include "http_parser.h"
#include "handlers.h"

#define SUPPORTED_METHODS_SIZE 2

typedef struct {
    char *methods[SUPPORTED_METHODS_SIZE];
    char *path;
    route_handler handler;
} route;

handler_response handle_routes(http_request *http_req);

bool _check_methods(char *required_method, char *methods[SUPPORTED_METHODS_SIZE]);

#endif