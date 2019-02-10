import java.util.*;
import java.io.*;

public class upwards
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		for(int i=0; i<num; i++)
		{
			String a = scan.next();
			if(checkword(a))
				System.out.println("YES");
			else
				System.out.println("NO");
		}
	}
	
	public static boolean checkword(String word)
	{
		ArrayList<Integer> arr = new ArrayList<Integer>();
		int max = -999;
		int num;
		for(int i=0; i<word.length(); i++)
		{
			num = word.charAt(i);
			if(num > max)
			{
				max = num;
				if(arr.contains(num))
					return false;
				else
					arr.add(num);
			}
			else
				return false;
		}
		return true;
	}
}