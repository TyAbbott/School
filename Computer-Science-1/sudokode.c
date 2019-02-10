/* Ty Abbott
   1/20/16
   COP 3502-1
   A Sudoku Puzzle Checker Program
   sudokode.c */

#define SIZE 9

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void checkPuzzle(int [], int);
int* readInput(int);
int myPow(int, int);

int main()
{
    int i, j, v, n;
    int *puzzle;

    printf("How many puzzles are you checking?\n");
    scanf("%d", &n);

    puzzle = readInput(n);
    checkPuzzle(puzzle,n);
    free(puzzle);

}

int* readInput(int numTimes)
{
    int i, j, *array;
    array = (int*)malloc((SIZE*numTimes)*sizeof(int));
    if(array==NULL)
    {
        printf("There was a problem with allocating memory.\n");
        free(array);
    }
    for(i=0; i<numTimes; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            scanf("%d", &array[j+(i*9)]);
        }
    }
    return array;
}

void checkPuzzle(int array[], int numTimes)
{
    int i, j, k, m, t, g, q, e, *col, *row, *box, num, remainder, correct;

    for(m=0; m<numTimes; m++)
    {
        correct = 0;
        for(j=0; j<SIZE; j++)
        {
            row = (int*)calloc(SIZE,sizeof(int));
            if(row==NULL)
            {
                printf("There was an error with the memory allocation.\n");
                free(row);
                break;
            }
            for(t=0; t<SIZE; t++)
            {
                remainder = array[j+(m*9)]%(myPow(10,t+1));

                if(row[remainder]==0)
                    row[remainder]++;
                else
                {
                    correct = 1;
                    continue;
                }
            }

        }
        for(i=0; i<SIZE; i++)
        {
            col = (int*)calloc(SIZE,sizeof(int));
            if(col==NULL)
            {
                printf("There was an error with the memory allocation.\n");
                free(col);
                break;
            }
            if(correct == 1)
                    continue;
            for(g=0; g<SIZE; g++)
            {
                remainder = array[g+(m*9)]%(myPow(10,i+1));

                if(col[remainder]==0)
                    col[remainder]++;
                else
                {
                    correct = 1;
                    continue;
                }
            }

        }
        for(k=0; k<SIZE; k++)
        {
            box = (int*)calloc(SIZE,sizeof(int));
            if(box==NULL)
            {
                printf("There was an error with the memory allocation.\n");
                free(box);
                break;
            }
            if(correct == 1)
                continue;

            for(q=0; q<SIZE/3; q++)
            {
               for(e=0; e<SIZE/3; e++)
                {
                   remainder = array[(q*e)+(m*9)]%(myPow(10,(q+1)*e));

                   if(box[remainder]==0)
                        box[remainder]++;
                   else
                   {
                       correct == 1;
                       continue;
                   }
                }
            }


        }
     if(correct == 0)
        printf("YES\n");
     else
        printf("NO\n");
    }
    free(row);
    free(col);
    free(box);
}

int myPow(int base, int exponent)
{
    int i, n = 1;
    for (i = 0; i < exponent; i++) {
        n *= base;
    }
    return n;
}
