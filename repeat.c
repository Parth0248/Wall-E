#include "main.h"

void repeat(char input[])   // repeats functions
{
    reps = 0;
    const char s[2] = " ";
    char *tok, cmd[buf] = "", call[buf] = "";
    tok = strtok(input, s);     // tokenizes input with " " as delimiter
    tok = strtok(NULL, s);      // skips the command
    reps = atoi(tok);           // converts number of repitions in int form
    tok = strtok(NULL, s);      // skips the number of reps

    while (tok != NULL)         // stores rest of input in a different string
    {
        strcat(call, tok);      
        strcat(call, " ");
        tok = strtok(NULL, s);
    }
    strcat(call, "\0");
    while (reps-- > 0)      // calls the input reps number of times
    {
        docmd(call, strlen(call));
    }
}