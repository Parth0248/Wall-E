#include "main.h"

void pwd(){
	
    char *curr_dir = NULL;
	printf("%s\n", getcwd(curr_dir, buf));	// prints path of current directory using getcwd
}