/*
    Ty Abbott
    COP 3223-05
    A program used to store information of girl scout cookie sales
    cookieSales.c
    12/4/15
*/

#include <stdio.h>
#include <string.h>

struct customer
{
    char name[24];
    char cookie[10];
    float costOfOne;
    int numBoxes;
    char paid;
};

void displayInfo(int, struct customer []);
void readInput(int* , FILE *infile, struct customer []);
float moneyReceived(int, struct customer []);
int ordersUnpaid(int, struct customer []);
float amountOutstanding(int, struct customer []);
int percentUnpaid(int, struct customer []);

int main()
{
    FILE *readFptr;
    struct customer customers[30];
    int numTimes = 0;
    readFptr = fopen("custInfo.txt", "r");

    if(readFptr!=NULL)
    {
        readInput(&numTimes, readFptr, customers);
        displayInfo(numTimes, customers);
    }
    else
        printf("There was a problem with opening the File\n");

    return 0;
}

/*function takes an int, representing the number of indices in the array of customer structs
given. This function displays the information inside the array */
void displayInfo(int numCustomers, struct customer array[])
{
    int i, ordersNotPaid, percUnpaid;
    float amountUnpaid, money;

    money = moneyReceived(numCustomers, array);
    ordersNotPaid = ordersUnpaid(numCustomers, array);
    percUnpaid = percentUnpaid(numCustomers, array);
    amountUnpaid = amountOutstanding(numCustomers, array);

    printf("Customers\n");
    printf("Name\t\tType of Cookie\tNum of Boxes\tCost of Box\tPaid\n");
    printf("----------------------------------------------------------------------------\n");
    for(i=0; i<numCustomers; i++)
        printf("%s\t%s\t\t%d\t\t$%.2f\t\t%c\n", array[i].name, array[i].cookie, array[i].numBoxes, array[i].costOfOne, array[i].paid);

    printf("\n\nSummary\n");
    printf("Total Cash Received: $%.2f\n\n", money);
    printf("Num customers who have not paid: %d\n\n", ordersNotPaid);
    printf("Total Amount Outstanding: $%.2f\n\n", amountUnpaid);
    printf("Percentage of Sales Outstanding: %d\n\n", percUnpaid);
}

/*function takes an int pointer, a file pointer, and an array of customer structs. It then reads
the information from the given file and puts that information in the array. */
void readInput(int* num, FILE *infile, struct customer array[])
{
    int i, numBoxes;
    char name[24];
    char cookieType[10];
    char name2[24];
    float cost;
    char paid, space = ' ';
    fscanf(infile, "%d", &numBoxes);
    *num = numBoxes;
    for(i=0; i<numBoxes; i++)
    {
        fscanf(infile, "%s", &name);
        fscanf(infile, "%s", &name2);
        strcat(name,&space);
        strcat(name, name2);
        strcpy(array[i].name, name);
        fscanf(infile, "%s", &cookieType);
        strcpy(array[i].cookie, cookieType);
        fscanf(infile, "%d", &numBoxes);
        array[i].numBoxes=numBoxes;
        fscanf(infile, "%f", &cost);
        array[i].costOfOne=cost;
        paid = fgetc(infile);                 //I had an error with this only. Not sure what else I could do.
    }
}

/*function takes an int with the number of index's from the given array of customer structs.
it then returns the amount of money the user has received from payments. */
float moneyReceived(int numCustomers, struct customer array[])
{
    int i;
    float money = 0;
    for(i=0; i<numCustomers; i++)
    {
        if(array[i].paid=='Y')
            money+=(array[i].costOfOne*array[i].numBoxes);
    }
    return money;
}

/*function takes an int with the number of index's from the given array of customer structs.
It then returns the number of orders that are still unpaid. */
int ordersUnpaid(int numCustomers, struct customer array[])
{
    int unpaidOrders = 0, i;
    for(i=0; i<numCustomers; i++)
    {
        if(array[i].paid=='N')
            unpaidOrders++;
    }
    return unpaidOrders;
}

/*function takes an int with the number of index's from the given array of customer structs.
It then calculates the amount of money that is still owed to the user. */
float amountOutstanding(int numCustomers, struct customer array[])
{
    int i;
    float amount = 0;
    for(i=0; i<numCustomers; i++)
    {
        if(array[i].paid=='N')
            amount += (array[i].costOfOne*array[i].numBoxes);
    }
    return amount;
}

/*function takes an int with the number of index's from the given array of customer structs.
It then calculates the amount of money that is left unpaid as a percentage. */
int percentUnpaid(int numCustomers, struct customer array[])
{
    return amountOutstanding(numCustomers,array)/moneyReceived(numCustomers, array)*100;
}
