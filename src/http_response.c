#include <stdio.h>
#include <string.h>

#include "route.h"


char *build_response(route_response res) {
    static char response[1024];

    int content_length = strlen(res.body);

    snprintf(
        response,
        sizeof(response),
        "HTTP/1.1 %i %s\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %i\r\n"
        "\r\n"
        "%s",
        res.status_code, res.body, content_length, res.body
    );

    return response;
}