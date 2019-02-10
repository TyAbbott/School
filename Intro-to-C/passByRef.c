/* Ty Abbott
   11/5/2015
   COP 3223
   A program that orders arrays from least to greatest
*/

#include <stdio.h>
#define NUM 100

void createArray(int[], FILE *infile, int);
void maxValue(int[], int);
void minValue(int[], int);
void sortMinToMax(int[], int[], int);
void totalValues(int[], int);

int main()
{
    FILE *fileptr;
    int array[NUM];
    int size = 0;
    int* sizeptr = &size;
    if(fopen("input.txt", "r")==NULL)                      //makes sure the file exists
        printf("The File could not be opened");
    else
    {
        fileptr = fopen("input.txt", "r");
        createArray(array, fileptr, sizeptr);
        int sortedArray[size];
        maxValue(array, size);
        minValue(array, size);
        sortMinToMax(array, sortedArray, size);
        totalValues(array, size);
    }
    return 0;
}

void createArray(int array[], FILE *fileptr, int size)
{
    int i, value;
    i=0;
    fscanf(fileptr, "%d", &value);
    printf("The original array is: ");
    while(value!=0)
    {
        array[i] = value;
        printf("%d,", value);
        fscanf(fileptr, "%d", &value);
        i++;
    }
    size = i;
}

void maxValue(int array[], int sizeOfArray)
{
    int maxVal = array[0];
    int i;
    for(i=1; i<sizeOfArray; i++)
    {
        if(array[i]>maxVal)
            maxVal=array[i];
    }
    printf("\nThe maximum value is %d", maxVal);
}

void minValue(int array[], int sizeOfArray)
{
    int minVal = array[0];
    int i;
    for(i=1; i<sizeOfArray; i++)
    {
        if(array[i]<minVal)
            minVal = array[i];
    }
    printf("\nThe minimum value is %d", minVal);
}

void sortMinToMax(int array[], int array2[], int sizeOfArray)
{
    int lowerBound, i, minVal, j;
    lowerBound = -1;
    printf("\nThe sorted array is: ");
    for(j=0; j<sizeOfArray; j++)
    {
        minVal = array[0];
        for(i=1; i<sizeOfArray; i++)
        {
            if(array[i]<minVal && array[i]>=lowerBound)
                minVal = array[i];
        }
        array2[j] = minVal;
        lowerBound = minVal;
        printf("%d,", minVal);
    }
}

void totalValues(int array[], int sizeOfArray)
{
    int total, i;
    total = 0;
    for(i=0; i<sizeOfArray; i++)
    {
        total += array[i];
    }
    printf("The total of the values in the array is: %d", total);
}



