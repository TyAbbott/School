/*
 *  Ty Abbott
 *  CIS 3360
 *  Fall 2017
 *  DiffieHellman.java
 */

import java.util.*;
import java.io.*;

/*
 * private numbers are random numbers that are less than p.
 * public numbers computed by a^x mod p
 * prime is given through the command prompt
 * root is computed using our root function
 */



public class DiffieHellman
{
	public static void main(String args[])
	{
		String primeVal = args[0];
		int prime = Integer.parseInt(primeVal);
		
		int privateX, privateY, publicX, privateY, root;
		
		int primRoots[] = getPrimitiveRoots(prime);
		int size = getSize(primRoots);
		int root = getRandomNumber(size);
		
		root = primRoots[root];
		privateX = getRandomNumber(prime);
		privateY = getRandomNumber(prime);
		
		publicX = generatePublicKey(prime,root,privateX);
		publicY = generatePublicKey(prime,root,privateY);
		
	}
	
	public static int pow(int base, int exp)
	{
		if(exp < 1)
			return 1;
		else
			return base*pow(base,exp-1);
	}
	
	public static int[] getPrimitiveRoots(int prime)
	{
		int[] primRoots = new int[prime-1];
		int num, cnt=0;
		boolean success = true;
		HashSet hash = new HashSet();
		
		// calculate i^j, then check if it's unique
		for(int i=2; i<prime; i++)
		{
			for(int j=1; j<prime; j++)
			{
				num = pow(i,j)%prime;
				
				if(hash.contains(num))
				{
					success = false;
					break;
				}
				else
					hash.add(num);
					
			}
			hash.clear();
			if(success)
				primRoots[cnt++] = i;
		}
		return primRoots;
	}
	
	public static int getRandomNumber(int size)
	{
		return primitiveRootsMath.random(size)-1;
	}
	
	
	/* X = a^x mod p 
	 * a = primitive root of p
	 * x = random number where x < p
	 * p = prime number
	 */
	public static int generatePublicKey(int prime, int randomRoot, int privateKey)
	{	
		return pow(randomRoot,privateKey)%prime;
	}
	
	
	public static int generatePrivateKey(int prime)
	{
		return getRandomNumber(prime);
	}
	
	public static int getSize(int[] roots)
	{
		for(int i=0; i<roots.length; i++)
		{
			if(roots[i] == 0)
				break;
		}
		return i;
	}
	
}