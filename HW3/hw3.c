#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_PATH_SIZE 2000
#define MAX_ARGS 150
char *g_regFilePaths[150];
short int g_noOfRegularFiles = 0;
bool g_canExecUnixOnlyOnce = false;

char *filetype(unsigned char type)
{
    char *str;
    switch (type)
    {
    case DT_BLK:
        str = "block device";
        break;
    case DT_CHR:
        str = "character device";
        break;
    case DT_DIR:
        str = "directory";
        break;
    case DT_FIFO:
        str = "named pipe (FIFO)";
        break;
    case DT_LNK:
        str = "symbolic link";
        break;
    case DT_REG:
        str = "regular file";
        break;
    case DT_SOCK:
        str = "UNIX domain socket";
        break;
    case DT_UNKNOWN:
        str = "unknown file type";
        break;
    default:
        str = "UNKNOWN";
    }
    return str;
}

void executeUNIX(char *filePath[], char *commandWithArgsReceived, int noOfRegFiles)
{
    int status = 0, index = 0, noOfArgs = 0, count = 0;
    char *commandToExecute = NULL, commandWithArgs[100], *args[MAX_ARGS];
    pid_t pid;

    strcpy(commandWithArgs, commandWithArgsReceived);
    for (index = 0; index < strlen(commandWithArgs); index++)
    {
        if (commandWithArgs[index] == ' ')
        {
            noOfArgs++;
        }
    }

    commandToExecute = strtok(commandWithArgs, " ");
    count = noOfArgs;

    args[0] = commandToExecute;
    index = 1;
    while (count > 0)
    {
        args[index] = strtok(NULL, " ");
        index++;
        count--;
    }
    for (int i = 0; i < noOfRegFiles; i++)
    {
        args[index] = filePath[i];
        index++;
    }
    args[index] = NULL;

    pid = fork();
    if (pid == 0)
    {
        execvp(commandToExecute, args);
        perror("execvp");
        printf("Error: Execvp failed.\n");
        exit(-1);
    }
    else if (pid > 0)
    {
        wait(&status);
        if (!WIFEXITED(status))
        {
            printf("Child process did not terminate normally and exited with status = %d\n", WEXITSTATUS(status));
        }
    }
    else
    {
        printf("Error: fork");
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void traverseDirectory(char *path, int tabSpaces, bool isDetailsNeeded, int sizeFilter, char *Namefilter, short int depth, bool canShowDirectories, bool canShowRegularFiles, bool canExecUnixEveryTime, char *commandWithArgs)
{
    struct dirent *dirent;
    DIR *parentDir;
    struct stat buf;
    bool isFileTypeDirectory = false;
    bool isFileTypeRegular = false;

    char *regFilePath[1];
    short int index = 0;

    parentDir = opendir(path);
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", path);
        exit(-1);
    }
    else if (tabSpaces == 0)
    {
        printf("%*s %s\n", 4 * tabSpaces, " ", path);
        tabSpaces += 1;
    }

    while ((dirent = readdir(parentDir)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
        {
            continue;
        }

        if (dirent->d_type == DT_DIR)
        {
            isFileTypeDirectory = true;
            isFileTypeRegular = false;
        }
        else
        {
            isFileTypeRegular = true;
            isFileTypeDirectory = false;
        }

        if ((canShowRegularFiles && isFileTypeRegular) || (canShowDirectories && isFileTypeDirectory))
        {
            char *currFilePath = (char *)malloc(MAX_PATH_SIZE);
            strcpy(currFilePath, path);
            strcat(currFilePath, "/");
            strcat(currFilePath, dirent->d_name);

            if (lstat(currFilePath, &buf) < 0)
            {
                printf("lstat error");
                continue;
            }

            if ((sizeFilter == -1) || (sizeFilter != -1 && isFileTypeRegular && buf.st_size <= sizeFilter) || isFileTypeDirectory)
            {
                if (depth == -1 || tabSpaces - 1 <= depth)
                {
                    if (Namefilter == NULL || (strstr(dirent->d_name, Namefilter)))
                    {
                        if (isDetailsNeeded)
                        {
                            char *lastAccessTime;
                            long long fileSize = 0;

                            lastAccessTime = ctime(&buf.st_atime);
                            lastAccessTime[strlen(lastAccessTime) - 1] = '\0';

                            if (!isFileTypeDirectory)
                            {
                                fileSize = buf.st_size;
                            }
                            printf("%*s %s (Size: %lld bytes, Permissions: %lo (octal), LastAccessTime: %s)\n", 4 * tabSpaces, " ", dirent->d_name, fileSize, (unsigned long)buf.st_mode, lastAccessTime);
                        }
                        else
                        {
                            printf("%*s %s\n", 4 * tabSpaces, " ", dirent->d_name);
                        }

                        if (isFileTypeRegular)
                        {
                            if (canExecUnixEveryTime)
                            {
                                regFilePath[0] = currFilePath;
                                executeUNIX(regFilePath, commandWithArgs, 1);
                            }

                            if (g_canExecUnixOnlyOnce)
                            {
                                g_regFilePaths[g_noOfRegularFiles] = currFilePath;
                                g_noOfRegularFiles++;
                            }
                        }
                    }
                }
            }
        }

        if (canShowDirectories)
        {
            if (isFileTypeDirectory)
            {
                char *subDirPath = (char *)malloc(MAX_PATH_SIZE);
                strcpy(subDirPath, path);
                strcat(subDirPath, "/");
                strcat(subDirPath, dirent->d_name);
                traverseDirectory(subDirPath, tabSpaces + 1, isDetailsNeeded, sizeFilter, Namefilter, depth - 1, canShowDirectories, canShowRegularFiles, canExecUnixEveryTime, commandWithArgs);
                free(subDirPath);
            }
        }
    }
    closedir(parentDir);
}

int main(int argc, char **argv)
{
    int tabSpaces = 0, sizeFilter = -1;
    bool isDetailsNeeded = false, canShowDirectories = true, canShowRegularFiles = true, canExecUnixEveryTime = false;
    char *Namefilter = NULL, *commandWithArgs = NULL, *path = NULL;
    short int depth = -1;

    if (argc < 1)
    {
        printf("Expecting an argument\n");
        exit(-1);
    }
    else if (argc == 1)
    {
        path = ".";
    }
    else
    {
        for (int argIndex = 1; argIndex < argc; argIndex++)
        {
            if (strcmp(argv[argIndex], "-S") == 0 || strcmp(argv[argIndex], "-s") == 0)
            {
                isDetailsNeeded = (strcmp(argv[argIndex], "-S") == 0);
            }
            else if (strcmp(argv[argIndex], "-s") == 0)
            {
                sizeFilter = atoi(argv[argIndex + 1]);
                argIndex++;
            }
            else if (strcmp(argv[argIndex], "-f") == 0)
            {
                Namefilter = argv[argIndex + 1];
                depth = atoi(argv[argIndex + 2]);
                argIndex += 2;
            }
            else if (strcmp(argv[argIndex], "-t") == 0)
            {
                canShowDirectories = strcmp(argv[argIndex + 1], "f");
                canShowRegularFiles = strcmp(argv[argIndex + 1], "d");
                argIndex++;
            }
            else if (strcmp(argv[argIndex], "-e") == 0)
            {
                canExecUnixEveryTime = true;
                commandWithArgs = argv[argIndex + 1];
                argIndex++;
            }
            else if (strcmp(argv[argIndex], "-E") == 0)
            {
                g_canExecUnixOnlyOnce = true;
                commandWithArgs = argv[argIndex + 1];
                argIndex++;
            }
            else if (argIndex == argc - 1)
            {
                path = argv[argIndex];
            }
        }
    }

    if (path == NULL)
    {
        path = ".";
    }

    traverseDirectory(path, tabSpaces, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowRegularFiles, canExecUnixEveryTime, commandWithArgs);

    if (g_canExecUnixOnlyOnce && g_noOfRegularFiles > 0)
    {
        printf("\n\n");
        executeUNIX(g_regFilePaths, commandWithArgs, g_noOfRegularFiles);
    }
    return 0;
}
