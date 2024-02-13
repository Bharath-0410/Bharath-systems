#include <stdio.h> // used to access all the basic functions of c-programming 
#include <stdlib.h> // used mainly for the memory allocations
#include <string.h> // used for the string manipulation functions 
#include <time.h> // used for the time and date functions 
#include <dirent.h> // used for the directory based operations 
#include <sys/stat.h> // used to get information about the file attributes 
#include<stdbool.h> // used to use the bool values true or false 
#include <unistd.h> // used to use the unix operating system's commands 
#include <sys/types.h> //used to define the various data types 




#define MAX_SIZE_OF_PATH 2000 // define is used to create macros. 

char * filetype(unsigned char type) 
// here the type refers to directory entry types. 
{
// Here DT_* refers to the multiple directory types used to access the filetypes.
// here the switch statement is used to define the file type entered and then the pointer 
// string 'str' is used to assign the corresponding value according the switch condition 
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
// the str value is returned according to the switch condition 
}


// here we are creating a function which can recursively explore and can get the contnets of the directory. 
// so the name is given as ExploreDirectory. the inputs for the function are as follows. 
void ExploreDirectory(char *path, int tabSpaces, bool isDetailsNeeded, int sizeFilter, char *Namefilter, short int depth, bool canShowDirectories, bool canShowFiles) {
    struct dirent *dirent;
    DIR *parentDirectory;
    struct stat buf;
    bool isFileTypeDirectory=false;
    bool isFileTypeRegular=false;

    // First, we need to open the directory. If the path is null an error message is given to the user. 
    parentDirectory = opendir(path);
    if (parentDirectory == NULL) { 
        printf ("Error opening directory '%s'\n", path); 
        exit (-1);
    } // if the tab space is zero then the output will be the path of the directory. 
    else if(tabSpaces==0){
            printf("%*s %s\n", 4 * tabSpaces, " ", path);
            tabSpaces+=1;
    }

    // once the directory is opened we can get the contents of the directory by each file.  
    while((dirent = readdir(parentDirectory)) != NULL){ 
        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
            continue;
        }
		// this loop is used to determine the current directory entry. 
        if(dirent->d_type == DT_DIR)
        { // if the DT_DIR is a directory then isFileTypeDirectory is set to true. 
            isFileTypeDirectory = true;
            
        }
        else
        { // if the DT_DIR is not a directory then isFileTypeRegular is set to true. 
            isFileTypeRegular = true;
            
        }
		// here the bool vales are being compared if all are true then the respective if block is being executed. 
        if((canShowFiles && isFileTypeRegular) || (canShowDirectories && isFileTypeDirectory))
        {
                char *currFilePath = (char *) malloc(MAX_SIZE_OF_PATH);   //getting the path to use that in lstat.
                strcpy(currFilePath, path);
                strcat(currFilePath, "/");
                strcat(currFilePath, dirent->d_name);
				// this if loop is used to retirve the information about the current file. 
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
                        	// if the isDetailsNeeded is true then the following if block is being executed. 
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
		// if canShowDirectories and isFileTypeDirectory both are true then the following if block is executed. 
        if(canShowDirectories && isFileTypeDirectory)
        {
                // Check to see if the file type is a directory. If it is, recursively call ExploreDirectory on it.
                // Build the new file path.
                char *subDirPath = (char *) malloc(MAX_SIZE_OF_PATH);
                strcpy(subDirPath, path);
                strcat(subDirPath, "/");
                strcat(subDirPath, dirent->d_name);
                ExploreDirectory(subDirPath, tabSpaces + 1, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowFiles);
                free(subDirPath);
            
        }
    } 
    // here we are closing the directory. 
    closedir(parentDirectory);
}
// main block is being started. 
int main(int argc, char **argv) {
    int tabSpaces = 0, sizeFilter = -1;
    bool isDetailsNeeded = false, canShowDirectories = true, canShowFiles = true;
    char *Namefilter=NULL;
    short int depth=-1;
    char *path = NULL;

    // Check to see if the user provides at least 2 command-line-arguments.
    // this loop is for the argc value is 0 
    if (argc < 1) { 
        printf ("Usage: %s <dirname>\n", argv[0]); 
        exit(-1);
    }
    // this loop is for the argc value is 1
    else if(argc == 1)
    {
        //if no directory is given, print the current directory.
        path = ".";
    } // this loop is for the argc value is greater than 2. 
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
	// this block is excecuted if the path is null 
    if (path == NULL)
    {
        path = ".";
    }
    // calling the function ExploreDirectory 
    ExploreDirectory(path, tabSpaces, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowFiles);
    return 0;
}