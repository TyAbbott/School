import java.util.*;
import java.io.*;
import java.lang.Math;

public class balloons
{
	public static void main(String[] args)
	{
		int total = 0;
		int[] k = new int[1000];
		int[] da = new int[1000];
		int[] db = new int[1000];
		int[] diff = new int[1000];
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		int a = scan.nextInt();
		int b = scan.nextInt();
		for(int i=0; i<num; i++)
		{
			k[i] = scan.nextInt();
			da[i] = scan.nextInt();
			db[i] = scan.nextInt();
			diff[i] = Math.max(da[i]-db[i], db[i]-da[i]);
		}
		int count = scan.nextInt();
		count = scan.nextInt();
		count = scan.nextInt();
		count = 0;
		int max;
		int spot = 0;
		HashSet<Integer> hashy = new HashSet<Integer>();
		while(count<num)
		{
			max = -1;
			for(int i=0; i<num; i++)
			{
				if(hashy.contains(i))
					continue;
				if(diff[i] > max)
				{
					spot = i;
					max = diff[i];
				}
			}
			hashy.add(spot);
			// choosing a and we have enough a balloons
			if(da[spot] < db[spot] && k[spot] < a)
			{
				total += k[spot]*da[spot];
				a -= k[spot];
			}
			// choosing b and we have enough b balloons
			else if(db[spot] < da[spot] && k[spot] < b)
			{
				total += k[spot]*db[spot];
				b -= k[spot];
			}
			// choosing a we don't have enough a balloons
			else if(da[spot] < db[spot] && k[spot] >= a)
			{
				total += a*da[spot];
				k[spot] -= a;
				total += k[spot]*db[spot];
				a = 0;
			}
			// choosing b we don't have enough b balloons
			else if(db[spot] < da[spot] && k[spot] >= b)
			{
				total += b*db[spot];
				k[spot] -= b;
				total += k[spot]*da[spot];
				b = 0;
			}
			// a and b are the same
			else
			{
				total += k[spot]*da[spot];
			}
			count++;
		}
		System.out.println(total);
	}
}