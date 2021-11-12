#include "main.h"

int alter = 1;

char *filename(char *str) // function to find file name
{
    const char ch = '/';
    char *s = strrchr(str, ch); //fetches last char '/' in the string
    if (s == NULL)
    {
        return str;
    }
    else
    {
        s++;
        return s;
    }
}

void cd(char input[], int start, long int sz)
{
    int len = sz, check;
    if (len == start) // when only cd is given as input
    {
        check = chdir(home); // goes to home directory
        strcpy(prevdir, "");
        strcpy(prevdir, path); // stores path to previous path
        strcpy(prevprnt, "");
        strcpy(prevprnt, prnt); // stores path to prev prnt path (in prompt)

        pwd(); // prints the path
        strcpy(prnt, "");
        strcpy(prnt, "~"); // sets print to ~
        strcpy(path, "");
        strcpy(path, home); // sets path to home
    }
    else if (len > 3) // to process cd with other inputs/flags
    {
        if (input[start] == '.' && input[start + 1] == '.' && (start >= len - 3)) // for cd ..
        {
            char *fn;
            if (strcmp(prnt, "~") == 0) // to check if we are at home dir or not
            {
                strcpy(path, home);
            }
            fn = filename(path); // finds name of current directory
            int dlen = strlen(fn);
            char dup[buf] = "", dup1[buf] = "";
            strncpy(dup, path, strlen(path) - dlen - 1); // stores path of prev directory in dup
            if (strcmp(prnt, "~") == 0)                  // stores path of prnt according to current location
            {
                strcpy(dup1, dup);
                printf("%s\n", dup); // stores path of prev dir in prnt and outputs path
            }
            else
            {
                strncpy(dup1, prnt, strlen(prnt) - dlen - 1); // stores path from our home to prev dir
            }
            strcpy(prevdir, "");
            strcpy(prevdir, path); // stores current path to prevdir
            strcpy(prevprnt, "");
            strcpy(prevprnt, prnt); // stores current prnt to prevprnt
            strcat(dup1, "\0");
            strcat(dup, "\0");
            strcpy(path, "");
            strcpy(path, dup); // updates path
            strcpy(prnt, "");
            strcpy(prnt, dup1); // updates prnt
            chdir(path);        // moves to prev dir
        }
        else if (input[start] == '-' && (start >= len - 3)) // to handle cd -
        {
            if (strcmp(prevdir, "-1") == 0) // if no prevdir given, outputs error message
            {
                printf("bash: cd: OLDPWD not set\n");
            }
            else
            {
                char dup[buf] = "", dup1[buf] = "";
                strcpy(dup, prevdir);   // stores prevdir to dup
                strcpy(dup1, prevprnt); // stores prevprnt to dup1
                strcpy(prevdir, "");
                strcpy(prevprnt, "");
                strcpy(prevdir, path);  // update prevdir to current path
                strcpy(prevprnt, prnt); // update prevprnt to current prnt
                strcpy(path, dup);      // update path to dup(prevdir before update)
                strcpy(prnt, dup1);     // update prnt to dup1(prevprnt before update)
                chdir(path);            // moves to prev dir
                pwd();                  // prints the path
            }
        }
        else if (input[start] == '.' && (start >= len - 2)) // handles cd .
        {
            // do nothing
        }
        else if (input[start] == '~' && (start >= len - 2)) // handles cd ~
        {
            strcpy(prevdir, "");
            strcpy(prevdir, path); // updates prevdir to current path
            strcpy(prevprnt, "");
            strcpy(prevprnt, prnt); // updates prevprnt to current prnt
            strcpy(path, "");
            strcpy(path, home); // updates path to home directory
            strcpy(prnt, "");
            strcpy(prnt, "~"); // updates prnt to ~
            chdir(home);       // moves to home dir
        }
        else
        {
            int ex = 0;
            char temp[100] = "", dup[buf] = "./";
            if (input[strlen(input - 1)] == ' ')    // if space at end, we remove it 
            {
                ex++;
            }
            strncpy(temp, input + start, len - start + ex); // copies the path in input to temp
            strcat(dup, temp);                              // creates a final path of input
            check = chdir(dup);                             // moves to that path
            if (check >= 0)                                 // checks if its a valid path
            {
                strcpy(prevdir, "");
                strcpy(prevdir, path); // stores current path to prevdir
                strcpy(prevprnt, "");
                strcpy(prevprnt, prnt); // stores current prnt to prev prnt
                strcat(path, "/");
                strcat(path, temp);          //  creates a final path
                if (strcmp(path, home) == 0) // if final path == home
                {
                    strcpy(prnt, "");
                    strcpy(prnt, "~"); // updates prnt to ~
                }
                else
                {
                    strcat(prnt, "/");
                    strcat(prnt, temp); // updates prnt to desired path
                }
            }
            else
            {
                printf("bash: cd: %s: No such file or directory\n", temp); // error message
            }
        }
    }
}
