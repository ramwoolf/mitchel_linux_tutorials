#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

sig_atomic_t child_exit_status = 1;

void cleanup_child_process(int signal_number) {
    int status;
    wait(&status);
    child_exit_status = status;
}

int spawn(char* program, char** arg_list) {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid != 0) {
        sleep(60);
        return child_pid;
    }
    else {
        execvp(program, arg_list);
    }
    fprintf(stderr, "an error occured in execvp\n");
    abort();
}

int main(int argc, char const *argv[])
{
    printf("%d\n", (int)child_exit_status);
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &cleanup_child_process;
    sigaction(SIGCHLD, &sa, NULL);

    int child_status;
    char * arg_list[] = {
        "ls", "-la", "/home/ramwoolf/Projects/mitchel_linux_tutorials", NULL
    };

    spawn("ls", arg_list);

    printf("Done with main program\n");
    printf("%d\n", (int)child_exit_status);

    return 0;
}
