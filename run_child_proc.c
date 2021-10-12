#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int spawn(char* program, char** arg_list) {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid != 0) {
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
    int child_status;
    char * arg_list[] = {
        "ls", "-la", "/", NULL
    };

    spawn("ls", arg_list);

    wait(&child_status);

    if (WIFEXITED(child_status)) {
        printf("The child process exited normally with code %d\n", WEXITSTATUS(child_status));
    }
    else {
        printf("Child process exited abnormally with signal %d\n", WTERMSIG(child_status));
    }

    printf("Done with main program\n");

    return 0;
}
