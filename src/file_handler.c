#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file_handler.h"
#include "handlers.h"


handler_response file_handler(char *file_path) {
    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "public%s", file_path);

    char *resolved_path = realpath(full_path, NULL);
    char *public_root = realpath("public", NULL);

    if (!resolved_path || !public_root) {
        free(resolved_path);
        free(public_root);
        return (handler_response) {404, strdup("Not Found"), 9, "text/plain"};
    }

    printf("%s\n", resolved_path);

    if (strncmp(resolved_path, public_root, strlen(public_root)) != 0) {
        free(resolved_path);
        free(public_root);
        return (handler_response) {403, strdup("Forbidden"), 9, "text/plain"};
    }

    long size = 0;
    char *buffer = load_content(resolved_path, &size);
    if (!buffer) {
        free(resolved_path);
        free(public_root);
        return (handler_response) {500, strdup("Internal Server Error"), 21, "text/plain"};
    }

    free(resolved_path);
    free(public_root);

    return (handler_response) {200, buffer, size, "text/html"};
}


char *load_content(char *file_path, long *size_out) {
    FILE *content = fopen(file_path, "rb");
    if (!content) {
        printf("Failed to open file.");
        return NULL;
    }

    fseek(content, 0L, SEEK_END);
    long file_size = ftell(content);
    rewind(content);

    char *buffer = malloc(file_size);

    if (!buffer) {
        fclose(content);
        return NULL;
    }

    fread(buffer, 1, file_size, content);
    *size_out = file_size;

    fclose(content);
    return buffer;
}