#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 100

int main() {
    char cmd[MAX_CMD_LENGTH];
    FILE *fp;
    char opt[1024];

    while (1) {
        printf("Enter command: ");
        fgets(cmd, sizeof(cmd), stdin);

        // Remove trailing newline
        cmd[strcspn(cmd, "\n")] = '\0';

        // Exit if the user inputs "quit"
        if (strcmp(cmd, "quit") == 0) {
            printf("Exiting program...bye!\n");
            break;
        }

        // Execute the command using popen
        fp = popen(cmd, "r");
        if (fp == NULL) {
            printf("Error executing command\n");
            continue;
        }

        // Read the output of the command and display it to the terminal
        while (fgets(opt, sizeof(opt), fp) != NULL) {
            printf("%s", opt);
        }

        // Close the pipe
        pclose(fp);
    }

    return 0;
}
