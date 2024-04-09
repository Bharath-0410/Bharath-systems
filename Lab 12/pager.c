/* Simple example to illustrate the use of pipes.
 * This example opens the file provided as the command-line argument,
 * creates a pipe, and forks a child process. Then the parent closes 
 * the read file descriptor of the pipe, reads the contents of the file
 * specified as the command-line argument, writes the contents to the 
 * pipe, and waits for the child process to complete. The child process 
 * closes the write file descriptor of the pipe and execs the "more" 
 * command. This is a simpler version of the program in Figure 15.6 in 
 * the textbook.
 * 
 * To Compile: gcc -Wall pager.c
 * To Run: ./a.out <filename>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  pid_t pid;
  int status;
  int pipefd[2]; /* pipefd[0] for read, pipefd[1] for write */
  FILE *fp;
  char line[BUFSIZ];
  int n;

  if (argc != 2) {
     printf("Usage: %s <filename>\n", argv[0]);
     exit(-1);
  }

  if ( (fp = fopen(argv[1], "r")) == NULL) {
	printf("Error opening file %s for reading\n", argv[1]);
	exit(-1);
  }

  if (pipe(pipefd) == 0) { /* Open a pipe */
    if ((pid = fork()) == 0) { /* I am the child process */
      close(pipefd[1]);    /* close write end */
      dup2(pipefd[0], STDIN_FILENO); /* replace stdin of child */
      execlp("/usr/bin/more", "more", (char *)NULL);
      perror("exec");
      exit(EXIT_FAILURE);
    } else if (pid > 0) { /* I am the parent process */
      close(pipefd[0]);   /* close read end */
      /* read lines from the file and write it to pipe */
      while (fgets(line, BUFSIZ, fp) != NULL) {
	  n = strlen(line);
          if (write(pipefd[1], line, n) != n) {
		printf("Error writing to pipe\n");
		exit(-1);
	  }
      }
      close(pipefd[1]);   /* close write end */

      wait(&status);      /* wait for child to terminate */
      if (WIFEXITED(status))
         printf("Child process exited with status = %d\n", WEXITSTATUS(status));
      else
         printf("Child process did not terminate normally!\n");
    } else { /* we have an error in fork */
      perror("fork");
      exit(EXIT_FAILURE);
    }
  } else {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

