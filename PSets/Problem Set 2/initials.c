
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char name[100];
    fgets(name,100,stdin);
    int size = strlen(name);
    char initials [10];
    initials[0] = name[0];
    int inNum = 1;
    for (int i=1;i<size;i++)
    {
       if(name[i] == ' ')
       {
            initials[inNum] = name[i+1];
            inNum++;
       }
    }
    for (int i=0;i<inNum;i++)
        printf("%c",toupper(initials[i]));
    printf("\n");    



    return 0;
}
