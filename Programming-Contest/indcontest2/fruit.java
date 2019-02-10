import java.util.*;
import java.io.*;

public class fruit
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int[] stand = new int[1000];
		int num = scan.nextInt();
		int deliv;
		int newdeliv;
		int extra;
		int total;

		for(int i=0; i<num; i++)
		{
			int days = scan.nextInt();
			deliv = -1;
			newdeliv = 0;
			total = 0;
			extra = -1;
			for(int j=1; j<=days; j++)
			{
				stand[j-1] = scan.nextInt();
				total += stand[j-1];
				newdeliv = (total + j-1)/j;
				deliv = Math.max(deliv, newdeliv);
			}
			total = 0;
			for(int k=0; k<days; k++)
			{
				total += deliv - stand[k];
				extra = Math.max(extra, total);
			}	
			System.out.println(deliv + " " + extra);
		}
	}
}