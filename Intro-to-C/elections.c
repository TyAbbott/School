/*  Ty Abbott
    COP 3223
    A program to read in election results
    and declare a winner
    10/22/15
*/

#include <stdio.h>

int main()
{
    int i, j, p, q, t, numParties, numStates, numVotes, mostVotes, winningParty, overallWinner;           //creating all of the int variables
    FILE *fileptr;                                                                                        //creating the file pointer

    if(fopen("votes.txt", "r")!=NULL)                                         //checking if the file can be opened
    {
        fileptr = fopen("votes.txt", "r");                                    //setting the file pointer to the file
        fscanf(fileptr, "%d", &numParties);
        fscanf(fileptr, "%d", &numStates);                                    //scanning in the number of states and parties

        int electionResults [numParties][numStates];                          //setting the size of the 2d array
        int statesWon [10] = {0};                                             //setting a parallel array which tracks how many states a party has won
        char parties[] = "ABCDEFGHIJ";                                        //setting another parallel array which keeps track of a parties name denoted by a char

        for(i=0; i<numParties; i++)                                           //this is a nested for loop that will go through every element in the 2d array
        {
            for(j=0; j<numStates; j++)
            {
                fscanf(fileptr, "%d", &numVotes);                             //this will scan the numbers from the file
                electionResults[i][j] = numVotes;                             //it will set the number scanned in to the appropriate index in the array
            }
        }

        printf("Election Results\n-------------------------------------\n");
        for(p=0; p<numStates; p++)                                            //Another nested for loop to go through every element in the 2d array except the first state
        {
            mostVotes = electionResults [0][p];                 //it sets the int mostVotes to the number of votes for party A at state[p] so theres something to compare
            winningParty = 0;                                   //sets the index of the winning party to 0 because thats what mostVotes is set to
            for(q=1; q<numParties; q++)                         //starts at 1 (because 0 has already been set), then it goes through every party
            {
                if(electionResults [q][p] > mostVotes)          //checks if the number of votes at the index is larger than the current value of mostVotes
                {
                    mostVotes = electionResults [q][p];         //if the above statement is true it will set mostVotes to the value of that index
                    winningParty = q;                           //then it will set winningParty to the index of the winning party.
                }
            }
            printf("State %d was won by Party %c \n", p+1, parties[winningParty]);  //prints what state was won by which party
            statesWon[winningParty]++;                                              //increases the value of statesWon at the index of the winning party by 1
        }

        printf("\n\nElection Results by Party\n-------------------------------------\n");
        printf("Party\t\t#states won\n\n");

        overallWinner = 0;                                                      //sets the overallWinner to a value
        for(t=0; t<numParties; t++)                                             //a for loop that goes through each party
        {
            printf("%c\t\t%d\n", parties[t], statesWon[t]);                     //prints each state and how many states they won
            if(statesWon[t]>statesWon[overallWinner])                           //checks for the party with the most number of states won
                overallWinner = t;
        }
        printf("\n\nParty %c has won the election, winning %d states.", parties[overallWinner], statesWon[overallWinner]);    //prints the winning party and how many states they won
    }
    else
        printf("There was an error opening the file");                       //lets the user know if the file could not be opened

    fclose(fileptr);                                              //closes the file
    return 0;
}



