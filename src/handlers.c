#include <string.h>

#include "handlers.h"
#include "file_handler.h"

handler_response route_index(http_request *http_req) {
    if (strcmp(http_req->method, "GET") == 0) {
        return file_handler("/index.html");
    }

    return (handler_response) {403, strdup("Internal Server Error"), 21 ,"text/plain"};
}