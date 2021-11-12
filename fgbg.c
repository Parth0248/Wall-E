#include "main.h"

void initc(char *input[buf]) // inits the array of words (char* c[buf])
{
    int i = 0;
    while (input[i] != NULL)
    {
        input[i++] = NULL;
    }
}

void fgbg(char input[]) // identifies if the given command is foreground or background function
{
    int flag = 0, i = 0;

    initc(c); // init c

    char dup[buf] = "";
    strcpy(dup, input);           // makes duplicate of input string
    char *tok = strtok(dup, " "); // tokenizes duplicate with " " as delimiter

    while (tok != NULL) // traverses through duplicate and stores each work in c (char* c[buf])
    {
        c[i] = tok;
        i++;
        tok = strtok(NULL, " ");
    }
    c[i] = NULL; // sets element after last entry to NULL
    i++;         // increaments total elements (including NULL entry)

    if (strcmp(c[i - 2], "&") == 0) // checks if last second element is "&"
    {
        flag = 1;        // flag to call background function set to 1
        c[i - 2] = NULL; // the element with & set to NULL
    }

    if (!flag) // calls foreground or background function based on flag condition
    {
        fg_fun(c, i);
    }
    else
    {
        bg_fun(c, i);
    }
}

void fg_fun(char *input[buf], int cnt) // performs foreground function
{
    int status;
    pid_t pid = fork(); // creates child process

    if (pid < 0) // error handling
    {
        printf("ERROR in creating child process\n");
        return;
    }
    if (pid == 0) // for child process (with pid == 0)
    {
        // printf("Pid of fg_child -- %d\n", pid);
        if (execvp(input[0], input) < 0) // calls the input with command as first input and entire string as second
        {
            printf("Invalid Command\n"); // error handling
            return;
        }
        return; // terminates after command is finished
    }
    else
    {
        // printf("Pid of fg_parent -- %d\n", pid);
        wait(0); // waits for child process
    }
}

void bg_fun(char *input[buf], int cnt) // performs background functions
{
    int status;
    pid_t pid = fork(); // creates child process

    if (pid < 0) // error handling
    {
        printf("ERROR in creating child process\n");
        return;
    }
    if (pid == 0) // for child process (with pid == 0)
    {
        if (execvp(*input, input) < 0) // calls the input with command as first input and entire string as second
        {
            printf("Invalid Command\n"); // error handling
            return;
        }
        return; // return after program is terminated
    }
    else
    {
        // printf("pid of bg_parent -- %d\n", pid);
        job[jobcnt].pid = pid;             // stores pid of bg process in jobs array
        job[jobcnt].status = 1;            // stores status for my reference in jobs array
        strcpy(job[jobcnt].jobname, c[0]); // stores name of the bg process in job array
        jobcnt++;                          // increaments number of bg process details added
        signal(SIGCHLD, check_bg);         // sends signal about child process and calls check_bg function
    }
}

void check_bg() // checks status of background function and prints message about its details and termination
{
    int pid, status, j = 0;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) // waits for process to terminates
    {   
        // WNOHANG -> waitpid should return immediately after termination of process
        // WUNTRACED -> allows parent to return if child is terminated/stopped/killed etc.
        if (WIFEXITED(status)) // checks if the child process terminated normally
        {
            for (int i = 0; i < jobcnt; i++)    // looks for the details of child process in the job array
            {
                if (job[i].pid == pid)          
                {
                    job[i].status = 0;          // sets its status in job array to 0 (since it terminated)
                    fprintf(stderr, "\n%s with pid %d exited normally\n", job[i].jobname, job[i].pid);  // prints the detail message
                }
            }
        }
        else
        {
            for (int i = 0; i < jobcnt; i++)        // looks for the details of child process in the job array
            {
                if (job[i].pid == pid)
                {
                    job[i].status = 0;              // sets its status in job array to 0 (since it terminated)
                    fprintf(stderr, "\nProcess %s with pid %d exited abnormally\n", job[i].jobname, job[i].pid); // prints the detail message
                }
            }
        }
    }
    printf("<%s%s>", user, prnt);   // prints the prompt message
    fflush(stderr);                 // flushes the stderr
    fflush(stdout);                 // flushes the stdout

    for (int i = 0; i < jobcnt; ++i)    // updates the job array by removing the terminated bg processes
    {
        if (job[i].status)
        {
            job[j] = job[i];
            j++;
        }
    }
    jobcnt = j;                         // updating the jobcnt to number of remaining bg processes
    return; 
}
