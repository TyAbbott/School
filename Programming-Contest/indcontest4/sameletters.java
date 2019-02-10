import java.util.*;
import java.io.*;

public class sameletters
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		String a, b;
		int cnt = 1;
		boolean getout;
		
		while(scan.hasNextLine())
		{
			int[] alets = new int[26];
			int[] blets = new int[26];
			getout = false;
			a = scan.nextLine();
			b = scan.nextLine();
			if(a.equals("END") || b.equals("END"))
				break;
			else if(a.length() == b.length())
			{
				for(int i=0; i<a.length(); i++)
				{
					alets[a.charAt(i)-'0'-49]++;
					blets[b.charAt(i)-'0'-49]++;
				}
				for(int j=0; j<26; j++)
				{
					if(alets[j] != blets[j])
					{
						System.out.println("Case " + cnt + ": different");
						cnt++;
						getout = true;
						break;
					}
				}
				if(!getout)
				{
					System.out.println("Case " + cnt + ": same");
					cnt++;
				}
			}
			else
			{
				System.out.println("Case " + cnt + ": different");
				cnt++;
			}
		}
	}
}