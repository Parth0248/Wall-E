#ifndef __MHEADER_H
#define __MHEADER_H

// All the standard header files
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <error.h>
#include <ctype.h>

#define buf 1000 // global value set to 1000

// Global variables
char str[buf];
char home[buf];
char user[buf];
char host[buf];
char path[buf];
char inp[buf];
char *token;
char prnt[buf];
char prevprnt[buf];
char prevdir[buf];
char *c[buf];
int inpcnt;
int echocnt;
int reps;
int ls_flag;
int total_ls;
int jobcnt;
int repl;
// char* inptk[buf];

// function init
void CWD(char user[buf], char host[buf]);       // for getting prompt
void docmd(char inp[buf], int inpcnt);          // to process and perform commands
void pwd();                                     // pwd command (to get path)
void cd(char input[], int start, long int sz);  // cd command (to move through directories)
void ls(char input[], int start, long int sz);  // ls to get info on dir content
void permi(char const filename[], char name[]); // to check the permissions of file/directory
void pinfo(char input[]);                       // to get pinfo like pid, status, exec path etc
void repeat(char input[]);                      // to repeat functions
void fgbg(char input[]);                        // check if command is foreground or background
void fg_fun(char *input[buf], int cnt);         // to perform foreground commands
void bg_fun(char *input[buf], int cnt);         // to perform background commands
void check_bg();                                // to check status of background commands termination
int echo(char *str, int start);                 // echo command to print on terminal
int getword(char inp[buf]);                     // to modify the input
char *filename(char *str);                      // gets name of last dir in path
void replay(char input[]);

// void history(char input[]);
// struct Queue *his;

struct stat total_stats;                        // to store total files during ls

typedef struct Jobs                             // store details about background process
{
    char jobname[buf];
    int status;
    pid_t pid;
} Jobs;

Jobs job[100];                                  // stores 100 background process details

#endif