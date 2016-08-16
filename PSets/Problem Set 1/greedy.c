#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    float kwota = -1.0;
    while (kwota<0)
    {
        printf("podaj kwote");
        kwota = GetFloat();
    }
    
    int kwotaDobra = lround(kwota*100);
    
    int n25 = kwotaDobra/25;
    kwotaDobra = kwotaDobra%25;
    
    int n10 = kwotaDobra/10;
    kwotaDobra = kwotaDobra%10;
    
    int n5 = kwotaDobra/5;
    kwotaDobra = kwotaDobra%5;
    
    //printf("potrzeba %dx25, %dx10, %dx5, %dx1\n",n25,n10,n5,kwotaDobra);
    printf("%d\n",n25+n10+n5+kwotaDobra);
}
