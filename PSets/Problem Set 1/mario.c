#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = -1;
    while (height<0 || height >23)
    {
        printf("podaj wysokosc\n");
        height = GetInt();
    }
    
    int znakowLacznie = height+1;
    int haszy = 2;
    int spacji = znakowLacznie-haszy;
    
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<spacji;j++)
        {
            printf(" ");
        }
        
        for (int j=0;j<haszy;j++)
        {
            printf("#");
        }
        haszy++;
        spacji--;
        printf("\n");
    }
}
