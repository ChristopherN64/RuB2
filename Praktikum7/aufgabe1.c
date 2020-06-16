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

void main(int argc, char *args[])
{
    if(mkfifo("/tmp/fifoA",0666)<0)
    {
        printf("Fehlrer\n");
    }
    if(mkfifo("/tmp/fifoB",0666)<0)
    {
        printf("Fehlrer\n");
    }

while(1) {
        //Öffnen der Fifos
        printf("Open A mit Read im Hauptprogramm\n");
        int fdA = open("/tmp/fifoA", O_RDONLY);
        if (fdA < 0) printf("Error bei öffnen von fda Eltern\n");

        printf("Open B mit Write im Hauptprogramm\n");
        int fdB = open("/tmp/fifoB", O_WRONLY);
        if (fdB < 0) printf("Error bei öffnen von fdb Eltern\n");



        //Lesen aus Fifo A zu Großbuchstaben Konvertieren und in Fifo B schreiben
        char *input;
        printf("Lese aus fifo A in Hauptprogramm und wandel um in Großbuchstaben\n");
        while (read(fdA, input, 1)) {
            *input = toupper(*input);
            printf("Schreibe %c geschribene Zeichen: %d\n", *input, write(fdB, input, 1));
        }
        printf("Schreiben abgeschlossen warte auf Kind\n");
        while (wait(NULL));
        printf("Kind beeneder\n");
        close(fdA);
        close(fdB);
    }
}
