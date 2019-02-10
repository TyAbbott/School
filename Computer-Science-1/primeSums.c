/*  Ty Abbott
    COP3502 lab
    PrimeSum.c
    Adds the prime numbers up to n primes
*/

#define SIZE 10000

#include <stdio.h>
#include <stdlib.h>

int getPrimes(int);

int main()
{
    FILE *fptr;
    int numTimes, i, n, sum;

    fptr = fopen("primesum.in", "r");
    if(fptr==NULL)
    {
        printf("There was a problem with opening the file!\n");
        return 0;
    }

    fscanf(fptr, "%d", &numTimes);

    for(i=0; i<numTimes; i++)
    {
        fscanf(fptr, "%d", &n);
        fscanf(fptr, "%d", &sum);
        printf("%d\n", sum);
    }
    return 0;
}

int getPrimes(int n)
{
    int i, j, k, q, sum=0, *primes;
    *primes = (int*)calloc(SIZE, sizeof(int));
    for(i=2; i<SIZE; i++)
    {
        for(k=2; k<SIZE; k++)
        {
            if(k%i==0)
            {
                for(q=k; k<SIZE; q+=i)
                {
                    primes[q]++;
                }
            }
        }
    }
    for(j=2; j<n; j++)
    {
        if(primes[j]==0)
            sum += j;
    }
    free(primes);
    return sum;
}
