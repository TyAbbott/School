/*
 * University of Central Florida
 * CIS 3360 - Fall 2017
 * Author: Ty Abbott
 */
 
import java.util.*;
import java.io.*;

public class RecoverPassword
{
	public static void main(String args[])
	{
		String filename = args[0];
		String hashval = args[1];
		int hash = Integer.parseInt(hashval);
		
		printHeader(filename, hashval);
		
		ArrayList<String> passwords = getPasswords(filename);
		long[] asciiVals = generateAsciiVal(passwords);
		int[] passVals = saltPasswords(asciiVals,hash);
		
		if(passVals[0] == -1)
			System.out.println("\nPassword not found in dictionary\n\nCombinations tested: " + passwords.size()*1000);
		
		else
		{
			System.out.println("\nPassword recovered:");
			System.out.println("   Password            : " + passwords.get(passVals[0]));
			System.out.println("   ASCII value         : " + asciiVals[passVals[0]]);
			System.out.println("   Salt value          : " + passVals[1]);
			long combinations = (passVals[0] * (passwords.size()*10) + passVals[1] + 1);
			System.out.println("   Combinations tested : " + combinations);
		}
		
		
	}
	
	public static ArrayList<String> getPasswords(String filename)
	{
		ArrayList<String> passwords = new ArrayList<String>();
		
		try
		{
			File file = new File(filename);
			Scanner scan = new Scanner(file);
			
			while(scan.hasNextLine())
				passwords.add(scan.nextLine());
		}
		
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return passwords;
	}
	
	public static long[] generateAsciiVal(ArrayList<String> passwords)
	{
		String password;
		int len = passwords.size();
		long[] asciiVals = new long[len];
		long[] mults = {10000000000L,100000000L,1000000L,10000L,100L,1L};
		long val;
			
		for(int i=0; i<len; i++)
		{
			val = 0L;
			password = passwords.get(i);
			for(int j=0; j<6; j++)
			{
				// KNZAVM = 75 + 78 + 90 + 65 + 86 + 77
				// Value = 757890658677 = 75(0000000000) + 78(00000000) + 90(000000) + ...
				val += password.charAt(j) * mults[j];
			}
			asciiVals[i] = val;
			printDictionary(i+1,password,val);
		}
		
		return asciiVals;
	}
	
	public static int[] saltPasswords(long[] asciiVals, int hash)
	{
		// Salt = 372
		// Ascii val = 757890658677
		// Salted Password = 372757890658677 = 372(000000000000) + 757890658677
		int len = asciiVals.length;
		long saltPass, computedHash;
		int[] retVal = new int[2];
		for(int j=0; j<len; j++)
		{
			for(int i=0; i<1000; i++)
			{
				saltPass = asciiVals[j] + i*1000000000000L;
				computedHash = computeHash(saltPass);
				if(hash == computedHash)
				{
					retVal[0] = j;  // password location
					retVal[1] = i;  // salt
					return retVal;
				}					
			}
		}
		retVal[0] = -1;
		retVal[1] = -1;
		return retVal;
	}
	
	public static long computeHash(long saltedPassword)
	{
		// computedHash = ((243*left) + right) % 85767489
		// left is the 7 leftmost digits
		// right is the 8 rightmost digits
		// 12345/100 = 123
		// 12345%100 = 45
		
		long hash, left, right;
		left = saltedPassword/100000000L;
		right = saltedPassword%100000000L;
		
		hash = ((243*left) + right) % 85767489L;
		return hash;
		
	}
	
	public static void printHeader(String file, String hash)
	{
		System.out.println("----------------------------------------");
		System.out.println("CIS3360 Password Recovery by Ty Abbott");
		System.out.println("\n   Dictionary file name       : " + file);
		System.out.println("   Salted password hash value : " + hash);
		System.out.println("\nIndex   Word   Unsalted ASCII equivalent\n");
		
	}
	
	public static void printDictionary(int index, String word, long ascii)
	{
		if(index<10)
			System.out.println("   " + index + " :  " + word + " " + ascii);
		else if(index>99)
			System.out.println(" " + index + " :  " + word + " " + ascii);
		else
			System.out.println("  " + index + " :  " + word + " " + ascii);
	}
	
	
	
}