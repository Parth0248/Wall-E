#include "main.h"

void docmd(char inp[buf], int inpcnt)
{
    const char s[2] = ";";
    char *tk;
    int start = 0;
    
    tk = strtok(inp, s);    // tokenizes modified input with ";" as delimiter

    while (tk != NULL)  // walk through other tokens
    {
        if(strncmp(tk,"replay",6) == 0){
            replay(tk);
        }
        else if (strncmp(tk, "echo ", 5) == 0 || strncmp(tk, " echo ", 6) == 0) // checks for echo command 
        {
            start = 5;          
            if (tk[start] == 'o')   // sets starting point of the input after echo accordingly
                start++;
            start = echo(tk, start); // calls echo command with entire token and start as input
        }
        else if ((strncmp(tk, "pwd", 3) == 0) || strncmp(tk, " pwd", 4) == 0 || strncmp(tk, "pwd ", 4) == 0 || strncmp(tk, " pwd ", 5) == 0)    // checks for pwd command
        {
            pwd();  // calls pwd command
        }
        else if ((strncmp(tk, "cd ", 3) == 0) || strncmp(tk, " cd ", 4) == 0 || strncmp(tk, "cd", 2) == 0)  // checks for cd command
        {
            if (strncmp(tk, "cd ", 3) == 0)
            {
                start = 3;
            }
            else if (strncmp(tk, " cd ", 3) == 0)
            {
                start = 4;
            }
            else
            {
                start = 2;
            }                               // sets start accordingly
            cd(tk, start, strlen(tk));      // calls cd command
        }
        else if (strncmp(tk, "ls", 2) == 0 || strncmp(tk, " ls", 3) == 0)   // checks for ls command
        {
            if (strncmp(tk, "ls", 2) == 0) 
            {
                start = 2;
            }
            else
            {
                start = 3;
            }                   // sets start accordingly
            ls(tk, start, strlen(tk));  // calls ls command
        }
        else if (strncmp(tk, "pinfo", 5) == 0 || strncmp(tk, " pinfo", 6) == 0)    // checks for pinfo command
        {
            pinfo(tk);          // calls pinfo command
        }
        else if (strncmp(tk, "repeat ", 7) == 0 || strncmp(tk, " repeat ", 8) == 0)   // checks for repeat command
        {
            repeat(tk);     // calls repeat command
        }
        else
        {
            fgbg(inp);      // calls foreground background commands and handles error inside it
        }
        tk = strtok(NULL, s); // moves to next token
    }
}