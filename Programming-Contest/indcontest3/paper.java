import java.util.*;
import java.io.*;

public class paper
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int year = scan.nextInt();
		int exam, students, pages;
		int sheets;
		
		for(int i=0; i<year; i++)
		{
			exam = scan.nextInt();
			sheets = 0;
			for(int j=0; j<exam; j++)
			{
				students = scan.nextInt();
				pages = scan.nextInt();
				sheets += students * ((pages + 4 - 1) / 4);
			}
			System.out.println(sheets);
		}
	}
}