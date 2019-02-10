// Ty Abbott
// 4/22/16
// Add All lab

#include <stdio.h>
#include <stdlib.h>

struct heapStruct {
    int* heapArray;
    int capacity;
    int size;
};

struct heapStruct * initHeapfromArray(int* values, int length);
void heapify(struct heapStruct *h);
void percolateUp(struct heapStruct *h, int index);
void percolateDown(struct heapStruct *h, int index);
int insert(struct heapStruct *h, int value);
int removeMin(struct heapStruct *h);
void swap(struct heapStruct *h, int index1, int index2);
int minimum(int a, int indexa, int b, int indexb);
void freeHeap(struct heapStruct *h);
void readInput(int);

int main()
{
    int numTimes;
    scanf("%d", &numTimes);
    readInput(numTimes);
    return 0;
}

struct heapStruct * initHeapfromArray(int* values, int length)
{
    int i;
    struct heapStruct* h;
    h = (struct heapStruct*)(malloc(sizeof(struct heapStruct)));
    h->heapArray = (int*)malloc(sizeof(int)*(length+1));

    for(i=1; i<=length; i++)
        h->heapArray[i] = values[i-1];
    h->size = length;
    heapify(h);
    return h;
}
void heapify(struct heapStruct *h)
{
    int i;
    for(i=h->size/2; i>0; i--)
        percolateDown(h, i);
}

void swap(struct heapStruct *h, int index1, int index2)
{
    int temp = h->heapArray[index1];
    h->heapArray[index1] = h->heapArray[index2];
    h->heapArray[index2] = temp;
}

void percolateUp(struct heapStruct *h, int index)
{
    if(index>1)
    {
        if(h->heapArray[index/2] > h->heapArray[index])
        {
            swap(h, index, index/2);
            percolateUp(h, index/2);
        }
    }
}

void percolateDown(struct heapStruct *h, int index)
{
    int min;
    if((2*index+1) <= h->size)
    {
        min = minimum(h->heapArray[2*index], 2*index, h->heapArray[2*index+1],
        2*index+1);
        if(h->heapArray[index] > h->heapArray[min])
        {
            swap(h, index, min);
            percolateDown(h, min);
        }
    }
    else if(h->size == 2*index)
    {
        if(h->heapArray[index] > h->heapArray[2*index])
            swap(h, index, 2*index);
    }
}
int insert(struct heapStruct *h, int value)
{
    int* temp;
    int* throwaway;
    int i;
    if (h->size == h->capacity)
    {
        h->heapArray = (int*)realloc(h->heapArray, sizeof(int)*(2*h->capacity+1));
        if (h->heapArray == NULL)
            return 0;
        h->capacity *= 2;
    }
    h->size++;
    h->heapArray[h->size] = value;
    percolateUp(h, h->size);
}
int removeMin(struct heapStruct *h)
{
    int retval;
    if (h->size > 0)
    {
        retval = h->heapArray[1];
        h->heapArray[1] = h->heapArray[h->size];
        h->size--;
        percolateDown(h, 1);
        return retval;
    }
    else
        return -1;
}

int minimum(int a, int indexa, int b, int indexb)
{
    if (a < b)
        return indexa;
    else
        return indexb;
}

void freeHeap(struct heapStruct *h)
{
    free(h->heapArray);
    free(h);
}

void readInput(int numCases)
{
    int i, j, size, num, sum;
    struct heapStruct* h;
    int *array = (int*)malloc(sizeof(int)*1);
    for(i=0; i<numCases; i++)
    {
        scanf("%d", &size);
        array = (int*)realloc(array, size*sizeof(int));
        for(j=0; j<size; j++)
        {
            scanf("%d", &num);
            array[j] = num;
        }
            h = initHeapfromArray(array, size);
            heapify(h);
            sum = addNums(h);
            freeHeap(h);
            printf("%d\n", sum);
    }
                free(array);
}

int addNums(struct heapStruct *h)
{
    int sum=0;
    if(h->heapArray==NULL)
        return 0;
    else
    {
        sum += removeMin(h);
        heapify(h);
        sum += removeMin(h);
        heapify(h);
        insert(h, sum);
        heapify(h);
        return sum + addNums(h);
    }
}



