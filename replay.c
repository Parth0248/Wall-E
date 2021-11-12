#include "main.h"

void initk(char *input[buf]) // inits the array of words (char* c[buf])
{
    int i = 0;
    while (input[i] != NULL)
    {
        input[i++] = NULL;
    }
}

void replay(char input[])
{
    int flag = 0, i = 0, k = 2, period = 0;

    initk(c); // init c

    char replayinp[buf] = "";
    char dup[buf] = "";
    strcpy(dup, input);           // makes duplicate of input string
    char *tok = strtok(dup, " "); // tokenizes duplicate with " " as delimiter

    while (tok != NULL) // traverses through duplicate and stores each work in c (char* c[buf])
    {
        c[i] = tok;
        i++;
        tok = strtok(NULL, " ");
    }
    // replay -command echo "hi" -interval 3 -period 6
    if (strcmp(c[1], "-command") == 0)
    {
        while (strcmp(c[k], "-interval") != 0 || k != i)
        {
            strcat(replayinp, c[k]);
            strcat(replayinp, " ");
            k++;
        }
        if (k == i)
        {
            printf("Invalid Input\n");
            return;
        }
        if (strcmp(c[k], "-interval") == 0)
        {
            k++;
            repl = atoi(c[k]);
            k++;
        }
        if (strcmp(c[k], "-period") == 0)
        {
            k++;
            period = atoi(c[k]);
        }
    }
    
    printf("Herer%d\n", reps);
    reps = period / repl;
    while (reps-- > 0)
    {
        printf("%s..\n", replayinp);
        docmd(replayinp, 1);
    }
}