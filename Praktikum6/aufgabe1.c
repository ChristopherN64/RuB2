#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#define MAXLINE 4096

void main(int argc, char *argv[])
{
    char input[1];
    while(read(STDIN_FILENO,input,1))
    {
        input[0]=toupper(input[0]);
        write(STDOUT_FILENO,input,1);
    }

}
