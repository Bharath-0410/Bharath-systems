Lab 09 
For Compilation: Use “gcc -o lab lab9.c”

For Running: Use “./lab”

GITHUB Link: https://github.com/Bharath-0410/Bharath-systems/tree/main/Lab%2009



child_pid (pid_t): This variable is of type pid_t, which is typically used to represent process IDs. In this code, it is used to store the process ID returned by the fork() function. When fork() is called, it returns different values in the parent and child processes. In the parent process, it returns the process ID of the child process, while in the child process, it returns 0. This variable is used to differentiate between the parent and child processes.

status (int): This variable is used to store the exit status of the child process. It is passed as an argument to the wait() function, which waits for the child process to terminate and stores the exit status in this variable.

argc (int): This variable represents the number of command-line arguments passed to the program, including the name of the program itself. It is of type int and is automatically populated by the operating system when the program is executed.

**argv (char ): This is an array of strings (char *) that contains the command-line arguments passed to the program. It stands for "argument vector." argv[0] contains the name of the program itself, and subsequent elements contain the command-line arguments provided by the user.

Ctrl+C (SIGINT):

When you press Ctrl+C, it sends the SIGINT (Signal Interrupt) signal to the foreground process running in the terminal.
SIGINT is typically used to request that a process terminate. By default, it causes the process to terminate gracefully.
In the context of the provided code:
SIGINT is handled by the sigint_handler function, which prints a message indicating that SIGINT was caught.
The parent process (main function) sets up a signal handler for SIGINT using the signal(SIGINT, sigint_handler) call.
Ctrl+Z (SIGTSTP):

When you press Ctrl+Z, it sends the SIGTSTP (Signal Terminal Stop) signal to the foreground process running in the terminal.
SIGTSTP is used to request that a process pause (i.e., stop execution).
Unlike SIGINT, which typically causes a process to terminate, SIGTSTP causes the process to be stopped and placed in the background.
In the context of the provided code:
SIGTSTP is handled by the sigtstp_handler function, which prints a message indicating that SIGTSTP was caught.
The parent process (main function) sets up a signal handler for SIGTSTP using the signal(SIGTSTP, sigtstp_handler) call.
Ctrl+\ (SIGQUIT):

When you press Ctrl+\, it sends the SIGQUIT (Signal Quit) signal to the foreground process running in the terminal.
SIGQUIT is similar to SIGINT, but it typically triggers a core dump of the process (i.e., it writes a memory image of the process to disk).
It's often used to debug processes or force them to terminate abnormally.
In the context of the provided code:
There is no specific handler set up for SIGQUIT. However, if not handled, it will cause the process to terminate similarly to SIGINT.