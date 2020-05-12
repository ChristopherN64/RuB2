#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHdl(int iSignum)
{
    if(iSignum==SIGTERM) printf("SIGTWERM\n");
    else if(iSignum==SIGINT) printf("SIGINT\n");
}


int main(void) {
    void (*signalHandler)(int);
    signalHandler=sigHdl;

    signal(SIGTERM,signalHandler);
    signal(SIGINT,signalHandler);
  for ( ; ; ) {
    pause();
    puts("main: Signal empfangen");
  }
}

