# Assignment: Homework 3
## Author: Bharath Kumar Nakka
## Date: 3/4/24

# Compilation Instructions
github link:https://github.com/Bharath-0410/Bharath-systems/tree/main/HW3
gcc -o h hw3.c  // used to compile the code. 
./h to check the basic functionality 

./h -L 1024 -e "ls -l" 
to List all files with size >= 1024 bytes in the current
directory, and execute the command "ls -l" on each file
(ignore directories)

./h -s jpg 3 -E "tar cvf jpg.tar" 
To List all files that have the substring “jpg” in their filename
or directory name with depth <=3 relative to the current
directory, and creates a tar file named jpg.tar that
contains these files

./h -L 1024 -s jpg 3 -e "wc -l"
To List all files that have the substring “jpg” in their filename
with depth <=3 relative to the current directory and size
>= 1024, and execute the command "wc -l" on each file
(ignore directories)

# My Files
## hw3.c

### Global Variables

The code defines several global variables that play specific roles in the overall functionality of the program. Let's go through each of them:

1. **`char *g_regFilePaths[150]`**: This is an array of pointers to characters (strings). It is used to store the paths of regular files that match the specified criteria during the directory traversal. The array has a maximum capacity of 150 elements.

2. **`short int g_noOfRegularFiles`**: This variable stores the count of regular files that match the specified criteria during the directory traversal. It keeps track of how many paths are stored in `g_regFilePaths`.

3. **`bool g_canExecUnixOnlyOnce`**: This boolean variable is used to control whether the execution of a UNIX command should happen only once for all the matched regular files or not. If this is set to `true`, the program will execute the specified UNIX command once after the directory traversal.

These global variables are used for sharing information and state between different functions and parts of the program. For example, during the directory traversal, if a regular file matches the specified criteria, its path is stored in `g_regFilePaths`, and the count is updated in `g_noOfRegularFiles`. Later, if `g_canExecUnixOnlyOnce` is `true`, the program will execute a UNIX command using the stored paths.

It's worth noting that the use of global variables makes the code more complex and can potentially lead to issues related to code maintainability and debugging. Global variables can introduce hidden dependencies and make it harder to understand the flow of the program. In more modular and well-structured code, you might consider using function parameters and return values to achieve similar results without relying heavily on global state.



### main(int argc, char **argv)

The `main` function in the provided code serves as the entry point for the program. Let's break down its structure and functionality:

```c
int main(int argc, char **argv)
{
    // Variable declarations
    int tabSpaces = 0, sizeFilter = -1;
    bool isDetailsNeeded = false, canShowDirectories = true, canShowRegularFiles = true, canExecUnixEveryTime = false;
    char *Namefilter = NULL, *commandWithArgs = NULL, *path = NULL;
    short int depth = -1;

    // Command-line arguments processing
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
        // Process command-line arguments
        for (int argIndex = 1; argIndex < argc; argIndex++)
        {
            // Handle various command-line options and arguments
            // ...

            // Set the path variable to the last argument
            else if (argIndex == argc - 1)
            {
                path = argv[argIndex];
            }
        }
    }

    // Set a default path if none is provided
    if (path == NULL)
    {
        path = ".";
    }

    // Directory traversal and processing
    traverseDirectory(path, tabSpaces, isDetailsNeeded, sizeFilter, Namefilter, depth, canShowDirectories, canShowRegularFiles, canExecUnixEveryTime, commandWithArgs);

    // Execute UNIX command if specified and 'g_canExecUnixOnlyOnce' is true
    if (g_canExecUnixOnlyOnce && g_noOfRegularFiles > 0)
    {
        printf("\n\n");
        executeUNIX(g_regFilePaths, commandWithArgs, g_noOfRegularFiles);
    }

    // Return 0 to indicate successful execution
    return 0;
}
```

Explanation:

1. **Variable Declarations:** The `main` function starts by declaring various variables to store information and configuration parameters that will be used during the program execution.

2. **Command-line Arguments Processing:** The function checks the number of command-line arguments (`argc`). If there are no arguments, it prints an error message and exits. If there is only one argument, it sets the `path` variable to the current directory (`.`).

3. **Processing Command-line Options:** The function then iterates through the command-line arguments to process various options (e.g., `-S`, `-s`, `-f`, `-t`, `-e`, `-E`). Each option modifies the behavior of the program by changing the values of the corresponding variables.

