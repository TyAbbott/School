import java.util.*;
import java.io.*;

public class triathlon
{
	public static void main(String[] args)
	{
		
		Scanner scan = new Scanner(System.in);
		int races = scan.nextInt();
		int comps, age;
		double rmiles, bmiles, smiles;
		String first, last;
		double swimtime, biketime, runtime, time;
		
		for(int i=1; i<=races; i++)
		{
			comps = scan.nextInt();
			smiles = scan.nextDouble();
			bmiles = scan.nextDouble();
			rmiles = scan.nextDouble();
			
			ArrayList<Competitor> list = new ArrayList<Competitor>();
			
			for(int j=0; j<comps; j++)
			{
				last = scan.next();
				first = scan.next();
				age = scan.nextInt();
				swimtime = scan.nextDouble();
				biketime = scan.nextDouble();
				runtime = scan.nextDouble();
				
				time = ((smiles/swimtime) + (bmiles/biketime) + (rmiles/runtime));
				list.add(new Competitor(first, last, age, time));
			}
			Collections.sort(list);
			System.out.println("Race " + i + ":");
			for(Competitor comp : list)
			{
				System.out.println(comp.getLname() + " " + comp.getFname() + " " + String.format("%.3f", comp.getTime()));
			}
			System.out.println();
		}
	}
}

class Competitor implements Comparable<Competitor>
{
	private String fname;
	private String lname;
	private int age;
	private double time;
	
	public int compareTo(Competitor c)
	{
		if(this.time == c.time)
		{
			if(this.age == c.age)
			{
				if(this.lname.equals(c.lname))
				{
					return this.fname.compareTo(c.fname);
				}
				else
					return this.lname.compareTo(c.lname);
			}
			else
				return this.age-c.age;
		}
		else if(this.time > c.time)
			return 1;
		else
			return -1;
	}
	
	public Competitor(String fname, String lname, int age, double time)
	{
		this.fname = fname;
		this.lname = lname;
		this.age = age;
		this.time = time;
	}
	
	public double getTime() { return (double)Math.round(time * 100000d) / 100000d; } 
	public String getFname() { return fname; } 
	public String getLname()	 { return lname; } 
}