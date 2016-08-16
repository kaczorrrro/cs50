/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 #include <stdio.h>
 #include <stdlib.h>
 
 int filesDone = 0;
 

int main(int argc, char* argv[])
{
    FILE* card = fopen("card.raw","r");
    FILE* out = NULL;
    if (card==NULL)
        return -1;
    int blockSize = 512;
    unsigned char tempData [blockSize];
    int started = 0;
    int newFile = 0;
    char* name = malloc(10*sizeof(char));
    while(1)
    {
        if (feof(card)!=0)
        {
            break;
        }
        
        int read = fread(tempData,1,blockSize,card);
        
        for (int i=0;i<blockSize-3;i++)
        {
            if( (tempData[i]==255 && tempData[i+1]==0xd8 && tempData[i+2]==0xff) && (tempData[i+3]==0xe0 || tempData[i+3]==0xe1))          
            {
                started = 1;
                newFile = 1;
            }
        }
        
        if (started)
        {
            if(newFile)
            {
                if(out!=NULL)
                    fclose(out);
                
                sprintf(name,"%.3d.jpg",filesDone);
                //printf("%s\n",name);
                out = fopen(name,"w");
                newFile = 0;
                filesDone++;
            }
            
            if(out!=NULL)
            {
                fwrite(tempData,read,1,out);
            }
        }
        
        
        
    }
    fclose(out);
    free(name);
    fclose(card);
    return 0;
}


