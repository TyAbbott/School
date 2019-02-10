/*  Ty Abbott
    Lemonade Stand program
    9-8-15
    Intro to C programming class
    the program is intended to act as a cash register for a lemonade
    stand with two items, lemonade and cookies.
*/

#include <stdio.h>

#define COOKIE .50
#define LEMONADE .75           // two constants that keep track of the price of one cookie and one lemonade

int main()
{
    int numCookies;
    int numLemonade;      //These are variables to keep track of the number of cookies and lemonade being bought
    float cost;
    float money;
    float change;       //These floats keep track of the cost of the lemonade and cookies, money the customer has and the change

    printf("Welcome to the Sunny Lane Lemonade Stand\n");

    printf("How many cookies would you like?\n");                //prompts the customer to enter how many cookies they want
    scanf("%d",&numCookies);

    printf("How many lemonades would you like?\n");              //prompts the customer to enter how many lemonades they want
    scanf("%d",&numLemonade);

    cost = (numCookies*COOKIE)+(numLemonade*LEMONADE);     //calculates the cost of the transaction and then prints it out
    printf("That will cost $%.2f\n",cost);

    printf("How much money do you have?\n");      //prompts for and then reads in how much money the customer is paying with
    scanf("%f",&money);

    change = money-cost;
    printf("That is $%.2f change.\n",change);        //calculates and then prints out the change

    printf("Thank you.");

    return 0;

}
