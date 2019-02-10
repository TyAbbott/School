//  Ty Abbott
//  5/6/16
//  shuffle.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30

void createList(int *list, int length);
void shuffle(int *list, int length);

int main()
{
    int *list;
    list = (int*)malloc(SIZE*sizeof(int));
    createList(&list, SIZE);
    shuffle(&list, SIZE);
    free(list);
    return 0;
}


//Simple function that creates a list of integers from random values
void createList(int *list, int length)
{
    srand(time(NULL));
    int i, random;
    for(i=0; i<length; i++)
    {
        random = rand()%1000;
        list[i] = random;
        printf("%d has been added to the list at position %d\n", random, i+1);
    }
    return;
}

void shuffle(int *list, int length)
{
    srand(time(NULL));
    int numPlayed=0, random;
    int *played;
    played = (int*)calloc(length, sizeof(int));
    while(numPlayed<length)
    {
        random = rand()%length;
        if(played[random]==0)
        {
            played[random]++;
            numPlayed++;
            printf("Played %d from the playlist\n", list[random]);
        }
    }
    printf("\n\nEvery Song has been played from the playlist\n\n");
    free(played);
    return;
}

