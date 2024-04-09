#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define MAX_JOBS 128

typedef struct {
    int job_id;
    char command[256];
    pid_t pid;
    int status; // 0: waiting, 1: running, 2: finished
    char starttime[32];
    char endtime[32];
    int success; // 0: running/waiting, 1: success, -1: failed
} Job;

Job jobs[MAX_JOBS]; // Array to store information about jobs
int job_count = 0; // Total number of jobs submitted
int running_jobs = 0; // Number of jobs currently running
int P; // Maximum number of concurrent jobs

// Function to get formatted time
void get_formatted_time(char* buffer, size_t buffer_size) {
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, buffer_size, "%c", timeinfo);
}

// Function to execute a job
void execute_job(int job_index) {
    pid_t pid = fork();
    
    if (pid == 0) { // Child process
        char out_filename[64], err_filename[64];
        snprintf(out_filename, sizeof(out_filename), "%d.out", jobs[job_index].job_id);
        snprintf(err_filename, sizeof(err_filename), "%d.err", jobs[job_index].job_id);
        
        freopen(out_filename, "w", stdout); // Redirect stdout to a file
        freopen(err_filename, "w", stderr); // Redirect stderr to a file
        
        execlp("/bin/sh", "sh", "-c", jobs[job_index].command, NULL); // Execute command using shell
        exit(EXIT_FAILURE); // Exit child process if execlp fails
    } else if (pid > 0) { // Parent process
        jobs[job_index].pid = pid;
        jobs[job_index].status = 1; // Job is now running
        running_jobs++;
        get_formatted_time(jobs[job_index].starttime, sizeof(jobs[job_index].starttime)); // Record start time
    } else {
        perror("fork failed"); // Print error if fork fails
    }
}

// Function to submit a job
void submit_job(const char *command) {
    if (job_count >= MAX_JOBS) {
        printf("Job queue is full.\n"); // Print error if job queue is full
        return;
    }
    
    int job_id = ++job_count; // Increment job ID
    strncpy(jobs[job_id - 1].command, command, sizeof(jobs[job_id - 1].command) - 1); // Copy command to job structure
    jobs[job_id - 1].job_id = job_id; // Set job ID
    jobs[job_id - 1].status = 0; // Job is waiting to be executed
    jobs[job_id - 1].success = 0; // Job status not determined
    
    printf("Job %d added to the queue\n", job_id); // Print confirmation message
    
    if (running_jobs < P) {
        execute_job(job_id - 1); // Execute the job if there's available capacity
    }
}

// Function to update job status
void update_jobs() {
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].status == 1) {
            int status;
            pid_t result = waitpid(jobs[i].pid, &status, WNOHANG); // Check if child process has finished
            if (result > 0) {
                jobs[i].status = 2; // Job has finished
                running_jobs--;
                get_formatted_time(jobs[i].endtime, sizeof(jobs[i].endtime)); // Record end time
                jobs[i].success = WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 1 : -1; // Determine job success status
            }
        }
    }

    for (int i = 0; i < job_count && running_jobs < P; i++) {
        if (jobs[i].status == 0) {
            execute_job(i); // Execute waiting jobs if there's available capacity
        }
    }
}

// Function to display active jobs
void show_jobs() {
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].status < 2) {
            printf("Job ID %d: %s - %s\n", jobs[i].job_id, jobs[i].command, jobs[i].status == 1 ? "Running" : "Waiting");
        }
    }
}

// Function to display job submission history
void show_submission_history() {
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].status == 2) {
            printf("%d %s %s %s %s\n", jobs[i].job_id, jobs[i].command, jobs[i].starttime, jobs[i].endtime, 
                   jobs[i].success == 1 ? "Success" : "Failed");
        }
    }
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <P>\n", argv[0]); // Print usage message if incorrect number of arguments
        exit(EXIT_FAILURE);
    }
    
    P = atoi(argv[1]); // Maximum number of concurrent jobs
    
    char command[256]; // Buffer to store user input command

    // Main loop
    while (1) {
        update_jobs(); // Check and update job status
        
        printf("Enter command> ");
        if (!fgets(command, sizeof(command), stdin)) break; // Read user input
        
        command[strcspn(command, "\n")] = 0; // Remove trailing newline
        
        // Handle user commands
        if (strcmp(command, "submithistory") == 0) {
            printf("Job ID Command Starttime Endtime Status\n");
            show_submission_history();
        }
        else if (strncmp(command, "submit", 6) == 0) {
            printf("Submitting job\n");
            submit_job(command + 7); // Submit a job
        } else if (strcmp(command, "showjobs") == 0) {
            show_jobs(); // Show active jobs
        }  else if (strcmp(command, "exit") == 0) {
            break; // Exit program
        } else {
            printf("Unknown command.\n"); // Print error for unknown command
        }
    }
    
    return 0; // Return success
} 
