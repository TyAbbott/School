import java.util.*;
import java.io.*;

public class passwords
{
	public static void main(String[] args)
	{
		int cases, length, index;
		Scanner scan = new Scanner(System.in);
		cases = scan.nextInt();
		for(int i=0; i<cases; i++)
		{
			String[] letters = new String[20];
			int[] lens = new int[20];
			int[] counter = new int[20];
			int[] combo = new int[20];
			
			String pass = "";
			
			length = scan.nextInt();
			// reads in all the possible letters
			for(int j=0; j<length; j++)
			{
				String lets = scan.nextLine();
				letters[j] = lets;
				lens[j] = lets.length();
			}
			index = scan.nextInt();	
			int combos = 1;
			for(int c=length-1; c>=0; c--)
			{
				combo[c] = combos;
				combos *= lens[c];
			}
			int cnt = 0, num = 0;
			int[] spot = new int[20];
			while(index != 0)
			{
				if(combo[cnt] < index)
				{
					spot[cnt]++;
					index -= combo[cnt];
				}
				else
				{
					cnt++;
				}
			}
			for(int h=0; h<length; h++)
			{
				pass += letters[h].charAt(spot[h]);
			}
			System.out.println(pass);
		}
	}
}