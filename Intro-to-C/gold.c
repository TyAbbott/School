/*  Ty Abbott
      CS-1 Lab 3
      gold.c
*/

#include <stdio.h>
#include <stdlib.h>

int findOptimalPath(int [], int, int, int);
int main()
{
    FILE *readfptr;
    int i, j, length, numTimes, optimal;
    int array[6] = {3,8,9,2,5,10};
/*     readfptr = fopen("gold.txt", "r");
 *     if(readfptr==NULL)
 *     {
 *         printf("There was an issue with opening the file");
 *         return 0;
 *     }
 *     fscanf(readfptr, "%d", &numTimes);
 *     for(i=0; i<numTimes; i++)
 *     {
 *         fscanf(readfptr, "%d", &length);
 *         array = (int*)malloc(length*sizeof(int));
 *         for(j=0; j<length; j++)
 *         {
 *             fscanf(readfptr, "%d", array[j]);
 *         }
 *         optimal = findOptimalPath(array, 0, length-1, 0);
 *         printf("%d\n", optimal);
 *     }
 *     fclose(readfptr);
 */
    optimal = findOptimalPath(array,0,5,0);
    printf("%d\n", optimal);
   // free(array);
    return 0;
}

int findOptimalPath(int array[], int left, int right, int person)
{
    int i, j, me, sabrina;

    /* Breakout statements here, once it gets down to 2 selections */
    if(right-left==1)
    {
        if(array[left]>array[right])
        {
            if(person==0)
            {
                me = array[left];
                sabrina = array[right];
            }
            else
            {
                sabrina = array[left];
                me = array[right];
            }
        }
        else
         {
             if(person==0)
             {
                 me = array[right];
                 sabrina = array[left];
             }
             else
             {
                 me = array[left];
                 sabrina = array[right];
             }
         }
    }
    else if(person==0)
    {
        person = 1;
        if(array[right]+findOptimalPath(array,left, right-1, person)>=array[left]+findOptimalPath(array,left+1,right, person))
            me = array[right]+findOptimalPath(array,left, right-1, person);
        else
            me = array[left]+findOptimalPath(array,left+1,right, person);
    }
    else
    {
        person=0;
        if(array[left]+findOptimalPath(array,left+1,right, person)>=array[right]+findOptimalPath(array,left,right-1, person))
            sabrina = array[left]+findOptimalPath(array,left+1, right, person);
        else
            sabrina = array[right]+findOptimalPath(array,left, right-1, person);
    }
    return me-sabrina;
}


