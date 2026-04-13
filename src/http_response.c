#include <stdio.h>

#include "http_response.h"


char *build_header(handler_response res) {
    static char header[1024];
    snprintf(
        header,
        sizeof(header),
        "HTTP/1.1 %i %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %i\r\n"
        "\r\n",
        res.status_code, build_error_code(res.status_code),
        res.content_type, res.content_size
    );

    return header;
}

char *build_error_code(int code) {
    switch (code) {
        case 200: return "OK";
        case 404: return "Not Found";
        case 403: return "Forbidden";
        case 500: return "Internal Server Error";
        default: return "Internal Server Error";
    }
}