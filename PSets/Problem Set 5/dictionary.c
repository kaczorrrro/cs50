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


/**
 * from a=0 to z=25, ' = 26 and 
 * if terminator is t that means words can end here
 */
 

level* firstLvl = NULL;
int wordCount = 0;
char *tempWord;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int wordL = strlen(word);
    
    level *curL = firstLvl;
    if (firstLvl == NULL)
        printf("first lvl null");
    
    for (int i=0;i<wordL;i++)
    {
       // for (int j=0;j<POSITIONS;j++)
        {
        //    printf("value of pos %d is %d\n",j,(int)(curL->letters[j]));
        }
        
        int hash = charToHash(word[i]);
        //printf("Im looking for %d\n",hash);
        
        if(curL->letters[hash] == NULL)
        {
            //printf("letters ended i = %d\n",i);
            return false;   
        }
        //printf("terminator %d\n",(int)(curL->terminator));
        curL = curL->letters[hash];
    }
    //printf("terminator %d\n",(int)(curL->terminator));
    if(curL->terminator == 't')
    {
        return true;
    }
    //printf("no terminator here\n");
    

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
    
    firstLvl = calloc(sizeof(level),1);   //first level created by default
    
    
    while (NULL != fgets(tempWord,LENGTH + 1,fp)) //reads one word into buffer
    {
       
        wordCount++;
        int wordL = strlen(tempWord)-1;       //not containing terminating
        
        //printf("%d word l\n",wordL);
        //char* word = malloc(sizeof(char)*(wordL+1));    //create space for word
        //strncpy(word,tempWord,wordL);    //copy data
        tempWord[wordL] = '\0';         //terminate word
        //printf("Im adding word %s\n",word);
        level* currentLvl = firstLvl;
       
       

        
        for (int i=0; i<wordL; i++)     //will be ok if all words in the dic are lowercase
        {
            int charP = charToHash(tempWord[i]);    // charP is index where to put this char
            
            //printf("%d is addad (letter %c)\n",charP,tempWord[i]);
            if(currentLvl->letters[charP] == NULL)  //checks if next lvl exists
            {
              //  printf("added\n");
                currentLvl->letters[charP] = calloc(sizeof(level),1);
            }
            else
            {
              //  printf("already there\n");
            }

            currentLvl = currentLvl->letters[charP];    //goes to next lvl

            if (i==wordL-1)           //sets terminator on struct corresponding to /0 char
            {
                currentLvl->terminator = 't'; 
            }
            
        }
        
        //printf("%d\n",wordL);
        //printf("%s\n",tempWord);

    }
    fclose(fp);
    
    
    return true;
}

int charToHash(char c)
{
    c = tolower(c);
    if (c=='\'')
        return 26;
    else if (c == '\0')
        return 27;
    else if ('a'<=c && 'z'>=c)
        return c-'a';   
    else
    {
        printf("Error in hashing\n");
        return -100; 
        
    }
        
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
    free(tempWord);
    return unloadLvl(firstLvl);
}

bool unloadLvl(level* lvl)
{
    
    for(int i=0;i<POSITIONS;i++)
    {
        if (lvl->letters[i] != NULL)
        {
            unloadLvl(lvl->letters[i]);
        }
    }
    free(lvl);
    return true;
}
