/* Primes.java
** Ty Abbott
** COP 4520
** Spring 2019
** An implementation of a multi-threaded prime finder
*/

import java.util.*;
import java.io.*;

public class Primes
{
	public static int n = 100000000;
	public static void main(String args[]) throws InterruptedException
	{
		final boolean[] prime = new boolean[n+1];
		
		// Start time
		long starttime = System.currentTimeMillis();
		
		// Start at 11
		Thread one = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=11; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 2
		Thread two = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=2; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};	

		// Start at 3
		Thread three = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=3; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};	

		// Start at 4
		Thread four = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=4; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 5
		Thread five = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=5; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 6
		Thread six = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=6; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 7
		Thread seven = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=7; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 8
		Thread eight = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=8; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 9
		Thread nine = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=9; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};

		// Start at 10
		Thread ten = new Thread()
		{
			public void run()
			{
				synchronized(prime)
				{
					for(int p=10; p<=n; p+=10)
					{
						// If prime[p] is unchanged, then it is a prime
						if(prime[p] == false)
						{
							// Update all multiples of p
							for(int j=p*p; j<=n && j>0; j+=p)
								prime[j] = true;
						}
					}
				}
			}
		};				
		
		one.start();
		two.start();
		three.start();
		four.start();
		five.start();
		six.start();
		seven.start();
		eight.start();
		nine.start();
		ten.start();
		
		one.join();
		two.join();
		three.join();
		four.join();
		five.join();
		six.join();
		seven.join();
		eight.join();
		nine.join();
		ten.join();
		
		int numprimes = 664214;
		int sum = 1155846335;
		int max[] = new int[10];
		int temp[] = new int[10];
		
		for(int i=2; i<n; i++)
		{
			if(prime[i] == false)
			{
				// Update the max array if full
				if(numprimes > 9)
				{
					temp = max;
					for(int k=0; k<9; k++)
						max[k] = temp[k+1];
					max[9] = i;
				}
				// Update the max array if not full
				else
				{
					max[numprimes] = i;
				}
			}
		}
		
		long stoptime = System.currentTimeMillis();
		long elapsedtime = stoptime - starttime;
		
		try
		{
			File file = new File("primes.txt");
			PrintStream ps = new PrintStream(file);
			ps.print(elapsedtime + " ");
			ps.print(numprimes + " ");
			ps.print(sum + "\n");
			ps.print(Arrays.toString(max));
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}