import java.util.*;
import java.io.*;
import java.util.Arrays;

public class sorting
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		int[] nums = new int[500];
		int size;
		int total;
		int spot1, spot2, min1, min2;
		int temp, tempspot;
		
		for(int i=0; i<num; i++)
		{
			total = 0;
			size = scan.nextInt();
			for(int j=0; j<size; j++)
			{
				nums[j] = scan.nextInt();
			}
			if(size == 0)
				System.out.println(0);
			else if(size == 1)
				System.out.println(0);
			else
			{
				// go through size-1 iterations
				for(int k=0; k<size-1; k++)
				{
					min1 = 501;
					min2 = 501;
					spot1 = 0;
					spot2 = 0;
					// find the 2 smallest values at each iteration
					for(int p=0; p<size; p++)
					{
						if(nums[p] < min1)
						{
							temp = min1;
							tempspot = spot1;
							spot1 = p;
							min1 = nums[p];
							// shifting min1 to min2 if its smaller
							if(temp <= min2)
							{
								min2 = temp;
								spot2 = tempspot;
							}
						}
						else if(nums[p] < min2)
						{
							spot2 = p;
							min2 = nums[p];
						}
					}
					// we found the 2 smallest values (min1 & min2) and their indexes (spot1 & spot2)
					total += min1+min2;
					nums[spot1] = min1+min2;
					nums[spot2] = 501;
				}
				System.out.println(total);
			}
		}
	}
	
}