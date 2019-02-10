import java.util.*;
import java.io.*;

public class sums
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		int n, total;
		
		int[] triangle = new int[302];
		triangle[0] = 0;
		for(int i=1; i<302; i++)
		{
			triangle[i] = triangle[i-1] + i;
		}
		
		for(int i=1; i<=num; i++)
		{
			n = scan.nextInt();
			total = 0;
			for(int j=1; j<=n; j++)
			{
				total += j*triangle[j+1];
			}
			System.out.println(i + " " + n + " " + total);
		}
	}
}