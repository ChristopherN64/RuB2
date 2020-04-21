#include <stdio.h>
#include <stdlib.h>

int quersumme(int zahl)
{
    int il;
    int qs=0;
    while(zahl!=0)
    {
        qs+=zahl%10;
        zahl/=10;
    }

    return qs;

}

int main()
{
    int x = 0;
    
    printf("Geben Sie ein Zahl ein: ");
    scanf("%i", &x);
    printf("Quersumme von %d: %d\n", x, quersumme(x));

    return EXIT_SUCCESS;
}
