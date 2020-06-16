#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *schlafe(void *iSchlafzeit);

int main (void)
{
    int status;
    int st[3];
    pthread_t thread[3];

    scanf("%d",&st[0]);
    scanf("%d",&st[1]);
    scanf("%d",&st[2]);

    /* Starte den Thread */


    int il;
    for(il=0;il<3;il++)
    {
        status=pthread_create(&thread[il],NULL,schlafe,&st[il]);
        printf("Starte Thread %d mit ID: %d\n",il,thread[il]);
        if(status!=0){
            fprintf(stderr,"Error: Konnte Thread nicht erzeugen\n");
            exit(-1);
        }
    }


    /* Warte auf Terminierung */
    for(il=0;il<3;il++)
    {
        pthread_join(thread[il],NULL);
        printf("Der Thread %d ist Terminiert\n",thread[il]);
    }


    exit(0);
}

void *schlafe(void *iSchlafzeit){

    int *st = (int*)iSchlafzeit;
    printf("Schlafe %d sekunden\n",*st);
    sleep(*st);

    return NULL;
}
