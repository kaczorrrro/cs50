#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    double n = atof(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    if(n<0)
    {
        return -1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int oldHeight = abs(bi.biHeight);
    int oldWidth = bi.biWidth;
    
    //resizie effect on headers
    bi.biWidth =(int)(bi.biWidth*n);
    bi.biHeight = (int)(bi.biHeight*n);
    
    int oldPaddedBytes = (4-(oldWidth*sizeof(RGBTRIPLE))%4)%4;
    int paddedBytes = (4-(bi.biWidth*sizeof(RGBTRIPLE))%4)%4;
    
    bi.biSizeImage = bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE) + abs(bi.biHeight) * paddedBytes;
    bf.bfSize = bi.biSizeImage + 54;
    

    fwrite(&bf,sizeof(BITMAPFILEHEADER),1,outptr);
    fwrite(&bi,sizeof(BITMAPINFOHEADER),1,outptr);
    

    
    double yPos = 0;
    int yPosTotal = 0;
    int lastLine = -1;  //must be initialized to 0
    int oldLineLength = 3*oldWidth+oldPaddedBytes;
    
    int yCounter = 0;
    while(yPosTotal<oldHeight)
    {
        yCounter++;
        
        
        double xPos = 0;
        int xPosTotal = 0;
        
        
        int colors [oldWidth];        //array for color values in one line
        
        if( lastLine!=yPosTotal ) //read new data only if line changes
        {
            for(int j=0,m=(yPosTotal-lastLine-1);j<m;j++)//skips lines of image if n<1
            {
                fseek(inptr,oldLineLength,SEEK_CUR);
            }
            
            lastLine = yPosTotal;
            
            for (int j=0;j<oldWidth;j++)
            {
                fread(&(colors[j]),3,1,inptr);   
            }
            fseek(inptr,oldPaddedBytes,SEEK_CUR);
            //printf("Reading from line %d\n",yPosTotal);
        }
        
        int colorsOut [bi.biWidth];
        for(int j=0;j<bi.biWidth;j++)       //fills new array with color values
        {
            colorsOut[j] = colors[xPosTotal];
            
            //xPos += 1/n;
            xPos = (j+1)/n;
            xPosTotal = (int)xPos;
        } 
        
        for(int j=0;j<bi.biWidth;j++)       //writes values
        {
            fwrite(&(colorsOut[j]),3,1,outptr);
        }
        
        for(int j=0;j<paddedBytes;j++)
                putc(0x00,outptr);
            
        
  
        //yPos += 1/n;
        yPos = yCounter/n;
        yPosTotal = (int)yPos;
    }
    

    fclose(inptr);
    fclose(outptr);
    
    return 0;
    
}    
