#ifndef ROUTE_H
#define ROUTE_H

#include <stdbool.h>
#include "http_parser.h"

#define SUPPORTED_METHODS_SIZE 2


typedef struct {
    int status_code;
    const char *body;
} route_response;

typedef route_response (*route_handler)(http_request *http_req);

typedef struct {
    char *methods[SUPPORTED_METHODS_SIZE];
    char *path;
    route_handler handler;
} route;

route_response handle_routes(http_request *http_req);
route_response route_index(http_request *http_req);

bool _check_methods(char *required_method, char *methods[SUPPORTED_METHODS_SIZE]);

#endif