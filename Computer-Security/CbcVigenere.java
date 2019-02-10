//----------------------------------------
// University of Central Florida
// CIS3360 - Fall 2017
// Program Author: Ty Abbott
//----------------------------------------

import java.io.*;
import java.util.*;

public class CbcVigenere
{
	static int size;
	
	public static void main(String args[])
	{
		String filename = args[0];
		String keyword = args[1];
		String vector = args[2];
		
		System.out.println("CBC Vigenere by Ty Abbott");
		System.out.println("Plaintext file name: " + filename);
		System.out.println("Vigenere keyword: " + keyword);
		System.out.println("Initialization vector: " + vector + "\n");
		
		
		System.out.println("Clean Plaintext:");
		char[] cipher = readInput(filename);
		int pad = size%keyword.length();
		char[] modCipher = modifyCipher(cipher, size, pad);
		printCipher(modCipher, size);
		
		for(int i=0; i<pad; i++)
			modCipher[i+size] = 'x';
		size += pad;
		
		System.out.println("\n\nCiphertext:");
		modCipher = vigenereCipher(modCipher, keyword, vector, size);
		printCipher(modCipher, size);
		size -= pad;
		
		System.out.println("\n\nNumber of characters in clean plaintext file: " + size);
		System.out.println("Block size = " + keyword.length());
		System.out.println("Number of pad characters added: " + pad);
		
	}
	



	// Prints a char array.  prints the array in lines of 80 characters.
	
	private static void printCipher(char[] cipher, int size)
	{
		for(int i=0; i<size; i++)
		{
			if(i%80==0)
				System.out.print("\n");		// starts a new line
			System.out.print(cipher[i]);    // prints on the same line
		}
	}

	// This method will simply read in text from an input file
	// and store that data into a character array of size 5000.

	private static char[] readInput(String filename)
	{
		String message = "";
		
		try
		{
			File file = new File(filename);
			Scanner scan = new Scanner(file);
			
			message = scan.nextLine();
			while(scan.hasNextLine())
				message = message + "\n" + scan.nextLine();
		} 
		
		catch (Exception e)
		{
			e.printStackTrace();
		}
		
		
		char[] cipher = message.toCharArray();
		size = cipher.length;
		return cipher;
	}





	// This method will modify the original cipher obtained from
	// the file.  It will strip off any non alphabetic letters
	// and it will change upper case letters to lower case.

	private static char[] modifyCipher(char[] rawCipher, int count, int padAmt)
	{
		char[] newCipher = new char[count+padAmt];
		int j = 0;
		
		for(int i=0; i<count; i++)
		{
			int c = (int)rawCipher[i];
			
			if(c < 65)    	// checking for whitespace or punctuation
				continue;
			else if(c < 91) // checking for uppercase letters
				newCipher[j++] = (char)(c+32);
			else if(c < 97) // checking for punctuation
				continue;
			else if(c < 123) // checking for lowercase letters
				newCipher[j++] = (char)(c);
			else
				continue;
		}
		size = j;
		return newCipher;
	}
	
	
	private static char[] vigenereCipher(char[] plainText, String keyword, String iv, int size)
	{
		int keySize = keyword.length();
		char[] cipher = new char[size];
		int value; 							// holds temporary numerical value of cipher char
		
		for(int i=0; i<keySize; i++)
		{
			value = (keyword.charAt(i)-97 + iv.charAt(i)-97)%26;
			cipher[i] += (char)(plainText[i] + value);
			if(cipher[i]>122)
				cipher[i] = (char)(cipher[i]-26);
		}
		

		for(int j=keySize; j<size; j++)
		{
			value = (keyword.charAt(j%keySize)-97 + cipher[j-keySize]-97)%26;
			cipher[j] += (char)(plainText[j] + value);
			if(cipher[j]>122) 
				cipher[j] = (char)(cipher[j]-26);
		}
		return cipher;
	}

}