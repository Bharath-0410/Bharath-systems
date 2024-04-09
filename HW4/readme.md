for compilation 

gcc -o hw HW.c

for running 

./hw 2 


github link: 




1. `jobs`: Array of structures to store information about jobs.
2. `job_id`: Integer variable representing the ID of a job.
3. `command`: Character array to store the command associated with a job.
4. `pid`: Process ID (PID) associated with a job.
5. `status`: Integer variable indicating the status of a job (0: waiting, 1: running, 2: finished).
6. `starttime`: Character array to store the start time of a job.
7. `endtime`: Character array to store the end time of a job.
8. `success`: Integer variable indicating the result of a job (0: running/waiting, 1: success, -1: failed).
9. `job_count`: Integer variable representing the total number of jobs submitted.
10. `running_jobs`: Integer variable representing the number of jobs currently running.
11. `P`: Integer variable representing the maximum number of concurrent jobs.
12. `user_input`: Character array to store user input commands.




1. **Header Files**: The program includes necessary header files such as `<stdio.h>`, `<stdlib.h>`, `<unistd.h>`, `<sys/wait.h>`, `<string.h>`, and `<time.h>`.

2. **Constants**: 
   - `MAX_JOBS`: Defines the maximum number of jobs that can be stored in the `jobs` array.

3. **Struct Definition**:
   - `Job`: Defines a structure to represent a job. It contains:
     - `job_id`: ID of the job.
     - `command`: Command associated with the job.
     - `pid`: Process ID associated with the job.
     - `status`: Status of the job (waiting, running, or finished).
     - `starttime`: Start time of the job.
     - `endtime`: End time of the job.
     - `success`: Indicates whether the job was successful or failed.

4. **Global Variables**:
   - `jobs`: Array of `Job` structures to store information about jobs.
   - `job_count`: Total number of jobs submitted.
   - `running_jobs`: Number of jobs currently running.
   - `P`: Maximum number of concurrent jobs.

5. **Function Prototypes**:
   - `get_formatted_time`: Formats the current time.
   - `execute_job`: Executes a job by forking a child process.
   - `submit_job`: Submits a new job to the system.
   - `update_jobs`: Updates the status of jobs (checks if any have finished).
   - `show_jobs`: Displays information about active jobs.
   - `show_submission_history`: Displays the submission history of jobs.

6. **`get_formatted_time` Function**:
   - Uses `localtime` and `strftime` functions to get and format the current time.

7. **`execute_job` Function**:
   - Forks a child process to execute a job.
   - Redirects stdout and stderr to separate files for the job.
   - Executes the command associated with the job using `execlp`.

8. **`submit_job` Function**:
   - Submits a new job by copying the command into the `jobs` array.
   - Updates job status and executes the job if there is available capacity.

9. **`update_jobs` Function**:
   - Checks if any running jobs have finished using `waitpid`.
   - Updates job status and success status accordingly.
   - Executes waiting jobs if there is available capacity.

10. **`show_jobs` Function**:
   - Displays information about active jobs (job ID, command, and status).

11. **`show_submission_history` Function**:
   - Displays the submission history of jobs, including job ID, command, start time, end time, and status.

12. **`main` Function**:
   - Parses command-line arguments to set the maximum number of concurrent jobs.
   - Enters a loop to interact with the user.
   - Updates job status, reads user commands, and executes corresponding actions (submitting a job, displaying active jobs, displaying submission history, or exiting the program).




