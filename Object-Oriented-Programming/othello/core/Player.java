/*
 * Ty Abbott
 * 9.17.2016
 * Player.java
 */
package core;

import java.awt.Color;

public class Player {             //Player keeps track of the name and their Color
    String name;
    Color discColor;
public String getName()          //getters and setters for the variables name and discColor
{
    return this.name;
}
public void setName(String newName)
{
    this.name = newName;
}
public Color getColor()
{
    return this.discColor;
}
public void setColor(Color newColor)
{
    this.discColor = newColor;
}
}
