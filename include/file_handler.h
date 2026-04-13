#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "handlers.h"


handler_response file_handler(char *file_path);
char *load_content(char *file_path, long *size_out);

#endif