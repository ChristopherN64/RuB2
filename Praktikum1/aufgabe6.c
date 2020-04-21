#include <stdio.h>
#include <stdlib.h>

int ascii2int(char *s)
{
    int zahl = 0;
    int il;

    for(il=0; s[il] <='9' && s[il] >='0';il++)
    {
        int i;
        i=(s[il]-'0');
        zahl=zahl*10+i;
    }
    return zahl;
}

int main()
{
    char *zahl[] = {"53463",
                    "44227 Dortmund",
                    "01234"
    };

    for (int i = 0; i < sizeof(zahl) / sizeof(char *); i++)
    {
        printf("Der String '%s' ist als Integer darstellt '%d'\n",
               zahl[i], ascii2int(zahl[i]));
    }

    return EXIT_SUCCESS;
}
