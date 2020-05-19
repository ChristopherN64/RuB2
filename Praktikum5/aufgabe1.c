#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"

void main(void)
{
    int fd[2];
    pipe(fd);
    printf("FileD1: %d\nFileD2: %d\n",fd[0],fd[1]);
    char *sWrite = "Hallo";
    write(fd[1],sWrite,6);
    char sRead[7];
    read(fd[0],sRead,6);
    printf("Aus pipe gelesen: %s",sRead);

}