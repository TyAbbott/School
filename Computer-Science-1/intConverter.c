// Ty Abbott
// intConverter.c
// A program that will convert the last two bits of an integer
// Into a string.  For example: 14 = 1110 which would then
// be converted in the string: 10.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 30

char* convertToBinary(int baseTen);
int getPower(int base, int power, int max);
int power(int base, int exp);
char* convertBinaryToString(char *bin);
void readInput(int numCases);

int main()
{
    int numTimes;
    printf("How many numbers do you want to convert?\n");
    scanf("%d", &numTimes);
    readInput(numTimes);
    return 0;
}

char* convertToBinary(int baseTen)
{
    int x, i, num;
    char* binary;
    binary = malloc(SIZE*sizeof(char));
    x = getPower(2, 1, baseTen);
    for(i=0; i<x; i++)
    {
        num = power(2,x-i);
        if(num<baseTen)
        {
            binary[i] = '1';
            baseTen -= num;
        }
        else
            binary[i] = '0';
    }
    return binary;
    free(binary);
}

char* convertBinaryToString(char *bin)
{
    int size;
    char* arr;
    arr = malloc(2*sizeof(char));
    size = sizeof(bin) / sizeof(bin[0]);
    arr[0] = bin[size-2];
    arr[1] = bin[size-1];
    return arr;
    free(arr);
}

int power(int base, int exp)
{
    if(exp==0)
        return 1;
    else
        return base*power(base, exp-1);
}

int getPower(int base, int power, int max)
{
    if(base>=max)
        return power;
    else
        return getPower(base*2, power+1, max);
}

void readInput(int numCases)
{
    int i, num;
    char* fullBin, final;
    fullBin=malloc(SIZE*sizeof(char));
    final=malloc(2*sizeof(char));
    for(i=0; i<numCases; i++)
    {
        printf("\nPlease enter a number to be converted\n");
        scanf("%d", &num);
        fullBin = convertToBinary(num);
        final = convertBinaryToString(fullBin);
        printf("The number is: %d\tConverted To Binary: %s\tConverted to last two: %s\n", num, fullBin, final);
    }
    free(fullBin);
    free(final);
}
