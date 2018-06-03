#include <stdio.h>
#include <uv.h>
#include <string>
#include <iostream>

uv_loop_t *loop;
uv_process_t child_req;
uv_process_options_t options;

void on_exit(uv_process_t *req, int64_t exit_status, int term_signal) {
    std::cout << "finish child process" << std::endl;
}


int main() {
    loop = uv_default_loop();


    std::string command = "mkdir";
    std::string folder = "/tmp/simple_swap_child_process";

    char* args[3];
    args[0] = const_cast<char*>(command.c_str());
    args[1] = const_cast<char*>(folder.c_str());
    args[2] = NULL;



    options.exit_cb = &on_exit;
    options.file = const_cast<char*>(command.c_str());
    options.args = args;

    int r;
    if ((r = uv_spawn(loop, &child_req, &options))) {
        fprintf(stderr, "%s\n", uv_strerror(r));
        return 1;
    } else {
        fprintf(stderr, "Launched process with ID %d\n", child_req.pid);
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}