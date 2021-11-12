#include "main.h"

int main(void)
{
    getcwd(home, buf); // gets path of current directory and stores it in home
    jobcnt = 0;     // init jobcnt to 0
    strcpy(path, home); // copying path to home at beginning
    strcpy(prevdir, "-1");  // init prevdir
    strcpy(prnt, "~");  // setting prnt to ~ at home dir
    CWD(user, host);    // finding name of user and host to create prompt

    while (1)
    {
        inpcnt = 0; // init inpcnt to 0
        printf("<%s%s>", user, prnt);   // printing prompt
        scanf("%[^\n]%*c", inp);    // scanning input
        inpcnt = getword(inp);      // modifying input to remove extra spaces tabs and replacing with just one space
        docmd(inp, inpcnt);         // performing the command   
    }

    return 0;
}