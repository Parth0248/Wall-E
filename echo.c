#include "main.h"

int echo(char *str, int start)
{
    int i = start;
    // while (str[i])       // prints the input string on terminal without spaces
    // {
    //     if (str[i] != ' ')
    //     {
    //         printf("%c", str[i]);
    //     }
    //     i++;
    // }
    printf("%s", str + i);      // prints the input string on terminal with spaces    
    printf("\n");
    return i;
}