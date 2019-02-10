/* Ty Abbott
    Cop3502
    vacation.c
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void readInput(FILE *infile, int, int**, int**);
int permutations(int, int, int**, int**); //try this to check every spot
double calculateTime(int, int, int, int);
int myPow(int, int);

int main()
{
    FILE *readfptr;
    int numVacations, numRides, numBlocks, maxPaths;
    readfptr = fopen("vacation.in", "r");
    if(readfptr==NULL)
    {
        printf("There was an error with opening the file.\n");
        fclose(readfptr);
        return 0;
    }
    else
    {
        fscanf(readfptr, "%d", &numVacations);
        int** rides;
        int** blocked;
        readInput(readfptr, numVacations, rides, blocked);
    }
}

void readInput(FILE *infile, int vacations, int** ride, int** block)
{
    int i, j, k, l, m, rides, blocked, time;
    for(i=0; i<vacations; i++)
    {
        fscanf(infile, "%d", &rides);
        fscanf(infile, "%d", &blocked);
        ride = (int**)malloc(rides*sizeof(int*));
        block = (int**)malloc(blocked*sizeof(int*));
        for(j=0; j<rides; j++)
        {
            ride[j] = (int*)malloc(2*sizeof(int));
            fscanf(infile, "%d", ride[j][1]);
            fscanf(infile, "%d", ride[j][2]);
        }
        for(k=0; k<blocked*blocked; k++)
        {
             block[k] = (int*)malloc(2*sizeof(int));
             fscanf(infile, "%d", block[k][1]);
             fscanf(infile, "%d", block[k][2]);
        }
        time = permutations(rides, blocked, ride, block);
        printf("Vacation #%d:\nJimmy can finish all rides in %d seconds\n", i+1, time);
    }
    for(l=0; l<rides; l++)
        free(ride[l]);
    for(m=0; m<blocked; m++)
        free(block[m]);
    free(ride);
    free(block);
}

int permutations(int numRides, int numBlocked, int** rides, int** blockedPaths)
{
    int i, j;
    double time=0.0;
    for(i=0; i<numRides; i++)
    {
        if(i<numRides-1)
            time += calculateTime(rides[i][1], rides[i][2], rides[i+1][1], rides[i+1][2]);
        else
            time += calculateTime(rides[i][1], rides[i][2], 0,0);
    }
    return time;
}

double calculateTime(x1, y1, x2, y2)
{
    return sqrt(myPow((x2-x1), 2))+(myPow((y2-y1), 2));
}


int myPow(int base, int exponent)
{
    int i, n = 1;
    for (i = 0; i < exponent; i++) {
        n *= base;
    }
    return n;
}


