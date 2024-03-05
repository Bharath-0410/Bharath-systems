#include <stdio.h> 
// used to access all the basic functions of c-programming 
#include <stdlib.h>
// used mainly for the memory allocations
#include <string.h>
// used for the string manipulation functions 
#include <dirent.h>
// used for the directory based operations 
#include <stdbool.h>
// used to use the bool values true or false 
#include <sys/types.h>
 //used to define the various data types 
#include <sys/stat.h>
// used to get information about the file attributes 
#include <unistd.h>
// used to use the unix operating system's commands 
#include <time.h> 
// used for the time and date functions 
#include <sys/wait.h>

// define is used to create macros. 
#define MAX_PATH_SIZE 2000
#define MAX_ARGS 150

// here the type refers to directory entry types. 
char *g_regFilePaths[150];
short int g_noOfRegularFiles = 0;
bool g_canExecUnixOnlyOnce = false;


// Here DT_* refers to the multiple directory types used to access the filetypes.
// here the switch statement is used to define the file type entered and then the pointer 
// string 'str' is used to assign the corresponding value according the switch condition 


char *filetype(unsigned char type)
{
	
    char *str;
    // switch statement is used here to make the decision based on the filetype
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
    
// the str value is returned according to the switch condition 
}


//here we are creating a function named the executeUNIX to get through the commands given during the program compilation and testing. 
void executeUNIX(char *filePath[], char *commandWithArgsReceived, int noOfRegFiles)
{
	// few variables have been initialized according the usage of the code
    int status = 0, index = 0, noOfArgs = 0, count = 0;
    char *commandToExecute = NULL, commandWithArgs[100], *args[MAX_ARGS];
    pid_t pid;
// strcpy is used to copy the string and this carries out the string operations. 
    strcpy(commandWithArgs, commandWithArgsReceived);
    // for loop is being started
    for (index = 0; index < strlen(commandWithArgs); index++)
    {
    	// opening if loop. 
        if (commandWithArgs[index] == ' ')
        {
            noOfArgs++;
        }
    }

    commandToExecute = strtok(commandWithArgs, " ");
    count = noOfArgs;

    args[0] = commandToExecute;
    index = 1;
    // if the count is greater than zero the following loop is being executed.
    while (count > 0)
    {
        args[index] = strtok(NULL, " ");
        index++;
        count--;
    }
    // for loop is being used to increase the index value. 
    for (int i = 0; i < noOfRegFiles; i++)
    {
        args[index] = filePath[i];
        index++;
    }
    args[index] = NULL;
// the command fork() came here adn assigned to PID 
    pid = fork();
    // the following if loop is executed if the PID value is zero 
    if (pid == 0)
    {
        execvp(commandToExecute, args);
        perror("execvp");
        printf("Error: Execvp failed.\n");
        exit(-1);
    }
    // the following else if loop is executed if the PID value is greater than zero 
    else if (pid > 0)
    {
        wait(&status);
        if (!WIFEXITED(status))
        {
            printf("Child process did not terminate normally and exited with status = %d\n", WEXITSTATUS(status));
        }
    }
    // the following else loop is executed if both the cases fail.  
    else
    {
        printf("Error: fork");
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

// the function name traverseDirectory is being created 
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
    // if loop is being executed is the parent directory given is null or empty. 
    if (parentDir == NULL)
    {
        printf("Error opening directory '%s'\n", path);
        exit(-1);
    }
    // this loop is being called if the tabspace values equals to zero. 
    else if (tabSpaces == 0)
    {
        printf("%*s %s\n", 4 * tabSpaces, " ", path);
        tabSpaces += 1;
    }
// while loop is being called if dirent and parent directory values are not euqal to null. 
    while ((dirent = readdir(parentDir)) != NULL)
    {	
    	// if loop is being called here
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
        {
        	// if the condition is true the executuion continues, as we used the continue statement. 
            continue;
        }
		// if loop is being called
        if (dirent->d_type == DT_DIR)
        {
            isFileTypeDirectory = true;
            isFileTypeRegular = false;
        }
        // this else part is executed if the given if condition is failed or false. 
        else
        {
            isFileTypeRegular = true;
            isFileTypeDirectory = false;
        }
		// if loop is called if the given argumet is true if not the else part is being executed. 
        if ((canShowRegularFiles && isFileTypeRegular) || (canShowDirectories && isFileTypeDirectory))
        {
            char *currFilePath = (char *)malloc(MAX_PATH_SIZE);
            strcpy(currFilePath, path);
            strcat(currFilePath, "/");
            strcat(currFilePath, dirent->d_name);
			// if loop is being called 
            if (lstat(currFilePath, &buf) < 0)
            {
                printf("lstat error");
                continue;
            }
					// if loop is called if the given argumet is true if not the else part is being executed. 
			// if loop is being called 
            if ((sizeFilter == -1) || (sizeFilter != -1 && isFileTypeRegular && buf.st_size <= sizeFilter) || isFileTypeDirectory)
            {
            	// if loop is being called 
                if (depth == -1 || tabSpaces - 1 <= depth)
                {
                	// if loop is being called 
                    if (Namefilter == NULL || (strstr(dirent->d_name, Namefilter)))
                    {
                    	// if loop is called here using the command as isDetailsNeeded
                        if (isDetailsNeeded)
                        {
                            char *lastAccessTime;
                            long long fileSize = 0;

                            lastAccessTime = ctime(&buf.st_atime);
                            lastAccessTime[strlen(lastAccessTime) - 1] = '\0';
							// if loop is called here using the command as isFileTypeDirectory and if it is not true. 
                            if (!isFileTypeDirectory)
                            {
                                fileSize = buf.st_size;
                            }
                            printf("%*s %s (Size: %lld bytes, Permissions: %lo (octal), LastAccessTime: %s)\n", 4 * tabSpaces, " ", dirent->d_name, fileSize, (unsigned long)buf.st_mode, lastAccessTime);
                        }
                        // else part is executed if the given condition is false. 
                        else
                        {
                            printf("%*s %s\n", 4 * tabSpaces, " ", dirent->d_name);
                        }
						// if loop is called here using the command as isFileTypeRegular
                        if (isFileTypeRegular)
                        {
                        	// if loop is called here using the command as canExecUnixEveryTime
                            if (canExecUnixEveryTime)
                            {
                                regFilePath[0] = currFilePath;
                                executeUNIX(regFilePath, commandWithArgs, 1);
                            }
							// if loop is called here using the command as g_canExecUnixOnlyOnce
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
		// if loop is called here using the command as canShowDirectories
        if (canShowDirectories)
        {
        	// if loop is called here using the command as isFileTypeDirectory
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
    // closing the opened directories using the closedir command. 
}
// main fucntion is being called here . 
int main(int argc, char **argv)
{
	//assigning the variables according to the requirememnt 
    int tabSpaces = 0, sizeFilter = -1;
    bool isDetailsNeeded = false, canShowDirectories = true, canShowRegularFiles = true, canExecUnixEveryTime = false;
    char *Namefilter = NULL, *commandWithArgs = NULL, *path = NULL;
    short int depth = -1;
	// if loop is being called. and is executed only if the argc value is less than 1
    if (argc < 1)
    {
        printf("Expecting an argument\n");
        exit(-1);
    }
    // if loop is being called and is executed only when the argc value is equal to 1
    else if (argc == 1)
    {
        path = ".";
    }
    // for all other condition of the argc the following else part is being executed. 
    else
    {
    	// for loop is opened here for the required outputs to pass as the input command line arguments. for the different inputs
        for (int argIndex = 1; argIndex < argc; argIndex++)
        {
        	// using if loop to check the condion for S
            if (strcmp(argv[argIndex], "-S") == 0 || strcmp(argv[argIndex], "-s") == 0)
            {
                isDetailsNeeded = (strcmp(argv[argIndex], "-S") == 0);
            }
            // this part is executed if the argindex value is null or equal to zero for s falg
            else if (strcmp(argv[argIndex], "-s") == 0)
            {
                sizeFilter = atoi(argv[argIndex + 1]);
                argIndex++;
            }
			// this part is executed if the argindex value is null or equal to zero for f flag
            else if (strcmp(argv[argIndex], "-f") == 0)
            {
                Namefilter = argv[argIndex + 1];
                depth = atoi(argv[argIndex + 2]);
                argIndex += 2;
            }
            // this part is executed if the argindex value is null or equal to zero for t flag
            else if (strcmp(argv[argIndex], "-t") == 0)
            {
                canShowDirectories = strcmp(argv[argIndex + 1], "f");
                canShowRegularFiles = strcmp(argv[argIndex + 1], "d");
                argIndex++;
            }
            // this part is executed if the argindex value is null or equal to zero for e flag
            else if (strcmp(argv[argIndex], "-e") == 0)
            {
                canExecUnixEveryTime = true;
                commandWithArgs = argv[argIndex + 1];
                argIndex++;
            }
            // this part is executed if the argindex value is null or equal to zero for E flag
            else if (strcmp(argv[argIndex], "-E") == 0)
            {
                g_canExecUnixOnlyOnce = true;
                commandWithArgs = argv[argIndex + 1];
                argIndex++;
            }
            // this part is executed if the argindes is less than argc-1 
            else if (argIndex == argc - 1)
            {
                path = argv[argIndex];
            }
        }
    }
// if the given path is not valid then the following output is being printed. 
    if (path == NULL)
    {
        path = ".";
    }
// traverseDirectory function has been called with the necessary input arguments. 
    traverseDirectory(path, tabSpaces, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowRegularFiles, canExecUnixEveryTime, commandWithArgs);
	// if loop is being called and is executed when the given statememnt is true. 
    if (g_canExecUnixOnlyOnce && g_noOfRegularFiles > 0)
    {
        printf("\n\n");
        executeUNIX(g_regFilePaths, commandWithArgs, g_noOfRegularFiles);
    }
    // returing zero after the code is compiled. 
    return 0;
}
