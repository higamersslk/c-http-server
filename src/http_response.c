#include <string.h>
#include <stdio.h>

#include "http_response.h"


char *build_response(http_request *req) {
    char *version = req->version;
    char *path = req->path;
    static char response[1024];
    char *text = path + 1;
    
    if (strcmp(path, "/") == 0) {
        text = "root";
    }

    snprintf(
        response,
        sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %li\r\n"
        "\r\n"
        "%s",
        strlen(text),
        text
    ); 

    return response;
}