4. **Setting Default Path:** If no path is provided explicitly, the program sets the `path` variable to the current directory.

5. **Directory Traversal and Processing:** The `traverseDirectory` function is called with the provided parameters. This function is responsible for recursively traversing the specified directory, printing information about files and directories based on the configured options, and potentially executing a UNIX command for specific regular files.

6. **Executing UNIX Command:** If the global variable `g_canExecUnixOnlyOnce` is set to `true`, and there are regular files that match the criteria (`g_noOfRegularFiles > 0`), the program executes a UNIX command using the paths stored in `g_regFilePaths`.

7. **Return 0:** The `main` function returns 0 to indicate successful execution. The operating system typically interprets a return value of 0 as a successful termination of the program.


Certainly! The provided C code is a program that explores a directory and provides information about files and directories within it. It has the capability to execute a specified UNIX command based on certain conditions.

Here's a more straightforward breakdown:

1. **Directory Traversal Function:**
   - The program has a function called `traverseDirectory` that explores a given directory and displays information about files and directories.
   - It supports options such as showing detailed information, applying size and name filters, controlling the depth of traversal, and specifying whether to display directories or regular files.

2. **UNIX Command Execution Function:**
   - There's a function named `executeUNIX` that can execute a UNIX command for a given set of file paths. The execution can happen either every time it encounters a matching regular file or only once after the traversal.

3. **Main Function:**
   - The `main` function is where everything comes together.
   - It processes command-line arguments to determine how the program should behave.
   - Based on the arguments, it sets up configuration parameters, like the directory path, verbosity, size and name filters, and other flags.
   - The program then initiates the directory traversal using the `traverseDirectory` function with the provided configurations.
   - If specified, it may also execute a UNIX command based on certain conditions.

4. **Global Variables:**
   - There are some global variables used to store paths of regular files that match specified criteria during traversal and to control the execution of UNIX commands.

5. **Overall Functionality:**
   - The program is flexible and customizable due to the variety of command-line options.
   - It can be used to explore directories, display information about files and directories, and execute UNIX commands based on certain conditions.

In simpler terms, this code is a versatile tool for exploring directories, gathering information about files, and potentially performing actions on selected files. Its behavior is configured through command-line options.




Inputs:
Directory Path:

Input: The path of the directory to be traversed.
Example: ./my_directory
Command-line Options:

Input: Various options that control the program's behavior.
Example: -S (for detailed information), -s 100 (to filter files by size less than or equal to 100 bytes), -f txt (to filter files by name containing "txt"), -t d (to show only directories), -e "echo Hello" (to execute the UNIX command "echo Hello" for every matching regular file).


Outputs:
Directory and File Information:

Output: Information about the files and directories in the specified directory.
Example:
./my_directory
    file1.txt
    file2.txt
    subdir1
        file3.txt
        file4.doc
    subdir2
        file5.txt


Execution of UNIX Commands:

Output: If specified in the command-line options, the program can execute a UNIX command for certain regular files.
Example: If the command is -e "echo Hello", it will execute echo Hello for each matching regular file.
Examples:
Basic Directory Listing:

Command: ./program ./my_directory
Output:
./my_directory
    file1.txt
    file2.txt
    subdir1
        file3.txt
        file4.doc
    subdir2
        file5.txt

Detailed Information and Size Filtering:

Command: ./program -S -s 100 ./my_directory
Output:
./my_directory
    file1.txt (Size: 50 bytes, Permissions: 644, LastAccessTime: ...)
    file2.txt (Size: 75 bytes, Permissions: 644, LastAccessTime: ...)
    subdir1
        file3.txt (Size: 90 bytes, Permissions: 644, LastAccessTime: ...)
        file4.doc (Size: 120 bytes, Permissions: 644, LastAccessTime: ...)
    subdir2
        file5.txt (Size: 80 bytes, Permissions: 644, LastAccessTime: ...)


Executing UNIX Command:

Command: ./program -e "echo Hello" ./my_directory
Output: (Executes echo Hello for each matching regular file)
These are just examples, and the actual output may vary based on the specific command-line options and the content of the specified directory. The flexibility comes from the ability to customize the program's behavior using various command-line options.


refference:
link: https://chat.openai.com/
