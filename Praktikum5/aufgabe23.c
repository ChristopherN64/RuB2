#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#define MAXLINE 4096

int main(int argc, char *args[]) {
  int   n, fd[2], err, pipeA[2],pipeB[2];
  pid_t pid;
  char  line[MAXLINE];
  
  err = pipe(fd);
  if (err < 0) {
    perror("pipe error");
    exit(1);
  }

  if(pipe(pipeA)<0)
  {
      perror("Pipe A error ");
      exit(1);
  }

    if(pipe(pipeB)<0)
    {
        perror("Pipe B error ");
        exit(1);
    }


  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(1);
  }     
  
  else if (pid > 0) {           /* parent */
      close(pipeA[0]); //Schließen von Ausgang von Pipe A
      close(pipeB[1]);//Schließen von Eingang vin Pipe B

      //Erstes Argument als Nachicht an Kind schicken
      write(pipeA[1],args[1],strlen(args[1]));
      char sReadB[MAXLINE];
      //Nachicht von Kind lesen
      read(pipeB[0],sReadB,MAXLINE);
      printf("Empfangene Nachicht: %s",sReadB);
      wait(NULL);
  } 
  else {                        /* child */
      close(pipeA[1]); //Schließen von Eingang von Pipe A
      close(pipeB[0]);//Schließen von Ausgang vin Pipe B

      char sRead[MAXLINE];
      //Nachicht von Elternprozess lesen
      read(pipeA[0],sRead,strlen(args[1]));
      for(int il=0; il<strlen(sRead);il++)
      {
          sRead[il]=(char) toupper((int)sRead[il]);
      }
      sleep(1);
      //Empfangene Nachicht wieder an Elternprozess schicken
      write(pipeB[1],sRead,MAXLINE);
      exit(100);
  }
  wait(NULL);
  return 0;
}
