#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
char kodujV(char c, string key,int keyL);
int keyPos = 0;

int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("wrong input\n");
        return 1;
    }
        

    int keyL = strlen(argv[1]);
    
    for(int i=0;i<keyL;i++)
    {
        if (!isalpha(argv[1][i]))     
        {
            printf("wrong input\n");
            return 1;
        }
    }


    char tekst [200];
    fgets(tekst,200,stdin);
    int signs = strlen(tekst)-1;

    for(int i=0;i<signs;i++)
    {
        printf("%c",kodujV(tekst[i],argv[1],keyL));
    }
    printf("\n");



    return 0;
}

char kodujV(char c, string key,int keyL)
{
    if (isalpha(c))
    {
        char k = tolower(key[keyPos])-'a';
        keyPos= (keyPos+1)%keyL;

        if (islower(c))
            c = 'a'+(c-'a'+k)%26;

        else if (isupper(c))
            c = 'A'+(c-'A'+k)%26;
    }



    return c;
}

