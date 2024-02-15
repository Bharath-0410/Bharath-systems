#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
// reruired header files have been inserted. 



// ListFilesRecursively function has been created.
void listFilesRecursively(char *basePath) {
    struct dirent *dirent;
    DIR *dir = opendir(basePath);

    if (!dir) {
        printf("Error opening directory '%s'\n", basePath);
        return;
    }

    int count = 1;
    while ((dirent = readdir(dir)) != NULL) {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
            printf("[%d] %s\n", count, dirent->d_name);
            count++;

            // Construct the full path for the entry
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", basePath, dirent->d_name);

            // Use stat to get information about the entry
            struct stat entryStat;
            if (stat(path, &entryStat) == 0) {
                // Check if the entry is a directory
                if (S_ISDIR(entryStat.st_mode)) {
                    // Recursively call listFilesRecursively for the subdirectory
                    listFilesRecursively(path);
                }
            }
        }
    }

    closedir(dir);
}

// main function started 
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }

    printf("Listing files and subdirectories in '%s':\n", argv[1]);
    // listFilesRecursively has called 
    listFilesRecursively(argv[1]);

    return 0;
}
