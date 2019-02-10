import java.util.*;
import java.io.*;

public class violin1
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		int notes;
		int current;
		boolean one;
		boolean two;
		boolean three;
		boolean four;
		int total;
		
		for(int i=0; i<num; i++)
		{
			total = 0;
			one = false;
			two = false;
			three = false;
			four = false;
			
			notes = scan.nextInt();
			for(int j=0; j<notes; j++)
			{
				current = scan.nextInt();
				if(current == 4)
				{
					// remove none
					// add 4 if not already added
					if(!four)
					{
						total++;
						four = true;
					}
				}
				if(current == 3)
				{
					// remove 4
					if(four)
					{
						total++;
						four = false;
					}
					// add 3 if not already added
					if(!three)
					{
						total++;
						three = true;
					}
				}
				if(current == 2)
				{
					// remove 4,3
					if(four)
					{
						total++;
						four = false;
					}
					if(three)
					{
						total++;
						three = false;
					}
					// add 2 if not already added
					if(!two)
					{
						total++;
						two = true;
					}
				}
				if(current == 1)
				{
					if(four)
					{
						total++;
						four = false;
					}
					if(three)
					{
						total++;
						three = false;
					}
					if(two)
					{
						total++;
						two = false;
					}
					// add 4 if not already added
					if(!one)
					{
						total++;
						one = true;
					}
				}
				if(current == 0)
				{
					if(four)
					{
						total++;
						four = false;
					}
					if(three)
					{
						total++;
						three = false;
					}
					if(two)
					{
						total++;
						two = false;
					}
					if(one)
					{
						total++;
						one = false;
					}
				}
			}
			System.out.println(total);
		}
		
	}
}