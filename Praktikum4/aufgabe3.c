#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096	/* max line length */

//Signalhandler
void sigHdl(int iSignum)
{
    if(iSignum==SIGTERM) puts("SIGTERM nichts da mit Ende\n%");
    else if(iSignum==SIGINT) puts("SIGINT nichts da mit Ende\n%");
    //Verhindern von Zombieprozessen
    else if(iSignum==SIGCHLD)
    {
        puts("Child gestorben");
        while (waitpid(-1,NULL,WNOHANG)>0);
        printf("%% ");
        fflush(stdout);
    }
}


int main(void) {
  char	buf[MAXLINE];
  pid_t   pid;
  int		status;
  int iHintergrund=0;
  //Erzeugen des Funktionspointers auf die Handlerfunktion
  void (*signalHandler)(int);
  signalHandler=sigHdl;
  //Einrichten der Signalhandler auf die Signale SIGRERM und SIGINT
  signal(SIGTERM,signalHandler);
  signal(SIGINT,signalHandler);
  signal(SIGCHLD,signalHandler);
  
  printf("%% ");  /* print prompt (printf requires %% to print %) */
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    buf[strlen(buf) - 1] = 0;	/* replace newline with null */

    //Quit Funktion
    if(strlen(buf)==1 && buf[0]=='q')
    {
        printf("TSCHÜSS\n");
        kill(getpid(),SIGKILL);
    }

    //Auswerten des & Zeichens in Befehlen
    if(buf[strlen(buf)-1]=='&')
    {
        char *befehl = strtok(buf,"&");

        //Entfernen alle in dem String ohen das & noch am ende Enthaltenten leerzeichen
        for(int il = strlen(befehl)-1;il>0;il--)
        {
            if(befehl[il]!=' ') break;
            if(befehl[il]==' ')
            {
                befehl[il]='\0';
            }
        }
        iHintergrund = 1;
    }

    if ( (pid = fork()) < 0)
      perror("fork error");
    
    else if (pid == 0) {		/* child */
      execlp(buf, buf, (char *) 0);
      printf("couldn't execute: %s\n", buf); 
      exit(127);
    }

    if(iHintergrund==1)
    {
        printf("%%");
        fflush(stdout);
    } else waitpid(pid,&status,0);


  }
  exit(0);
}
