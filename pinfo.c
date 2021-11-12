#include "main.h"

void pinfo(char input[]) // finds informations about the process
{
    const char s[2] = " ";
    char *tok;
    FILE *file;
    tok = strtok(input, s); // tokenize input with " " as delimiter
    tok = strtok(NULL, s);  // skipping the command

    char exe[buf], mem[buf], status[buf] = "", pid[buf] = "", memory[buf] = ""; // strings to store required details
    char temp[buf] = "", stor[buf], *p;

    if (tok == NULL) // if no extra input given after pinfo
    {
        strcpy(exe, "/proc/self/exe");          // sets exe path to self proc file
        file = fopen("/proc/self/status", "r"); // opens self status file in read mode
    }
    else
    {
        strcpy(temp, "/proc/");
        strcat(temp, tok); // stores path to given pid in proc
        if (temp[strlen(temp) - 1] == ' ')
        {
            temp[strlen(temp) - 1] = '/';
        }
        else
        {
            temp[strlen(temp)] = '/';
        }                        // proper formatting of path
        strcpy(exe, temp);       // copies the path to exe
        strcat(exe, "exe");      // sets path to exe of given pid
        strcat(temp, "status");  // sets path to status of given pid
        file = fopen(temp, "r"); // opens status file of given pid in read mode
    }

    if (!file) // error handling
    {
        perror("ERROR in file ");
        return;
    }

    while (fgets(stor, buf, file)) // traverses through the status file and stores each line in stor
    {
        if (strncmp(stor, "State:", 6) == 0) // matches State: entry of status file
        {
            strcpy(status, stor + 7); // copies status
        }
        else if (strncmp(stor, "Pid:", 4) == 0)
        {
            strcpy(pid, stor + 5); // copies pid
        }
        else if (strncmp(stor, "VmSize:", 7) == 0)
        {
            strcpy(memory, stor + 8); // copies memory consumed
        }
        else
        {
            continue;
        }
    }
    char sign = ' ';
    if (tcgetpgrp(0) == atoi(pid))
        sign = '+';                              // if grouppid and pid are equal, sets sign to + {coz fg process}

    printf("pid -- %s", pid);                    // prints pid of process
    printf("Status -- %c%c\n", status[0], sign); // prints status with sign
    for (int i = 0; i < strlen(memory); i++)    // formatting memory information
    {
        if (memory[i] == '\n')
        {
            memory[i] = ' ';
        }
    }
    if (memory != "")   // prints memory information of process
    {
        printf("memory -- %s {Virtual Memory} \n", memory); 
    }
    else
    {
        printf("memory -- 0 {Virtual Memory}\n");
    }

    int len, flag = 0;
    if ((len = readlink(exe, mem, sizeof(mem) - 1)) < 0)        // reads the executible path and stores it in mem
    {
        perror("ERROR in readlink");                    // error handling
    }
    else
    {
        if (strlen(mem) < strlen(home))                 // if mem is shorter than home, prints mem
        {
            printf("Executable Path -- %s\n", mem);
            return;
        }
        else
        {
            len = strlen(home);                         // stores length of path to home 
            for (int i = 0; i < strlen(home); i++)      // checks if mem contains path to home in it
            {
                if (home[i] != mem[i])
                {
                    flag = 1;
                }
            }
            if (!flag)
            {
                printf("Executable Path -- ~%s\n", mem + len);      // prints mem without home path in it
            }
            else
            {
                printf("Executable Path -- %s\n", mem);             // prints entire mem path.
            }
        }
        fclose(file);               // closes the file
    }
}