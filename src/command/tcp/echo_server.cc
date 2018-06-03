#include <stdio.h>
#include <stdlib.h>
#include <uv.h>


void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}

int main() {
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);


    sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 3333, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);

    int r = uv_listen((uv_stream_t*) &server, 2, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}