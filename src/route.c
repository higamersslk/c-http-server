#include <string.h>
#include "route.h"


route routes[] = {
    {{"GET"}, "/", route_index}
};

const int routes_count = 1;


route_response handle_routes(http_request *http_req) {
    for (int i = 0; i < routes_count; i++) {
        if (!_check_methods(http_req->method,routes[i].methods)) continue;
        if (strcmp(http_req->path, routes[i].path) != 0) continue;

        return routes[i].handler(http_req);
    }

    return (route_response){404, "Not found"};
}


route_response route_index(http_request *http_req) {
    if (strcmp(http_req->method, "GET") == 0) {
        return (route_response) {200, "OK"};
    }

    return (route_response) {404, "Not Found"};
}


bool _check_methods(char *required_method, char *methods[SUPPORTED_METHODS_SIZE]) {
    for (int i = 0; i < SUPPORTED_METHODS_SIZE; i++) {
        char *method_type = methods[i];
        if (!method_type) break;

        if (strcmp(method_type, required_method) == 0) {
            return true;
        }
    }

    return false;
}