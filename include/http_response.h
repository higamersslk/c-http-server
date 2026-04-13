#ifndef HTTP_RESPONSE
#define HTTP_RESPONSE

#include "handlers.h"

char *build_header(handler_response res);
char *build_error_code(int code);

#endif