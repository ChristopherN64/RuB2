#include <stdio.h>
#include <string.h>

void to_upper_case(char in[], char out[])
{
    int il;
    for(il=0;il< 30;il++)
    {
        if(in[il]>='a' && in[il]<='z')
        {
            out[il]=(in[il]-32);
        }
        else
            {
                out[il]=in[il];
        }
    }
}

int main()
{
    char input[30] = "a-6430 ötztal-bahnhof";
    char output[30];
    
    printf("Original:    %s\n", input);
    to_upper_case(input, output);
    printf("Umgewandelt: %s\n", output);
}
