#include <signal.h>
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"


void main()
{
    printf("GO\n");
    sleep(3);
    printf("STOP\n");
    kill(getpid(),SIGTERM);
}


