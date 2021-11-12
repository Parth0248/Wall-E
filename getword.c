#include "main.h"

int getword(char inp[buf])  // modifies the input by removing extra spaces, tabs and replacing them with single space
{
    int i, x;
    for (i = x = 0; inp[i]; ++i)
        if (!isspace(inp[i]) || (i > 0 && !isspace(inp[i - 1])))
        {
            if (isspace(inp[i]))
            {
                inp[x++] = ' ';
            }
            else
            {
                inp[x++] = inp[i];
            }
        }
    inp[x++] = '\0';
    return x;
}