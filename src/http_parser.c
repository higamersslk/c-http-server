#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "http_parser.h"


http_request* http_parser(char *raw) {
    char *line = strtok(raw, "\r\n");
    if (!line) return NULL;

    http_request *req = malloc(sizeof(http_request));
    sscanf(line, "%s %s %s", req->method, req->path, req->version);

    req->header_count = 0;

    char *header = line;

    while((header = strtok(NULL, "\r\n")) != NULL) {
        if(strcmp(header, "") == 0) break;

        char *column = strchr(header, ':');
        if (!column) continue;

        *column = '\0';

        strcpy(req->headers[req->header_count].key, header);
        strcpy(req->headers[req->header_count].value, column + 2);
        
        req->header_count++;
    }

    return req;
}