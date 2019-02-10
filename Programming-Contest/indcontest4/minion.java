import java.util.*;
import java.io.*;

public class minion
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int num = scan.nextInt();
		int trials, vertices, edges, n, m;
		String word;
		int val = 0;
		

		
		for(int i=0; i<num; i++)
		{
			HashSet<String> forbidden = new HashSet<String>();
			trials = scan.nextInt();
			for(int j=0; j<trials; j++)
			{
				forbidden.add(scan.next());
			}
			
			vertices = scan.nextInt();
			edges = scan.nextInt();
			
			@SuppressWarnings("unchecked")
			ArrayList<Integer>[] graph = (ArrayList<Integer>[]) new ArrayList[vertices];
			for(int p=0; p<vertices; p++)
				graph[p] = new ArrayList<Integer>();
			
			for(int k=0; k<edges; k++)
			{
				n = scan.nextInt();
				m = scan.nextInt();
				word = scan.next();
				if(!(forbidden.contains(word)))
				{
					if(!(graph[n].contains(m)))
						graph[n].add(m);
					if(!(graph[m].contains(n)))
						graph[m].add(n);
				}
			}
			HashSet<Integer> visited = new HashSet<Integer>();
			val = traverse(graph, 0, vertices-1, visited);
			System.out.println(val);
		}
	}
	
	public static int traverse(ArrayList<Integer>[] graph, int current, int target, HashSet<Integer> visited)
	{
		if(current == target)
			return 1;
		else
		{
			ArrayList<Integer> tocheck = graph[current];
			for(Integer i : tocheck)
			{
				if(i == target)
					return 1;
				else if(visited.contains(i))
					continue;
				else
				{
					visited.add(i);
					return 0+traverse(graph, i, target, visited);
				}	
			}
			return 0;
		}
	}
}