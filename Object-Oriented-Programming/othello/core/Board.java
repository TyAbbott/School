/*
 * Ty Abbott
 * 9.17.2016
 * Board.java
 */
package core;

public class Board {
    private Disc[][] board;               //creates a 2d array of discs that is private in scope
    
    public Board()
    {
        initObjects();                    //calls initObjects
    }
    
    private void initObjects()
    {
        board = new Disc[8][8];            //Creating the board using a 2d array of Disc objects
        for(int i=0; i<8; i++)             //Double for-loop loops through each spot on the board and instantiates it
        {
            for(int j=0; j<8; j++)
            {
                board[i][j] = new Disc();
            }
        }
        board[3][3].setColor(Constants.Light);  //Setting the colors of the middle 4 spots
        board[3][4].setColor(Constants.Dark);
        board[4][3].setColor(Constants.Dark);
        board[4][4].setColor(Constants.Light);
    }
}
