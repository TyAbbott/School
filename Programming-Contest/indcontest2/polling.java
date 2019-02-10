import java.util.*;
import java.io.*;
import java.lang.Math;

public class polling
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		TreeMap<String, Integer> tr = new TreeMap<String, Integer>();
		String input;
		int max = -1;
		int newnum;
		for(int i=0; i<=num; i++)
		{
			input = scan.nextLine();
			if(tr.containsKey(input))
			{
				newnum = tr.get(input)+1;
				tr.put(input, newnum);
				max = Math.max(newnum, max);
			}
			else
			{
				tr.put(input, 1);
				max = Math.max(1, max);
			}
		}
		Set<String> keys = tr.keySet();
		for(String key: keys)
		{
			if(tr.get(key) == max)
				System.out.println(key);
		}	

	}
}