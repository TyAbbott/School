/* Sim.java
** Ty Abbott
** EEL 4678
** Fall 2018
** An implementation of a gshare branch predictor
*/

import java.util.*;
import java.io.*;
import java.math.*;

public class Sim
{
	private static int m; 		// bits in branch history table
	private static int n; 		// number of outcomes we keep in register
	private static int global; 	// global result register
	private static int hits;	// Hits
	private static int misses;	// Misses
	// 0 = SN, 1 = WN, 2 = WT, 3 = ST
	private static int[] table; // prediction table
	
	public static void main(String[] args)
	{
		String[] info = new String[2];
		long add;
		char branch;
		String line;
		int gpb = Integer.parseInt(args[0]);
		int rb = Integer.parseInt(args[1]);
		String filename = args[2];
		m = gpb;
		n = rb;
		int tablesize = (int)Math.pow(2,m);
		table = new int[tablesize];
		global = 0;	// Empty Global Register
		hits = 0;
		misses = 0;
		
		// Initialize all values in table
		for(int i=0; i<tablesize; i++)
		{
			table[i] = 2;
		}
		
		try
		{
			File file = new File(filename);
			Scanner scan = new Scanner(file);
			
			// read input
			while(scan.hasNext())
			{
				line = scan.nextLine();
				info = line.split(" ", 2);
				add = Long.parseLong(info[0], 16);
				branch = info[1].charAt(0);
				gshare(add, branch);
			}
		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}
		// Printing Outputs
		double ratio = (double)misses/(double)(hits+misses); // Misprediction Ratio
		System.out.println("" + m + " " + n + " " + ratio);
	}
	
	public static void gshare(long address, char branch)
	{
		int index, current, result, prediction;
		long preindex;
		int size = (int)(Math.pow(2,n));			// Table Size
		int bsize = (int)(Math.pow(2,n-1));			// Max bit size in decimal
		// Retrieving the Index
		preindex = address/4; 						// 1) removing least significant 2 bits
		preindex = preindex%(int)(Math.pow(2,m));  	// 2) taking the M least significant bits
		index = (int)preindex;
		current = global + (int)(Math.pow(2,m-n));	// 3) add m-n zeros to current global register
		result = index ^ global;					// 4) XOR the results from steps 2 and 3 to get the index
		
		prediction = table[result];	// Our prediction: 0-3
		global = global >> 1;		// Shifting Global Register Right
		
		// Correct Taken Prediction
		if(branch == 't' && prediction > 1)
		{
			hits++;
			// Setting Updated Value
			table[result] = 3; 	// table is now ST
			global += bsize;	// Taken so MSB is a 1
		}
		// Correct Not-Taken Prediction
		else if(branch == 'n' && prediction < 2)
		{
			hits++;
			// Setting Updated Value
			table[result] = 0;  // table is now SN
			// Not-Taken so Global is unchanged after shift.
		}
		// Incorrect Taken Prediction
		else if(branch == 't' && prediction < 2)
		{
			misses++;
			// Setting Updated Value
			table[result] = prediction + 1; // Changes SN to WN or WN to WT
			global += bsize; 	// Taken so MSB is a 1
		}
		// Incorrect Not-Taken Prediction
		else if(branch == 'n' && prediction > 1)
		{
			misses++;
			// Setting Updated Value
			table[result] = prediction - 1; // Changes WT to WN or ST to WT
			// Not-Taken so Global is unchanged after shift.
		}
		// Unexpected Outcome
		else
		{
			System.out.println("Unexpected Outcome");
		}
	}
}
