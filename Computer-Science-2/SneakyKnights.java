// Ty Abbott
// SneakyKnights.java
// 2/12/2017
// CS II


import java.util.*;

public class SneakyKnights 
{
	public static boolean
	allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		
		// Initiates an iterator, String array, and a 2d boolean array
		// The iterator will traverse through the arraylist and store
		// the string values as rows and columns that are then put into
		// the 2d array.  The 2d array does create n^2 run times unfortunately.
		
		Iterator itr = coordinateStrings.iterator();
		int arraySize = coordinateStrings.size()+1;
		
		// Checks if there are too many knights for the given board
		// to give a nice juicy best case scenario without instantiating the array
			
			if(boardSize > 2 && arraySize > (((boardSize*boardSize)+1)/2))
				return false;
			else
			{
				// do nothing, continue the program
			}
		boolean [][] rowsAndColumns = new boolean[boardSize][boardSize];
		String [] preConv = new String[2];
		int row, col;
		
		
		
		while(itr.hasNext())
		{
			
			// This splits the string between letters and numbers to get rows and columns
			
			preConv = ((String) itr.next()).split("(?<=\\D)(?=\\d)|(?<=\\d)(?=\\D)");
			row = Integer.parseInt(preConv[1])-1;
			col = getColumn(preConv[0])-1;
			
			// This checks if the spot has already been accessed
			// If it has it will end the method and return false
			// Otherwise it will change the value to true
			
			if(rowsAndColumns[row][col] == false)
				rowsAndColumns[row][col] = true;
			else
				return false;
			
			// Checks all the spots the knights can move
			// If the spots being checked have an element
			// the method will return false, otherwise
			// it will continue

			// Checks left 1 up 2
			if(row>1 && col>0)
			{
				if(rowsAndColumns[row-2][col-1] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks left 2 up 1
			if(row>0 && col>1)
			{
				if(rowsAndColumns[row-1][col-2] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks right 1 up 2
			if(row>1 && col<boardSize-1)
			{
				if(rowsAndColumns[row-2][col+1] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks right 2 up 1
			if(row>0 && col<boardSize-2)
			{
				if(rowsAndColumns[row-1][col+2] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks left 2 down 1
			if(row<boardSize-1 && col>1)
			{
				if(rowsAndColumns[row+1][col-2] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks left 1 down 2
			if(row<boardSize-2 && col>0)
			{
				if(rowsAndColumns[row+2][col-1] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks right 1 down 2
			if(row<boardSize-2 && col<boardSize-1)
			{
				if(rowsAndColumns[row+2][col+1] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			// Checks right 2 down 1
			if(row<boardSize-1 && col<boardSize-2)
			{
				if(rowsAndColumns[row+1][col+2] == true)
					return false;
			}
			
			else
			{
				// do nothing
			}
			
			
		}
		
		
		return true;
	}
	
	public static int getColumn(String letters)
	{
		int col = 0;
		int n = 0;
		char let;
		for(int i=letters.length()-1; i>=0; i--)
		{
			let = letters.charAt(i);
			col += (let-96)*pow(26,n);
			n++;
		}
		
		return col;
	}
	
	public static int pow(int base, int exp)
	{
		if(exp==0)
			return 1;
		else if(exp==1)
			return base;
		else
			return base*pow(base, exp-1);
	}

	
	public static double difficultyRating()
	{
		return 3.5;
	}
	
	public static double hoursSpent()
	{
		return 10.0;
	}
	
	
	
	
}
