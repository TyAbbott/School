import java.util.*;
import java.io.*;

public class trip
{
	public static void main(String[] args)
	{
		double total, childprice, adultprice, adult, child;
		int cases, childtickets, adulttickets;
		Scanner scan = new Scanner(System.in);
		cases = scan.nextInt();
		childprice = 0.00;
		adultprice = 0.00;
		childtickets = 0;
		adulttickets = 0;
		for(int i=0; i<cases; i++)
		{
			adultprice = scan.nextDouble();
			childprice = scan.nextDouble();
			adulttickets = scan.nextInt();
			childtickets = scan.nextInt();
			adult = (adultprice*(double)adulttickets);
			child = (childprice*(double)childtickets);
			total = adult+child;
			System.out.format("%.2f\n", total);
		}
	}

}