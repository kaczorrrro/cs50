/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>
#define SIZE 150000

/**
 * from a=0 to z=25, ' = 26 and 
 * if terminator is t that means words can end here
 */
 

int wordCount = 0;
char *tempWord;
char **pointers = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
   //printf("dziaa\n");
   int wordL = strlen(word);
   int start = 0;
   int end = wordCount;
   int middle;
   
   char wordSmall [wordL+1];
   for (int i=0;i<wordL+1;i++)
   {
        wordSmall[i] = tolower(word[i]);
   }
   
   while(start<=end)
   {
        //printf("%d %d %d\n",start,middle,end);
        middle = (end+start)/2;
        int val = strcmp(wordSmall,pointers[middle]);       //zwraca -1 jesli word jest wczesniej niz to ze slownika
        
        //printf("%s\t%s\n",wordSmall,pointers[middle]);
        
        if(val==0)
        {
            return true;
        }
        else if(val<0)
        {
           
            end = middle-1;
        }
        else
        {
            
            start = middle+1;
        }
        
   }
   return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *fp = fopen(dictionary,"r");
    
    if (fp==NULL)
    {
        return false;
    }
    
    tempWord = malloc(sizeof(char)*(LENGTH+1));   //all pointers set to null
    pointers = malloc(sizeof(char*)*SIZE);
    
    while (NULL != fgets(tempWord,LENGTH + 1,fp)) //reads one word into buffer
    {
       
        
        int wordL = strlen(tempWord)-1;       //not containing terminating
        char* word = malloc(sizeof(char)*(wordL+1));    //create space for word
        strncpy(word,tempWord,wordL);    //copy data
        word[wordL] = '\0';
        pointers[wordCount] = word;
        wordCount++;

    }
    fclose(fp);
    free(tempWord);
    
    
    return true;
}




/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{   
    return wordCount;   
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i=0;i<wordCount;i++)
    {
       free(pointers[i]); 
    }
    free(pointers);
    
    return true;
}


