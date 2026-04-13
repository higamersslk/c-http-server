#ifndef HANDLERS_H
#define HANDLERS_H

#include "http_parser.h"

typedef struct {
    int status_code;
    const char *body;
} handler_response;

typedef handler_response (*route_handler)(http_request *http_req);

handler_response route_index(http_request *http_req);

#endif