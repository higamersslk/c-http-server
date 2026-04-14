# C http server
## About
This project is a minimal HTTP server writen in C. 
it handles incoming TCP connections, parsers HTTP request, routes them and servers static files
from a `public/` directory.

It was built for learning purposes, focusing on low level programing and how HTTP servers work.

## Features
- Basic HTTP request parsing
- Routing system for endpoints
- File serving (`public/` folder)
- Simple MIME type detection (html, css, png, jpeg)
- Status code:
    - 200 OK
    - 403 Forbidden
    - 404 Not Found
    - 500 Internal Server Error
- Simple multi-process handling using fork()
- Basic protection against directory traversal

## Build and Run
Requires cmake for quick building.

```bash

cmake . && build/server

```

Default PORT is defined in `include/server.h` 8080.
Open on browser `https://localhost:8080/`

## Routing
Routes are defined in `src/route.c`:
```c
route routes[] = {
    {{"GET"}, "/", route_index}
};
```
**route** is a struct defined in `include/route.h`:
```c
typedef struct {
    char *methods[SUPPORTED_METHODS_SIZE]; // SUPPORTED_METHODS_SIZE = 2
    char *path;
    route_handler handler;
} route;
```
**route_handler** is a function that takes **http_request** as parameter and returns a **handler_response**.<br>
**handler_response** is a struct defined in `include/handlers.h`:
```c
typedef struct {
    int status_code;
    char *body;
    unsigned int content_size;
    const char *content_type;
} handler_response;
```
ANd handlers are defined in `src/handlers.c`.

## HTTP handling
Request parsing:
  - method
  - path
  - version
  - header

Response format:
```
HTTP/1.1 <status> <message>
Content-Type: <type>
Content-Length: <size>

<body>
```

## Limitations
- Only support GET method (possible to expand)
- No persistent connection (keep-alive)
- No advanced routing (params, etc)
- No multithreading
- No HTTPS
---
Made by me
