#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#define MAXLINE 4096

void main(int argc, char *argv[])
{
    char *input;
    while(read(STDIN_FILENO,input,1))
    {
        *input=toupper(*input);
        write(STDOUT_FILENO,input,1);
    }

}
