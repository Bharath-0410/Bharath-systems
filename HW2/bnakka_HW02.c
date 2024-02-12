#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> //This allows us open, read and close directories as it is part of posix library
#include<stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define MAX_PATH_SIZE 2000

char * filetype(unsigned char type) {
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}



void traverseDirectory(char *path, int tabSpaces, bool isDetailsNeeded, int sizeFilter, char *Namefilter, short int depth, bool canShowDirectories, bool canShowFiles) {
    struct dirent *dirent;
    DIR *parentDir;
    struct stat buf;
    bool isFileTypeDirectory=false;
    bool isFileTypeRegular=false;

    // First, we need to open the directory.
    parentDir = opendir(path);
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", path); 
        exit (-1);
    }
    else if(tabSpaces==0){
            printf("%*s %s\n", 4 * tabSpaces, " ", path);
            tabSpaces+=1;
    }

    // After we open the directory, we can read the contents of the directory, file by file.
    while((dirent = readdir(parentDir)) != NULL){ 
        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }

        if(dirent->d_type == DT_DIR)
        {
            isFileTypeDirectory = true;
            isFileTypeRegular = false;
        }
        else
        {
            isFileTypeRegular = true;
            isFileTypeDirectory = false;
        }

        if((canShowFiles && isFileTypeRegular) || (canShowDirectories && isFileTypeDirectory))
        {
                char *currFilePath = (char *) malloc(MAX_PATH_SIZE);   //getting the path to use that in lstat.
                strcpy(currFilePath, path);
                strcat(currFilePath, "/");
                strcat(currFilePath, dirent->d_name);

                if (lstat(currFilePath, &buf) < 0) { 
                    printf("lstat error"); 
                    continue; 
                }

                if (depth == -1 || tabSpaces-1 <= depth)
                {
                    if((sizeFilter == -1) || (sizeFilter != -1 && isFileTypeRegular && buf.st_size <= sizeFilter) || isFileTypeDirectory)
                    {
                        if(Namefilter == NULL || (strstr(dirent->d_name, Namefilter)))
                        {
                            if(isDetailsNeeded)
                            {
                                char *lastAccessTime;
                                long long fileSize = 0;

                                lastAccessTime = ctime(&buf.st_atime);
                                lastAccessTime[strlen(lastAccessTime)-1] = '\0'; //as ctime has \n by default at the end, I am removing it to make the output look neat
                                if(!isFileTypeDirectory)
                                {
                                    fileSize = buf.st_size;
                                }
                                printf("%*s %s (Size: %lld bytes, Permissions: %lo (octal), LastAccessTime: %s)\n", 4 * tabSpaces, " ", dirent->d_name, fileSize, (unsigned long) buf.st_mode, lastAccessTime);
                            }
                            else
                            {
                                printf("%*s %s\n", 4 * tabSpaces, " ", dirent->d_name);
                            }
                        }
                    }
                }
        }

        if(canShowDirectories)
        {
                // Check to see if the file type is a directory. If it is, recursively call traverseDirectory on it.
            if (isFileTypeDirectory) {
                // Build the new file path.
                char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
                strcpy(subDirPath, path);
                strcat(subDirPath, "/");
                strcat(subDirPath, dirent->d_name);
                traverseDirectory(subDirPath, tabSpaces + 1, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowFiles);
                free(subDirPath);
            }
        }
    } 
    closedir(parentDir);
}

int main(int argc, char **argv) {
    int tabSpaces = 0, sizeFilter = -1;
    bool isDetailsNeeded = false, canShowDirectories = true, canShowFiles = true;
    char *Namefilter=NULL;
    short int depth=-1;
    char *path = NULL;

    // Check to see if the user provides at least 2 command-line-arguments.
    if (argc < 1) { 
        printf ("Usage: %s <dirname>\n", argv[0]); 
        exit(-1);
    }
    else if(argc == 1)
    {
        //if no directory is given, print the current directory.
        path = ".";
    }
    else
    {
        for (int argIndex = 1; argIndex < argc; argIndex++)
        {
            if(strcmp(argv[argIndex], "-S") == 0)
            {
                isDetailsNeeded = true;
            }
            else if(strcmp(argv[argIndex], "-s") == 0)
            {
                sizeFilter = atoi(argv[argIndex+1]);
                argIndex++;
            }
            else if(strcmp(argv[argIndex], "-f") == 0)
            {
                Namefilter = argv[argIndex+1];
                depth = atoi(argv[argIndex+2]);
                argIndex+=2;
            }
            else if (strcmp(argv[argIndex], "-t") == 0)
            {
                canShowDirectories = strcmp(argv[argIndex + 1], "f");
                canShowFiles = strcmp(argv[argIndex + 1], "d");
                argIndex++;
            }
            else if(argIndex == argc - 1){
                path = argv[argIndex];
            }
        }
    }

    if (path == NULL)
    {
        path = ".";
    }
    traverseDirectory(path, tabSpaces, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowFiles);
    return 0;
}