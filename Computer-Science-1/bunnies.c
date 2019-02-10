/* bunnies.c
    Ty Abbott
    Sparta Coding assignment
    */

#include <stdio.h>
#include <stdlib.h>

#define MAXROWS 10
#define MAXCOLS 10

int checkCage(char[][MAXCOLS], int, int, int, int);
void findP(char[][MAXCOLS], int*, int*, int, int);

int main()
{
    int testCases, rows, cols, rowP, colP, i, j, k, true=0;
    char maze[MAXROWS][MAXCOLS];
    scanf("%d", &testCases);
    for(k=0; k<testCases; k++)
    {
        scanf("%d", &rows);
        scanf("%d", &cols);
        for(i=0; i<=rows; i++)
        {
            for(j=0; j<cols; j++)
                scanf("%c", &maze[i][j]);
        }
        //findP(maze, &rowP, &colP, rows, cols);
        true=checkCage(maze, rows, cols, 0, 0);
        if(true==1)
            printf("\nyes");
        else
            printf("\nno");
    }
    return 0;
}

int checkCage(char cage[][MAXCOLS], int numRows, int numCols, int curRow, int curCol)
{
    if(cage[curRow][curCol]=='C')
        return 1;
    else if(cage[curRow][curCol]=='#')
        return 0;
    else if(curRow==numRows-1)
    {
        if(curCol==numCols-1)
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, curRow, curCol-1) + checkCage(cage, numRows, numCols, curRow, 0) + checkCage(cage, numRows, numCols, curRow-1, curCol) + checkCage(cage, numRows, numCols, 0, curCol);
        }
        else if(curCol==0)
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, curRow, curCol+1) + checkCage(cage, numRows, numCols, curRow, numCols-1) + checkCage(cage, numRows, numCols, curRow-1, curCol) + checkCage(cage, numRows, numCols, 0, curCol);
        }
        else
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, curRow, curCol+1) + checkCage(cage, numRows, numCols, curRow, curCol-1) + checkCage(cage, numRows, numCols, 0, curCol) + checkCage(cage, numRows, numCols, curRow-1, curCol);
        }
    }
    else if(curCol==numCols-1)
    {
        if(curRow==0)
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, curRow, curCol-1) + checkCage(cage, numRows, numCols, curRow, 0) + checkCage(cage, numRows, numCols, curRow+1, curCol) + checkCage(cage, numRows, numCols, numRows-1, curCol);
        }
        else
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, curRow, 0) + checkCage(cage, numRows, numCols, curRow, curCol-1) + checkCage(cage, numRows, numCols, curRow+1, curCol) + checkCage(cage, numRows, numCols, curRow-1, curCol);
        }
    }
    else if(curRow==0)
    {
        if(curCol==0)
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, curRow+1, curCol) + checkCage(cage, numRows, numCols, numRows-1, curCol) + checkCage(cage, numRows, numCols, curRow+1, curCol) + checkCage(cage, numRows, numCols, numRows-1, curCol);
        }
        else
        {
            cage[curRow][curCol] = '#';
            return 0 + checkCage(cage, numRows, numCols, numRows-1, curCol) + checkCage(cage, numRows, numCols, curRow+1, curCol) + checkCage(cage, numRows, numCols, curRow, curCol+1) + checkCage(cage, numRows, numCols, curRow, curCol-1);
        }
    }
    else if(curCol==0)
    {
        cage[curRow][curCol] = '#';
        return 0 + checkCage(cage, numRows, numCols, curRow, curCol+1) + checkCage(cage, numRows, numCols, curRow, numCols-1) + checkCage(cage, numRows, numCols, curRow-1, curCol) + checkCage(cage, numRows, numCols, curRow+1, curCol);
    }
    else
    {
        cage[curRow][curCol] = '#';
        return 0 + checkCage(cage, numRows, numCols, curRow+1, curCol) + checkCage(cage, numRows, numCols, curRow-1, curCol) + checkCage(cage, numRows, numCols, curRow, curCol+1) + checkCage(cage, numRows, numCols, curRow, curCol-1);
    }
}

void findP(char maze[][MAXCOLS], int *rows, int *cols, int numRows, int numCols)
{
    int i, j;
    for(i=0; i<numRows; i++)
    {
        for(j=0; j<numCols; j++)
        {
            if(maze[i][j]=='P')
            {
                rows = i;
                cols = j;
                return;
            }
        }
    }
}
