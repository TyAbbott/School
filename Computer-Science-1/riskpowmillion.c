/*   Ty Abbott
       riskpowmillion.c
       A program that runs a modified version of risk
       Program 4 for COP3502
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

void mergeSort(int*, int, int);
void merge(int*, int, int, int);
void readInput(int);
int battle(int[], int[], int);

int main()
{
    int numCases;
    scanf("%d", &numCases);
    readInput(numCases);
    return 0;
}

void readInput(int numCases)
{
    int i, j, k, numArmies, *atk, *def, wins;
    for(i=0; i<numCases; i++)
    {
        scanf("%d", &numArmies);
        atk = (int*)malloc(numArmies*sizeof(int));
        def = (int*)malloc(numArmies*sizeof(int));

        for(j=0; j<numArmies; j++)
            scanf("%d", atk[j]);
        for(k=0; k<numArmies; k++)
            scanf("%d", def[k]);

        mergeSort(atk, 0, numArmies);
        mergeSort(def, 0, numArmies);
        wins = battle(atk, def, numArmies);
        free(atk);
        free(def);
        printf("\n%d", &wins);
    }
}

int battle(int attack[], int defense[], int armies)
{
    int atkMin=0, defMin=0, atkMax=armies-1, defMax=armies-1, atkWin=0, defWin=0;
    while(defMin!=defMax)
    {
        if(defense[defMax]>attack[atkMax])
        {
            atkMax--;
            defMax--;
            defWin++;
        }
        else
        {
            if(defense[defMin]>attack[atkMax])
                defWin++;
            else
                atkWin++;
            atkMax--;
            defMin++;
        }
    }
    return defWin;
}

void merge(int *arr, int low, int mid, int high)
{
    int arr2[SIZE];
    int i=low, j= mid+1, k=0;
    while(i<=mid && j<=high)
    {
        if(arr[i]<=arr[j])
            arr2[k++] = arr[i++];
        else
            arr2[k++] = arr[j++];
    }
    while(i<=mid)
        arr2[k++] = arr[i++];
    while(j<=high)
        arr2[k++] = arr[j++];

    k--;
    while(k>=0)
    {
        arr[low+k] = arr2[k];
        k--;
    }
}

void mergeSort(int *arr, int low,  int high)
{
    if(low<high)
    {
        int mid = (high+low)/2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}
