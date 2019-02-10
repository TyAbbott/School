/*
 * Ty Abbott
 * 9.17.2016
 * Game.java
 */
package core;

import java.util.ArrayList;
import javax.swing.JOptionPane;


public class Game {
    ArrayList<Player> players = new ArrayList<Player>();   //intializes the list of players and the board
    Board board;
public Game()
{
    initObjects();
}

public ArrayList<Player> getPlayer()                    //Getters and setters for players and board
{
    return this.players;
}
public void setPlayer(ArrayList<Player> newPlayer)
{
    this.players = newPlayer;
}
public Board getBoard()
{
    return this.board;
}
public void setBoard(Board newBoard)
{
    this.board = newBoard;
}
public void initObjects()             //initializes all of the players and the board
{
    board = new Board();
    createPlayers();
    printPlayers();
}
public void createPlayers()              //creates player 1 and 2 and sets them to light or dark
{
    for(int i=0; i<2; i++)
    {
        String playerName = JOptionPane.showInputDialog(null, "Enter player's name");
        Player player = new Player();
        player.setName(playerName);
        if(i==0)     //if i is 0, then this is player 1
            player.setColor(Constants.Dark);
        else         //if i is not 0, then it is player 2
            player.setColor(Constants.Light);
                
        players.add(player);
    }
    
}

public void printPlayers()               //prints out the players and their disc color
{
    System.out.println("The game has the following players:");
    for(Player p : players)
    {
        System.out.println("Player " + p.getName() + " is playing the disc color " + 
                p.getColor());
    }
}
}
