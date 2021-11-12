#include "main.h"

void permi(char const filename[], char name[])
{
    struct stat inpfile;

    if (stat(filename, &inpfile) == -1) // error handling if the file doesnot exists or has some issues
    {
        char error[150] = "";
        perror(error); // prints the error on screen
        return;
    }
    struct passwd *usr;     // to store user info 
    usr = getpwuid(inpfile.st_uid); // gets user info
    struct group *grp;      // to store grp info
    grp = getgrgid(inpfile.st_gid); // gets grp info

    // checks for permissions for user group and others
    printf((S_ISDIR(inpfile.st_mode)) ? "d" : "-"); 
    printf((inpfile.st_mode & S_IRUSR) ? "r" : "-");
    printf((inpfile.st_mode & S_IWUSR) ? "w" : "-");
    printf((inpfile.st_mode & S_IXUSR) ? "x" : "-");
    printf((inpfile.st_mode & S_IRGRP) ? "r" : "-");
    printf((inpfile.st_mode & S_IWGRP) ? "w" : "-");
    printf((inpfile.st_mode & S_IXGRP) ? "x" : "-");
    printf((inpfile.st_mode & S_IROTH) ? "r" : "-");
    printf((inpfile.st_mode & S_IWOTH) ? "w" : "-");
    printf((inpfile.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %ld", inpfile.st_nlink);   // number of hardlinks for the file 
    printf(" %s", usr->pw_name);        // prints user name
    printf(" %s", grp->gr_name);        // prints grp name
    printf(" %ld", inpfile.st_size);    // prints size of file/directory
    char time[100];               
    struct tm *temp;
    temp = gmtime(&inpfile.st_mtime);   // stores time of creation of input file/directory
    strftime(time, 100, "%b %d %R", temp);  // converts the time to desired format using flags
    printf(" %s %s\n", time, name);         // prints time and name of file/directory
}

void ls(char input[], int start, long int sz)
{
    int len = sz;   
    ls_flag = 0;            
    struct dirent *de;
    DIR *dr = opendir(".");     // opens current directory
    if (start == len || ((len == start + 1 && input[start] == ' '))) // if only ls is given as input
    {
        if (dr == NULL)     // error handling
        {
            printf("ls: cannot access '%s': No such file or directory\n", input);
            return;
        }
        while ((de = readdir(dr)) != NULL) // traverses the current directory
        {
            if (de->d_name[0] != '.')       // prints names of files/folders that are not hidden
            {
                printf("%s\t", de->d_name);
                ls_flag = 1;                // sets flag to 1
            }
        }
        printf("\n");
        closedir(dr);                   // closes dr
    }
    else if (len > start && input[start] == ' ')    // if ls is given along with flags and/or path
    {
        char dupinput[buf] = "";        
        strcpy(dupinput, input);        // stores input in duplicate file
        const char m[2] = "-";
        char *fg;
        const char st[2] = " ";
        char *part;
        int start = 0, count = 0, lflag = 0, aflag = 0;

        fg = strtok(dupinput, m);   // tokenize input taking "-" as delimiter
        fg = strtok(NULL, m);       // skips the ls token
        while (fg != NULL)  // runs through entire input and checks for l and a flag in different combinations
        {
            if (strncmp(fg, "l", 1) == 0 && !isalpha(fg[1]))  
            {
                lflag = 1;
            }
            else if (strncmp(fg, "a", 1) == 0 && !isalpha(fg[1]))
            {
                aflag = 1;
            }
            else if (strncmp(fg, "al", 2) == 0 || strncmp(fg, "la", 2) == 0 && !isalpha(fg[2]))
            {
                lflag = 1;
                aflag = 1;
            }
            else
            {
                printf("ls: invalid line width: '%s'\n", fg);   // error handling 
                return;
            }
            fg = strtok(NULL, m);
        }

        part = strtok(input, st);   // tokenize input taking " " as delimiter
        part = strtok(NULL, st);    // skips the ls token
        while (part != NULL)    // runs through entire input and calls ls on different files/directories/path
        {
            if (strncmp(part, "~", 1) == 0 && !isalpha(part[1]))    // to handle default case "~" {ls home}
            {
                char temp[1000] = "";
                strcat(temp, home);
                DIR *dr = opendir(temp);
                struct dirent *de;
                total_ls = 0;
                while ((de = readdir(dr)) != NULL)
                {
                    if (lflag && aflag) // both a and l flag
                    {
                        char tm[100] = "";
                        strcpy(tm, temp);
                        strcat(tm, "/");
                        strcat(tm, de->d_name);
                        lstat(de->d_name, &total_stats);
                        total_ls += total_stats.st_blocks;
                        permi(tm, de->d_name);
                    }
                    else if (lflag == 1 && de->d_name[0] != '.')    // only l flag
                    {
                        char tm[100] = "";
                        strcpy(tm, temp);
                        strcat(tm, "/");
                        strcat(tm, de->d_name);
                        lstat(de->d_name, &total_stats);
                        total_ls += total_stats.st_blocks;
                        permi(tm, de->d_name);
                    }
                    else if (lflag == 0 && aflag == 1)  // only a flag
                    {
                        printf("%s\t", de->d_name);
                    }
                    else if (lflag + aflag == 0 && de->d_name[0] != '.') // no flag
                    {
                        printf("%s\t", de->d_name);
                    }
                }
                if (total_ls > 0)   // prints total if l flag is called
                    printf("total %d\n", total_ls / 2);
                else
                    printf("\n");

                ls_flag = 1;
            }
            else if (strcmp(part, "-l") != 0 && strcmp(part, "-al") != 0 && strcmp(part, "-la") != 0 && strcmp(part, "-a") != 0) // for general cases
            {
                char temp[1000] = "./";
                strcat(temp, part);
                DIR *dr = opendir(temp);
                struct dirent *de;

                if (dr == NULL) // error handling 
                {
                    printf("ls: cannot access '%s': No such file or directory\n", part);
                }
                else
                {
                    printf("%s:\n", part);  // prints name of path / dir / file
                    total_ls = 0;
                    while ((de = readdir(dr)) != NULL)  // traverses and calls ls like done above
                    {
                        if (lflag && aflag)
                        {
                            char tm[100] = "";
                            strcpy(tm, temp);
                            strcat(tm, "/");
                            strcat(tm, de->d_name);
                            lstat(de->d_name, &total_stats);
                            total_ls += total_stats.st_blocks;
                            permi(tm, de->d_name);
                        }
                        else if (lflag == 1 && de->d_name[0] != '.')
                        {
                            char tm[100] = "";
                            strcpy(tm, temp);
                            strcat(tm, "/");
                            strcat(tm, de->d_name);
                            lstat(de->d_name, &total_stats);
                            total_ls += total_stats.st_blocks;
                            permi(tm, de->d_name);
                        }
                        else if (lflag == 0 && aflag == 1)
                        {
                            printf("%s\t", de->d_name);
                        }
                        else if (lflag + aflag == 0 && de->d_name[0] != '.')
                        {
                            printf("%s\t", de->d_name);
                        }
                    }
                    if (total_ls > 0)
                        printf("total %d\n", total_ls / 2);
                    else
                        printf("\n");

                    ls_flag = 1;
                }
            }

            part = strtok(NULL, st);
        }

        if (ls_flag == 0)   // for handling cases where only a and/or l flags are given
        {
            total_ls = 0;
            while ((de = readdir(dr)) != NULL)  // executes same as above
            {
                if (lflag && aflag)
                {
                    char tm[100] = "./";
                    strcat(tm, de->d_name);
                    lstat(de->d_name, &total_stats);
                    total_ls += total_stats.st_blocks;
                    permi(tm, de->d_name);
                }
                else if (lflag == 1 && de->d_name[0] != '.')
                {
                    char tm[100] = "./";
                    strcat(tm, de->d_name);
                    lstat(de->d_name, &total_stats);
                    total_ls += total_stats.st_blocks;
                    permi(tm, de->d_name);
                }
                else if (lflag == 0 && aflag == 1)
                {
                    printf("%s\t", de->d_name);
                }
                else if (lflag + aflag == 0 && de->d_name[0] != '.')
                {
                    printf("%s\t", de->d_name);
                }
            }
            if (total_ls > 0)
                printf("total %d\n", total_ls / 2);
            else
            {
                printf("\n");
            }
            ls_flag = 1;
        }
    }
}
