#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#define MAXLINE 4096

void main(int argc, char *args[]) {

    //Öffnen der Fifos
    printf("Open A mit Write im Testprogramm\n");
    int fdAk = open("/tmp/fifoA", O_WRONLY);
    if (fdAk < 0) printf("Error bei öffnen von fda Kind\n");

    printf("Open B mit Read im Testprogramm\n");
    int fdBk = open("/tmp/fifoB", O_RDONLY);
    if (fdBk < 0) printf("Error bei öffnen von fdb Kind\n");


    printf("Schreibe %s in fifo A in Testprogramm\n0", args[1]);
    write(fdAk, args[1], strlen(args[1]));
    close(fdAk);


    sleep(5);
    //Lesen aus Fifo A zu Großbuchstaben Konvertieren und in Fifo B schreiben
    char *input;
    printf("Lese aus Fifo B in Testprogramm\n");
    printf("fdb: %d\n", fdBk);
    while (read(fdBk, input, 1))
    {
        printf("Lesen %c\n", *input);
    }
    printf("lesen beendet\n");
    fflush(stdout);
    close(fdBk);
}
