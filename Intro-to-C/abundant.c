/*     Ty Abbott
       COP 3223
       A program that determines whether a given number from a file is an abundant number
       10/8/2015
*/

#include <stdio.h>

int main()
{
    FILE *readFptr;                                          //declares the pointer
    int numTimes, sum, i, j, check;                          //declaring int's to be used later

    if(fopen("input.txt", "r")!=NULL)                      //makes sure the file exists
    {
        readFptr = fopen("input.txt", "r");                //setting the pointer to read from input.txt
        fscanf(readFptr,"%d", &numTimes);                  //scans the first number of the text file
        int nums[numTimes];                               //sets the array with a size of the number of numbers in the text file

        for(i=0; i<numTimes; i++)                         //goes through the for loop for how ever many numbers there are
        {
            fscanf(readFptr, "%d", &nums[i]);             // scans numbers from the file and adds them to the array
        }

        for(j=0; j<numTimes; j++)                         //goes through the for loop for how ever many numbers there are
        {
            sum = 0;                                      //sets sum to be 0 at the beginning of the loop
            for(check = nums[j]-1; check>0; check--)      //checks every number below the number in the array.  So for 12 it will check 11-1
            {
                if(nums[j]%check==0)                      //checks if the number is a proper divisor
                sum += check;                             //if it is a proper divisor it will add it to sum
            }
            if(sum>nums[j])                               //checks if the sum of proper divisors is greater than the number
            {
                printf("Test case #%d: %2d is abundant.\n", j+1, nums[j]);    //prints that the number is abundant
            }
            else
            {
                printf("Test case #%d: %2d is NOT abundant.\n", j+1, nums[j]);       //prints that the number is not abundant
            }

        }
    }
    else                                                  //if the fopen statement is null meaning it didn't work it will go here
    {
        printf("There was an error with opening the file");                         //prints to the user that there was an error
    }

    fclose(readFptr);                                    //closes the file
    return 0;
}
