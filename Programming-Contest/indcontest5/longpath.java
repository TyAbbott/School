import java.util.*;
import java.io.*;

public class longpath
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int c = scan.nextInt();
		int s, d, m, sh, ln, v, e;
		
		
		for(int i=0; i<c; i++)
		{
			v = scan.nextInt();
			e = scan.nextInt();
			int[][] longest = new int[v][v];
			int[][] shortest = new int[v][v];
			int[] shortnodes = new int[v];
			int[] longnodes = new int[v];
			// s = start
			// d = destination
			// m = minutes (distance between s and d)
			for(int j=0; j<e; j++)
			{
				s = scan.nextInt();
				d = scan.nextInt();
				m = scan.nextInt();
				
				if(shortest[s][d] == 0 || m < shortest[s][d])
					shortest[s][d] = m;
				if(longest[s][d] == 0 || m > longest[s][d])
					longest[s][d] = m;
			}
			for(int pl=0; pl<5; pl++)
			{
				for(int row=0; row<v; row++)
				{
					for(int col=0; col<v; col++)
					{
						sh = shortest[row][col];
						ln = longest[row][col];
						if(sh == 0)
							continue;
						else
						{
							if(shortnodes[col] == 0 || (shortnodes[row] + sh) < shortnodes[col])
								shortnodes[col] = shortnodes[row] + sh;
							if(longnodes[col] == 0 || (longnodes[row] + ln) > longnodes[col])
								longnodes[col] = longnodes[row] + ln;
							
						}
					}
				}
				
				for(int row=(v-1); row>=0; row--)
				{
					for(int col=(v-1); col>=0; col--)
					{
						sh = shortest[row][col];
						ln = longest[row][col];
						if(sh == 0)
							continue;
						else
						{
							if(shortnodes[col] == 0 || (shortnodes[row] + sh) < shortnodes[col])
								shortnodes[col] = shortnodes[row] + sh;
							if(longnodes[col] == 0 || (longnodes[row] + ln) > longnodes[col])
								longnodes[col] = longnodes[row] + ln;
							
						}
						System.out.println("Longnode " + col + "- " + longnodes[col]);

					}
				}
			}
				
			System.out.println(shortnodes[v-1] + " " + longnodes[v-1]);
		}
	}
}