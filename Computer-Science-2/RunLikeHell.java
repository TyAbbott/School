/*
 * Ty Abbott
 * RunLikeHell.java
 * CS II - Spring 2017
 * Professor Szumlanski
 * Dynamic Programming Assignment
 */

public class RunLikeHell 
{
	public static int maxGain(int [] blocks)
	{
		int length = blocks.length;
		 
		// Side cases for lengths of 0 or less and 1.
		if(length < 1)
			return 0;
		if(length == 1)
			return blocks[0];
		
		
		// Dynamic programming array to store our solution
		int [] dp = new int[length];
		
		for(int i=0; i<length; i++)
		{
			// Base Cases
			if(i<2)
				dp[i] = blocks[i];
			
			// Another case to prevent an array index out of bounds
			else if(i == 2)
				dp[i] = blocks[i] + blocks[0];
			
			// Main bit of recursion:  Adds current location with
			// max of the blocks 3 in front or 2 in front.
			else
				dp[i] = blocks[i] + Math.max(dp[i-3], dp[i-2]);
		}
		
		// Returns the max of the last two elements
		return Math.max(dp[length-2], dp[length-1]);
	}
	
	public static double difficultyRating()
	{
		return 1.5;
	}
	
	public static double hoursSpent()
	{
		return 3.0;
	}
}
