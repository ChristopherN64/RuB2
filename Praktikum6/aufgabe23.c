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

  //pipe zum senden von Nachichten von Elternprozess an Kindprozess
  if(pipe(pipeA)<0)
  {
      perror("Pipe A error ");
      exit(1);
  }
  //pipe zum senden von Nachichten von Kinprozess an Elternprozess
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
      printf("Schreibe an Kindprozess\n");
      sleep(3);
      write(pipeA[1],args[1],strlen(args[1]));

      char sReadB[MAXLINE];
      //Nachicht von Kind lesen
      printf("Lese von Pipe\n");
      read(pipeB[0],sReadB,strlen(args[1]));
      printf("Empfangene Nachicht: %s\n",sReadB);

      wait(NULL);
  }
  else {
      /* child */

      close(pipeA[1]); //Schließen von Eingang von Pipe A
      close(pipeB[0]);//Schließen von Ausgang vin Pipe B

      sleep(1);

      printf("Pipe1 umlegen\n");
      dup2(pipeA[0],STDIN_FILENO);      //Den Inputkanal von STDIN auf den Ausgang der Nachichtenpipe des Elternprozesses umlegen
      printf("Pipe1 umlegen\n");
      dup2(pipeB[1],STDOUT_FILENO);     //Den Outputkanal von STDOUT auf den Eingang der Nachichtenpipe des Kindprozesses an den Elternprozess umlegen
      execlp("/home/cnieder/CLionProjects/RuB2/Praktikum6/start.sh","start.sh",NULL);
  }
  wait(NULL);
  return 0;
}
