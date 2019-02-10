// Ty Abbott
// Number Guesser Program
// The user has 5 guesses to

#include <stdio.h>

int main()
{
    int randomNum, guess, numGuesses;
    int i=4;                      //counter for the while loop, starts at 1 goes to 5
    char guessed = 'n';            //char to keep track of whether the number has been guess , n is no
    randomNum = rand() % 100 + 1;                            //creates a random number 1-100
    printf("Welcome to the Guessing Number Game\n");       //prompts for the user to enter their guess
    while(i>=0 && guessed=='n')                             //A while loop that stays in 5 times or whenever the number is guessed
    {
        printf("Can you guess my secret number from 1-100?\n");     //prompts the user to guess the secret number
        scanf("%d", &guess);

        if(guess==randomNum)                                       //checks if the user entered the correct number
        {
            guessed='y';                                       //changes the guessed to y or yes so it kicks out of the while loop
            int numGuesses = 5-i;                              //calculates the number of guesses it took
            printf("Congratulations you win!\n");
            printf("You have guessed my secret number %d in %d guesses!\n", randomNum, numGuesses);     //prints out a message to the user after guessing the number
        }

        else if(guess!=randomNum && i>0)                         //checks if the guess was wrong and there are still guesses left
        {
            if(guess<randomNum)
                printf("Sorry your guess is too low. You have %d more guesses.\n", i);   //These check if it is too low or too high
            else
                printf("Sorry your guess is too high. You have %d more guesses.\n", i);
        }

        else                                                                  //checks if the user is out of guesses and guessed wrong
        {
            printf("Sorry you lose! I win!\n");
            printf("You could not guess my secret number %d.\n", randomNum);
        }
        i--;                 //decreases the counter by 1
    }
    return 0;
}
