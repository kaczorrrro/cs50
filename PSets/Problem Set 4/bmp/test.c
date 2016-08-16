#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        return 1;
    }
    if(argv[1]==NULL)
    {
        return 2;
    }
    
    FILE* file = fopen(argv[1],"r");
    if (file==NULL)
        return 3;
        
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    
    fread(&bf,sizeof(BITMAPFILEHEADER),1,file);
    fread(&bi,sizeof(BITMAPINFOHEADER),1,file);
    
    printf("%d\n",bi.biWidth);
        
        
}
