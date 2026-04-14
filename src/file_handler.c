#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "file_handler.h"
#include "handlers.h"


handler_response file_handler(char *file_path) {
    char full_path[PATH_MAX];
    char *resolved_path = NULL;
    char *public_root = NULL;
    char *buffer = NULL;

    handler_response res = (handler_response) {500, strdup("Internal Server Error"), 21, "text/plain"};
    snprintf(full_path, sizeof(full_path), "public%s", file_path);

    resolved_path = realpath(full_path, NULL);
    public_root = realpath("public", NULL);

    if (!resolved_path || !public_root) {
        res = (handler_response) {404, strdup("Not Found"), 9, "text/plain"};
        goto cleanup;
    }

    if (strncmp(resolved_path, public_root, strlen(public_root)) != 0) {
        res = (handler_response) {403, strdup("Forbidden"), 9, "text/plain"};
        goto cleanup;
    }

    if (is_directory(resolved_path)) {
        char index_path[PATH_MAX];
        snprintf(index_path, sizeof(index_path), "%s/index.html", resolved_path);
        
        free(resolved_path);
        resolved_path = realpath(index_path, NULL);

        if(!resolved_path) {
            res = (handler_response) {404, strdup("Not Found"), 9, "text/plain"};
            goto cleanup;
        }
    }

    long size_out = 0;
    buffer = load_content(resolved_path, &size_out);
    if (!buffer) {
        res = (handler_response) {500, strdup("Internal Server Error"), 21, "text/plain"};
        goto cleanup;
    }

    res = (handler_response) {200, buffer, size_out, get_mime_type(resolved_path)};
    buffer = NULL;

    cleanup:
        free(resolved_path);
        free(public_root);
        free(buffer);

        return res;
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


char *get_mime_type(char* path) {
    char *extension = strrchr(path, '.');

    if (!extension) return "application/octet-stream";

    if(strcmp(extension, ".html") == 0) return "text/html";
    if(strcmp(extension, ".css") == 0) return "text/css";
    if(strcmp(extension, ".png") == 0) return "image/png";
    if(strcmp(extension, ".jpeg") == 0) return "image/jpeg";

    return "application/octet-stream";
}


int is_directory(char *path) {
    struct stat buffer;
    if(stat(path, &buffer) != 0) return 0;
    return S_ISDIR(buffer.st_mode);
}