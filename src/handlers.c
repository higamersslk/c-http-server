#include <string.h>

#include "handlers.h"


handler_response route_index(http_request *http_req) {
    if (strcmp(http_req->method, "GET") == 0) {
        return (handler_response) {200, "OK"};
    }

    return (handler_response) {404, "Not Found"};
}