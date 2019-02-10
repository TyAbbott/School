/* SIM.java
** Ty Abbott
** EEL 4678
** Fall 2018
** An implementation of a flexible cache simulator in Java
*/

import java.util.*;
import java.io.*;
import java.math.*;

// ./SIM <CACHE_SIZE> <ASSOCIATIVITY> <REPLACEMENT> <WB POLICY> <TRACE FILE>
public class SIM 
{
	private static BigInteger[][] cache;
	private static int[][] lru;
	private static boolean dirty[][];
	private static int total = 0;
	private static int hits = 0;
	private static int misses = 0;
	private static int memwrites = 0;
	private static int memreads = 0;
	private static int size, assoc, replacement, wb, blocks, fifopos;
	
	public static void main(String[] args)
	{
		String line, filename;
		BigInteger add;
		char op;
		String[] info = new String[2];
		
		size = Integer.parseInt(args[0]);
		assoc = Integer.parseInt(args[1]);
		replacement = Integer.parseInt(args[2]);
		wb = Integer.parseInt(args[3]);
		filename = args[4];
		
		fifopos = 0;
		blocks = size/64;
		cache = new BigInteger[blocks][assoc];
		lru = new int[blocks][assoc];
		dirty = new boolean[blocks][assoc];
		for(int i=0; i<blocks; i++)
		{
			for(int j=0; j<assoc; j++)
			{
				cache[i][j] = BigInteger.ZERO;
			}
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
				op = info[0].charAt(0);
				add = new BigInteger(info[1].substring(2), 16);
				simulateAccess(op, add);
			}
		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}
		
		double missrat = ((double)misses/((double)misses+(double)hits));
		System.out.println("Miss ratio: " + missrat);
		System.out.println("Writes to Memory: " + memwrites);
		System.out.println("Reads to Memory: " + memreads);
	}
	
	public static void simulateAccess(char op, BigInteger add)
	{
		total++;
		BigInteger bits = new BigInteger("64");
		BigInteger blcks = new BigInteger(Integer.toString(blocks));
		BigInteger preset1 = add.divide(bits);
		BigInteger preset = preset1.mod(blcks);
		int set = preset.intValue();
		BigInteger tag = add.divide(bits);
		//BigInteger tag = tag1.divide(BigInteger.valueOf(size));
		//System.out.println("Address: " + add + "\nSet: " + set + "\nTag: " + tag);
		for(int i=0; i<assoc; i++)
		{
			// Hit
			if(tag.equals(cache[set][i]))
			{
				hits++;
				lru[set][i] = total;
				// on Write Through we write to memory
				if(op == 'W' && wb == 0)
				{
					// write through
					memwrites++;	
				}
				else if(op == 'W' && wb == 1)
				{
					// write back
					dirty[set][i] = true;
				}
				return;
			}
		}
		// Miss
		misses++;
		// LRU protocol
		if(replacement==0)
		{
			updateLru(add);
			if(op == 'W' && wb == 0)
			{
				memreads++;
				memwrites++;
			}
			else
			{
				memreads++;
			}
		}
		else
		{
			updateFifo(add);
			if(op == 'W' && wb == 0)
			{
				memreads++;
				memwrites++;
			}
			else
			{
				memreads++;
			}
		}
		
	}
	
	// called on a miss
	public static void updateLru(BigInteger add)
	{
		// updates the cache according to lru on a miss
		BigInteger bits = new BigInteger("64");
		BigInteger blcks = new BigInteger(Integer.toString(blocks));
		BigInteger preset1 = add.divide(bits);
		BigInteger preset = preset1.mod(blcks);
		int set = preset.intValue();
		BigInteger tag = add.divide(bits);
		//BigInteger tag = tag1.divide(BigInteger.valueOf(size));
		int min = 999999999;
		int spot = 0;
		BigInteger zero = new BigInteger("0");
		
		for(int i=0; i<assoc; i++)
		{
			if(lru[set][i] < min)
			{
				spot = i;
				min = lru[set][i];
			}
		}
		cache[set][spot] = tag;
		lru[set][spot] = total;
		if((wb==1) && (dirty[set][spot]))
		{
			dirty[set][spot] = false;
			memwrites++;
		}
	}
	
	public static void updateFifo(BigInteger add)
	{
		// updates the cache according to fifo on a miss
		BigInteger bits = new BigInteger("64");
		BigInteger blcks = new BigInteger(Integer.toString(blocks));
		BigInteger preset1 = add.divide(bits);
		BigInteger preset = preset1.mod(blcks);
		int set = preset.intValue();
		BigInteger tag = add.divide(bits);
		//BigInteger tag = tag1.divide(BigInteger.valueOf(size));
		//long preset = add/64%blocks;
		//int set = (int)preset;
		//long tag = add/64;
		
		if(fifopos < assoc-1)
		{
			if(dirty[set][fifopos])
			{
				memwrites++;
				dirty[set][fifopos] = false;
			}
			cache[set][fifopos] = tag;
			fifopos++;
		}
		else
		{
			if(dirty[set][0])
			{
				memwrites++;
				dirty[set][0] = false;
			}
			cache[set][0] = tag;
			fifopos = 0;
		}
	}
	
}