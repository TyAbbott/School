/*   Ty Abbott
        COP 3502
        Word Search - Project 2
        A program used to find words located in a word bank also in a word search
        wordsearch.c  */

#define SIZE 19
const int DX_SIZE = 8;
const int DX[] = {-1,-1,-1,0,0,1,1,1};
const int DY[] = {-1,0,1,-1,1,-1,0,1};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readInput(FILE *infile, char [][], int, int);
void searchWords(char [][], char [], char [][], int);
void checkSpot(char [][], int, int, char [][]);
char* searchGrid(char [][], int, int);


int main()
{
    int i,j,numWords, row, col, numPuzzles, r, c;
    FILE* dictfptr ;
    dictfptr = fopen("dictionary.txt", "r");
    if(dictfptr==NULL)
    {
        printf("There was a problem with opening the file\n");
        return 0;
    }
    fscanf(dictfptr, "%d", &numWords);
    char* dictionary[] = (char*)malloc((numWords*SIZE)*sizeof(char));
    for(i=0; i<numWords; i++)
    {
        fscanf(dictfptr, "%s", dictionary[i]);
    }
    scanf("%d", &numPuzzles);
    scanf("%d %d", &row, &col);
    char* wordGrid[] = (char*)malloc((row*col)*sizeof(char));
    for(j=0; j<numPuzzles; j++)
    {
        char* list[] = (char*)malloc((SIZE*SIZE)*sizeof(char));
        for(r=0; r<row; r++)
        {
                scanf("%s", wordGrid[r][col]);
        }
        checkSpot(wordGrid, col, row, &list);
        printf("Words Found Grid #%d", j);
        printf("%s", list[0]);
        printf("%s", list[1]);
        printf("%s", list[2]);
    }
    fclose(dictfptr);
    free(list);
    free(dictionary);
    return 0;
}

/*------------------------------------------------------------------------------------
 function looks at all the different spots in the grid and creates words
-------------------------------------------------------------------------------------*/
void checkSpot(char grid[][], int col, int row, char list[][])
{
    int i,j,k,m;
    char* word;
    word = (char*)malloc(SIZE*sizeof(char));
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
                for(k=0; k<DX_SIZE; k++)
                {
                    for(m=0; m<row; m++)
                    {
                        if(k==0&&i-m>0&&j-m>0)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==1&&j-m>0)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==2&&i+m<row&&j-m>0)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==3&&i-m>0)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==4&&i+m<row)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==5&&i-m>0&&j+m<col)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==6&&j+m<col)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else if(k==7&&i+m<row&&j+m<col)
                            word[m] = grid[i+DY[k]][j+DX[k]];
                        else
                            searchWords(dictionary, word, list);
                    }

                }
            }
        }
    }
}

/*--------------------------------------------------------------------------------------
    A function that will search a dictionary of words for a specific string
    if that string exists in the dictionary, then it will add that word to a list
    this function uses a binary search method
-----------------------------------------------------------------------------------------*/
void searchWords(char dict[][], char word[], char list[][], int size, int* spot)
{
    int start=0, end=size, mid;
    while(start<=end)
    {
        mid = start + (end-start)/2;
        if(strcmp(dict[mid],word)==0)
        {
            strcpy(list[spot+1],word);
            *spot++;
        }
        else if(strcmp(dict[mid], word)>0)
            end = mid-1;
        else
            start = mid+1;
    }
}




