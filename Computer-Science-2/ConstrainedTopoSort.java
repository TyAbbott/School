package Assignments;

import java.util.*;
import java.io.*;

public class ConstrainedTopoSort 
{
	HashMap<Integer, ArrayDeque<Integer>> adjList = new HashMap<Integer, ArrayDeque<Integer>>();
	
	// read file into adjacency list where
	// the key is the vertex number
	// and the value is an ArrayDeque list
	// of vertices that go into the given vertex
	public ConstrainedTopoSort(String filename) throws FileNotFoundException
	{
		Scanner input = new Scanner(new File(filename));
		int numElements, size;
		
		size = input.nextInt();
		
		for(int i=0; i<size; i++)
		{
			numElements = input.nextInt();
			ArrayDeque<Integer> list = new ArrayDeque<Integer>();
			
			for(int j=0; j<numElements; j++)
				list.add(input.nextInt());
			
			adjList.put(i+1, list);
		}
	}
	
	// if x occurs before y in the adjacency list
	// this method will return true
	public boolean hasConstrainedTopoSort(int x, int y)
	{
		ArrayDeque<Integer> checkedVertices = new ArrayDeque<Integer>();
		ArrayDeque<Integer> verticesToCheck = new ArrayDeque<Integer>();
		int num;
		
		verticesToCheck = adjList.get(y).clone();
		
		while(!(verticesToCheck.isEmpty()))
		{
			num = verticesToCheck.pop();
			
			if(checkedVertices.contains(num))
				continue;
			
			else if(num == x)
				return false;
			
			else
			{
				verticesToCheck.addAll(adjList.get(num));
				checkedVertices.add(num);
			}
		}
		
		return true;
	}
	
	
	
	public static double difficultyRating()
	{
		return 2.5;
	}
	
	public static double hoursSpent()
	{
		return 10.0;
	}
}
