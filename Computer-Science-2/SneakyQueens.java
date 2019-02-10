// Ty Abbott
// SneakyQueens.java
// 1/22/2017
// CS II

import java.util.*;

public class SneakyQueens 
{
	
	// Given the coordinates of queens and the size of the chess board
	// this method will return true if any queens can attack another queen
	// and it will return false if all the queens can't be attacked
	
	public static boolean
	allTheQueensAreSafe(ArrayList<String> coordinateStrings, int boardSize)
	{
		Iterator itr = coordinateStrings.iterator();
		int [] rows = new int[coordinateStrings.size()+1];
		int [] columns = new int[coordinateStrings.size()+1];
		String [] preConv = new String[2];
		int count = 0;
		
		while(itr.hasNext())
		{
			preConv = ((String) itr.next()).split("(?<=\\D)(?=\\d)|(?<=\\d)(?=\\D)");
			columns[count] = getColumn(preConv[0]);
			rows[count] = Integer.parseInt(preConv[1]);
			count++;
		}
		
		int [] verticals = new int[boardSize+1];
		int [] horizontals = new int[boardSize+1];
		int [] diagonals1 = new int[(boardSize*2)+1];
		int [] diagonals2 = new int[(boardSize*2)+1];
		
		//Checks if Queens can attack another Queen vertically
		
		for(int i=0; i<=count; i++)
		{
			if(verticals[columns[i]] == 0)
				verticals[columns[i]]++;
			else
				return false;
		}
		
		
		//Checks if Queens can attack another Queen horizontally
		
		for(int j=0; j<=count; j++)
		{
			if(horizontals[rows[j]] == 0)
				horizontals[rows[j]]++;
			else
				return false;
		}
		
		//Checks if Queens can attack another Queen diagonally like this: /
		
		for(int k=0; k<count; k++)
		{
			if(diagonals1[columns[k]+rows[k]+1] == 0)
				diagonals1[columns[k]+rows[k]+1]++;
			else
				return false;
		}
		
		//Checks if Queens can attack another Queen diagonally like this: \
		
		for(int m=0; m<count; m++)
		{
			if(diagonals2[boardSize-columns[m]+rows[m]] == 0)
				diagonals2[boardSize-columns[m]+rows[m]]++;
			else
				return false;
		}
		
		
		return true;
	}
	
	
	
	
	// Given a string of lowercase letters, getColumn
	// will return the column of the chess piece
	
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
	
	// Pow is an exponential calculator that takes the base
	// and exponent of a function and finds the solution
	
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
		return 2.5;
		
		// I thought the difficulty was good for a first assignment
		// It was not an assignment I could blow off, or something
		// that proved to be a huge stress.  A good in between.
	}
	
	public static double hoursSpent()
	{
		return 8;
	}
	
}