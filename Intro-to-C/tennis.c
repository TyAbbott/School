/*     Ty Abbott
       COP 3223
       A program that keeps track of performance statistics
       for the Tennis pro Marisol Bohen
       11/19/2015
*/

#include <stdio.h>

#define TOURNAMENTS 8
#define MONTHS 12

void makeArray(FILE *infile, int array[][TOURNAMENTS]);
int getScore(int array[][TOURNAMENTS], int, int);
int getMonthMax(int array[][TOURNAMENTS], int);
int getYearMax(int array[][TOURNAMENTS]);
float getMonthAvg(int array[][TOURNAMENTS], int);
float getYearAvg(int array[][TOURNAMENTS]);
int toursMissed(int array[][TOURNAMENTS]);
void displayMenu();
void processRequest(int array[][TOURNAMENTS], int);
void printArray(int array[][TOURNAMENTS]);

int main()
{
    FILE *readFptr;
    int scores[MONTHS][TOURNAMENTS];
    int response;
    readFptr = fopen("scores.txt", "r");

    if(readFptr!=NULL)
    {
        makeArray(readFptr, scores);
    }
    else
        printf("There was a problem with opening the File\n");
    do
    {
        displayMenu();
        scanf("%d", &response);
        processRequest(scores, response);
    } while(response!=0);


    return 0;
}

/*function takes a file pointer as input and an empty 2d array as input,
it then fills the array with the input from the file.  The file must
contain only integers */

void makeArray(FILE *infile, int array[][TOURNAMENTS])
{
    int i,j;
    for(i=0; i<MONTHS; i++)
        {
            for(j=0; j<TOURNAMENTS; j++)
            {
                fscanf(infile, "%d", &array[i][j]);
            }
        }
}
/*-------------------------------------------------------------------*/

/*function takes the filled 2d array, a month, and a tournament as ints as
as the input.  It then returns the score at the given month and tournament */

int getScore(int array[][TOURNAMENTS], int month, int tournament)
{
    return array[month-1][tournament-1];
}
/*-------------------------------------------------------------------*/

/*function takes a filled 2d array and a month given as an int as input
it then returns the largest value in the given month */

int getMonthMax(int array[][TOURNAMENTS], int month)
{
    int i, max=array[month-1][0];
    for(i=1; i<TOURNAMENTS; i++)
        if(array[month-1][i]>=max)
            max=array[month-1][i];
    return max;
}
/*--------------------------------------------------------------------*/

/*function takes a filled 2d array as input.  It then returns the maximum
score throughout the entire year */

int getYearMax(int array[][TOURNAMENTS])
{
    int i,j, max;
    max = array[0][0];
    for(i=0; i<MONTHS; i++)
    {
        for(j=0; j<TOURNAMENTS; j++)
        {
            if(array[i][j]>=max)
                max = array[i][j];
        }
    }
    return max;
}
/*---------------------------------------------------------------------*/

/*function takes a filled 2d array and the month the user wants to know
the average of.  It then returns the average scores for the month*/

float getMonthAvg(int array[][TOURNAMENTS], int month)
{
    int i, sum=0;
    for(i=0; i<TOURNAMENTS; i++)
    {
        sum += array[month-1][i];
    }
    return (float)sum/TOURNAMENTS;
}
/*----------------------------------------------------------------------*/

/*function takes a filled 2d array and then it returns the average
score for the entire year */

float getYearAvg(int array[][TOURNAMENTS])
{
    int i, j, sum=0;
    for(i=0; i<MONTHS; i++)
    {
        for(j=0; j<TOURNAMENTS; j++)
        {
            sum += array[i][j];
        }
    }
    return (float)sum/(TOURNAMENTS*MONTHS);
}
/*-----------------------------------------------------------------------*/

/*function takes a filled 2d array and counts how many events the player
missed throughout the entire year.  These are marked by a 0 */

int toursMissed(int array[][TOURNAMENTS])
{
    int i, j, numMissed=0;
    for(i=0; i<MONTHS; i++)
    {
        for(j=0; j<TOURNAMENTS; j++)
        {
            if(array[i][j]==0)
                numMissed++;
        }
    }
    return numMissed;
}
/*------------------------------------------------------------------------*/

/*function prints out the menu for the user to respond to */

void displayMenu()
{
    printf("What would you like to do?\n----------------------------------------\n");
    printf("Select from options 1-7 or 0 to stop\n");
    printf("Select 1 to get the score for a specific game\n");
    printf("Select 2 to get the max score for a specific month\n");
    printf("Select 3 to get the average score for a specific month\n");
    printf("Select 4 to get the max score for the year\n");
    printf("Select 5 to get the average score for the year\n");
    printf("Select 6 to get the number of tournaments missed for the year\n");
    printf("Select 7 to print all scores for the year\n");
    printf("Select 0 to stop\n----------------------------------------\n");
}
/*-------------------------------------------------------------------------*/

/*function takes a filled 2d array and an integer between 0-7 for input
then based on the number used for input it will run the appropriate function */
void processRequest(int array[][TOURNAMENTS], int input)
{
    int month, game, score;
    float avg;
    if(input==1)
    {
       printf("\nPlease enter the month and the game\n");
       scanf("%d %d", &month, &game);
       score = getScore(array, month, game);
       printf("\nThe score for Tournament %d is %d\n\n\n", game, score);
    }
    else if(input==2)
    {
        printf("\nPlease enter the month\n");
        scanf("%d", &month);
        score = getMonthMax(array, month);
        printf("\nThe max score for Month %d is %d\n\n\n", month, score);
    }
    else if(input==3)
    {
        printf("\nPlease enter the month\n");
        scanf("%d", &month);
        avg = getMonthAvg(array, month);
        printf("\nThe average score for month %d is %.2f\n\n\n", month, avg);

    }
    else if(input==4)
    {
       score = getYearMax(array);
       printf("\nThe max score for the year is %d\n\n\n", score);
    }
    else if(input==5)
    {
        avg = getYearAvg(array);
        printf("\nThe average score for the year is %.2f\n\n\n", avg);
    }
    else if(input==6)
    {
        score = toursMissed(array);
        printf("\nThe number of tournaments missed for the year is %d\n\n\n", score);
    }
    else if(input==7)
    {
        printArray(array);
    }
    else
    {
        printf("\nThank you!   Goodbye\n");
    }
}
/*--------------------------------------------------------------------------------*/

/*function takes in a filled 2d array and prints out the elements */

void printArray(int array[][TOURNAMENTS])
{
    int i,j;
    printf("The scores for the year are:\n");
    for(i=0; i<MONTHS; i++)
    {
        for(j=0; j<TOURNAMENTS; j++)
        {
            printf("%2d     ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}
/*---------------------------------------------------------------------------------*/
