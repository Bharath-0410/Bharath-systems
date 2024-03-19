#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_handler(int sig) {
    //printf("[%ld] Parent process got Caught SIGINT!\n", (long)getpid());
    if (sig == SIGINT) {
        printf("Caught SIGINT, exiting now\n");
    }
}

void sigtstp_handler(int sig) {
    if (sig == SIGTSTP) {
        printf("Caught SIGTSTP, stopping now\n");
    }
}


int main(int argc, char **argv) {
    pid_t child_pid;
    int status;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    child_pid = fork();
    if (child_pid == 0) { 
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(-1);
    } else if (child_pid > 0) { 
        printf("Wait for the child process to terminate\n");
        signal(SIGINT, sigint_handler); 
        signal(SIGTSTP, sigtstp_handler); 
        wait(&status); 
        for (;;) {
            pause();
        }
    } else { 
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    printf("[%ld]: Exiting program .....\n", (long)getpid());

    return 0;
}