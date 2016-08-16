/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"
#include "stdio.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int valueToFind, int values[], int n)
{
    for (int i=0; i<n; i++)
    {
        printf("%d\n",values[i]);
    }
    
    int first = 0;
    int last = n-1;
    while (true)
    {
        //printf("first:%d current %d last %d",first,(last+first)/2,last);
        
        if (last < first)
            return false;
        
        int temp = values[(last+first)/2];
        
        //printf(" temp: %d \n",temp);
        if (valueToFind == temp)
            return true;
        else if (valueToFind > temp)
        {
            first = (last+first)/2+1;
        }
        else
        {
            last = (last+first)/2-1;
        }
        
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i=0; i<n-1; i++)
    {
        for (int j=0; j<n-1-i; j++)
        {
            if (values[j]> values[j+1])
            {
                int temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
    
    return;
}