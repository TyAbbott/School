/* Ty Abbott
    mastermind.c
    */
 #include <stdio.h>

int calculateCombos(int, int, int, int);
int myPow(int, int);

int main()
{
        int c, n, k, m, b, w, i, j, p, *nums, solution;
        scanf("%d", &c);
        for(i=0; i<c; i++)
        {
            scanf("%d %d %d", &n, &k, &m);
            for(j=0; j<m; j++)
            {
                nums = (int*)malloc(n*sizeof(int));
                for(p=0; p<n+2; p++)
                {
                    if(p<n)
                        scanf("%d", &nums[p]);
                    else if(p==n)
                        scanf("%d", &b);
                    else
                        scanf("%d", &w);
                }
            }
            solution = calculateCombos(n, k, b, w);
            printf("\n%d\n", solution);
        }
        free(nums);
        return 0;
}

int calculateCombos(int spots, int colors, int black, int white)
{
    return myPow(spots-1,spots-black-white)+((spots-1)*white);
}

int myPow(int base, int exponent)
{
    int i, n = 1;
    for (i = 0; i < exponent; i++) {
        n *= base;
    }
    return n;
}
