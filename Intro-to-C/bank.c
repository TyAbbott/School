/*        Ty Abbott
          Cop 3223
          A program that will run bank accounts
          10/29/15
*/
#define INTEREST .0185
#include <stdio.h>

/* function prototypes */
float withdraw(float balance, float withdrawl);
float deposit(float balance, float toDeposit);
float update(float balance);
float getBalance(int accountNumber, int *accountnums, float *accountbals);
void processServices(FILE* fileptr, int *acctNums, float *acctBalances, int arraySize);

/*-----------------------------------------------------------------------*/
int main()
{
    FILE *readfptr;
    int numTimes, x, acctnum;
    float amount, acctbalance, j;
    if(fopen("bankfile.txt", "r")!=NULL)
    {
        readfptr = fopen("bankfile.txt", "r");
        fscanf(readfptr,"%d", &numTimes);
        int accountNumbers [numTimes];
        float accountBalances [numTimes];
        processServices(readfptr, accountNumbers, accountBalances, numTimes);

    printf("Account\t\tBalance\n-----------------------------------\n");
    for(x=0; x<numTimes; x++)
        {
            printf("%d\t\t%.2f\n", accountNumbers[x], accountBalances[x]);
        }
    }

    else
        printf("There was an error opening the file");
    return 0;
}

/* function will withdraw a requested amount from the current balance
if possible, if not it will print an error message and the current balance */

float withdraw(float balance, float withdrawl)
{
    if(balance>=withdrawl)
        return balance-withdrawl;
    else
    {
        printf("You can not withdrawl more than your balance");
        return balance;
    }
}


/* function will deposit the given amount to the given balance */

float deposit(float balance, float toDeposit)
{
    return balance+toDeposit;
}


/* function will take in the balance of an account and apply interest */

float update(float balance)
{
    return balance * (1+INTEREST);
}


/* function takes the account number, along with the array of account numbers
and array of account balances and returns the balance of the account */

float getBalance(int accountNumber, int *accounts, float *acctBalances)
{
   int i=0;
   while(accounts[i]!=accountNumber)
        i++;
   return acctBalances[i];
}


/* function will read through a file and perform the actions of the file */

void processServices(FILE *readfptr, int *acctNums, float *acctBalances, int numTimes)
{
    int acctnum, k, i, j;
    float acctbalance, amount;
    char input;
    fscanf(readfptr, "%c", &input);
        while(input!='Z')
        {
           if(input=='W')
           {
               fscanf(readfptr, "%d", &acctnum);
               fscanf(readfptr, "%f", &amount);
               withdraw(acctnum, amount);
           }
           else if(input=='D')
           {
               fscanf(readfptr, "%d", &acctnum);
               fscanf(readfptr, "%f", &amount);
               j = getBalance(acctnum, acctNums, acctBalances);
               deposit(j, amount);
           }
           else if(input=='B')
           {
               fscanf(readfptr, "%d", &acctnum);
               getBalance(acctnum, acctNums, acctBalances);
           }
           else if(input=='U')
           {
               fscanf(readfptr, "%d", &acctnum);
               float balance = getBalance(acctnum, acctNums, acctBalances);
               for(i=0; i<numTimes; i++)
               {
                   if(acctNums[i]==acctnum)
                        k=i;
               }
               acctBalances[k] = update(balance);
           }
        }
}
