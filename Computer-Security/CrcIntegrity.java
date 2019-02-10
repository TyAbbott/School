/*
 * University of Central Florida
 * CIS 3360 - Fall 2017
 * Author: Ty Abbott
 */
 
import java.util.*;
import java.io.*;
 
// Calculates the integrity of a string using CRC
// CRC polynomial: x^12 + x^11 + x^8 + x^7 + x^5 + x^4 + x^2 + 1
// This polynomial gives us: 1100 1101 1010 1
// This program runs in two modes, calculation and verification
// inputs: 1 string to determine whether calculation or verification
// 2nd string is the input to be checked
 
 public class CrcIntegrity
{
	
	public static void main(String[] args)
	{
		String polynomial = "1100110110101";
		String mode = args[0];
		String input = args[1]; 
		String value, crc = "";
		int length = input.length();
		
		// last 3 hex characters represent CRC value in verification mode
		// input form: 5AE0E9 where 0E9 is the CRC value
		
		if(mode.equalsIgnoreCase("v"))
		{
			value = input.substring(0,length-3);
			crc = input.substring(length-3);
		}
		else
			value = input;
		
		printHeader();
		printIntermediate(input, mode, polynomial, crc);
		
		value = hexToBinary(value);
		value += "000000000000"; // padding with 12 zeros
		value = value.replace(" ", "");
		value = binaryDivision(polynomial, value);
		System.out.println(value);
	}
	
	public static String hexToBinary(String hex)
	{
		String bin = "";
		String binFragment = "";
		int iHex;
		hex = hex.trim();
		hex = hex.replaceFirst("0x", "");
		int check = 0;
		
		for(int i=0; i<hex.length(); i++)
		{
			iHex = Integer.parseInt("" + hex.charAt(i),16);
			binFragment = Integer.toBinaryString(iHex);
			
			while(binFragment.length() < 4)
			{
				binFragment = "0" + binFragment;
			}
			bin += binFragment;
		}
		
		StringBuilder str = new StringBuilder(bin);
		int len = str.length();
		for(int j=0; j<len; j++)
		{
			if(j%4 == 0 && j!=0)
			{
				str.insert(j+check, ' ');
				check++;
			}
		}
		
		return str.toString();
	}
	
	public static String binaryToHex(String bin)
	{
		int val = 0;
		int len = bin.length();
		for(int i=0; i<len; i++)
		{
			if(bin.charAt(i) == '1')
			{
				val += pow(2,len-1-i);
			}
		}
		return Integer.toString(val);
	}
	
	public static int pow(int base, int power)
	{
		if(power == 0)
			return 1;
		return base * pow(base,--power);
	}
	
	public static void printHeader()
	{
		System.out.println("--------------------------------------------------------------\n");
		System.out.println("CIS3360 Fall 2017 Integrity Checking Using CRC");
		System.out.println("Author: Ty Abbott\n");
	}
	
	public static void printIntermediate(String hexInput, String mode, String poly, String crc)
	{
		System.out.println("The input string (hex): " + hexInput);
		System.out.println("The input string (bin): " + hexToBinary(hexInput));
		System.out.println("\nThe polynomial used (binary bit string): " + printDifference(poly));
		
		if(mode.equals("c"))
		{
			System.out.println("\nMode of operation: calculation\n");
			System.out.println("Number of zeroes that will be appended to the binary input: " + (poly.length()-1));
		}
		else
		{
			System.out.println("\nMode of operation: verification\n");
			System.out.println("The CRC observed at the end of the input: " + hexToBinary(crc) + " (bin) = " + crc + " (hex)");
		}
		
		System.out.println("\nThe binary string difference after each XOR step of the CRC calculation:\n");
	}
	
	public static String printDifference(String input)
	{
		StringBuilder str = new StringBuilder(input);
		int len = str.length(), check=0;
		for(int i=0; i<len; i++)
		{
			if(i%4 == 0 && i!=0)
			{
				str.insert(i+check, ' ');
				check++;
			}
		}
		return str.toString();
	}
	
	public static int calculate()
	{
		return 0;
	}
	
	public static int verify()
	{
		return 0;
	}
	
	public static String binaryDivision(String poly, String div)
	{
		int len = poly.length();
		int head = 0; 								// keeps track of the last non-zero position during the division process
		int tail = len-1;							// keeps track of the tail end of the result
		int end = div.length();					// keeps a pointer to the end of the dividend
		char[] result = poly.toCharArray();			// holds the updating divisor (red in the example)
		char val1, val2;							// value holders for the two bits that will be xor'ed
		String output = "";
		
		
		// This loop will line up the head pointer to the first non-zero bit
		while(div.charAt(head) == 0)
		{
			head++;
			tail++;
		}
		
		
		while(tail < end)
		{
			int count = 0;
			
			// performing the xor bit by bit division
			for(int i=0; i<len; i++)
			{
				val1 = div.charAt(head+i);
				val2 = result[i];
				
				if(val1 == '1' && val2 == '1')
					result[i] = '0';
				else if(val1 == '1' && val2 == '0')
					result[i] = '1';
				else if(val2 == '0' && val2 == '1')
					result[i] = '1';
				else
					result[i] = '0';
			}
			
			// populating output to be printed out
			for(int j=0; j<head; j++)
				output += "0";
			
			for(int k=head; k<tail; k++)
				output += result[count++];
			
			output += div.substring(tail,end);
			
			// prints out the output
			System.out.println(printDifference(output));
			
			while(tail<end || div.charAt(head) == '0')
			{
				head++;
				tail++;
			}
			div = output;
			output = "";
		}
			
		// return the correct output
		return output.substring(head);
	}
		
	
	
}	