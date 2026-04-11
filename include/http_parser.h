#ifndef HTTP_PARSER
#define HTTP_PARSER

typedef struct {
    char key[32];
    char value[256];
} http_header;

typedef struct {
    char method[8];
    char path[256];
    char version[16];

    http_header headers[32];
    int header_count;
} http_request;

http_request* http_parser(char *raw);

#endif