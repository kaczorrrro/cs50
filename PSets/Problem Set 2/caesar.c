#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
char koduj(char c,int k);


int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("Wrong input");
        return 1;
    }
       
    int k = atoi(argv[1]);
    if(k<0)
    {
        printf("Wrong input");
        return 1;
    }

    k = k%26;

    char tekst [200];
    fgets(tekst,200,stdin);
    int signs = strlen(tekst)-1;

    for(int i=0;i<signs;i++)
    {
        printf("%c",koduj(tekst[i],k));
    }
    printf("\n");



    return 0;
}

char koduj(char c, int k)
{
    if (islower(c))
        c = 'a'+(c-'a'+k)%26;

    else if (isupper(c))
        c = 'A'+(c-'A'+k)%26;

    return c;
}


