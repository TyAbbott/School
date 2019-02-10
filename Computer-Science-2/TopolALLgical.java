/*
 * Ty Abbott
 * TopolALLgical.java
 * CS II
 * Sean Szumlanski
 * TopolALLgical is a program designed to return
 * every possible topological sort of a given graph
 * using recursive backtracking to find the solution.
 */

import java.util.*;
import java.io.*;

public class TopolALLgical 
{

	// Creation of static variables to be used through out the program
	// adjList is a standard adjacency list
	// reverseAdjList maps each vertice that comes into a vertex
	// sorts is our HashSet of strings that holds our topo sorts
	
	static HashMap<Integer, ArrayDeque<Integer>> adjList = new HashMap<Integer, ArrayDeque<Integer>>();
	static HashMap<Integer, ArrayDeque<Integer>> reverseAdjList = new HashMap<Integer, ArrayDeque<Integer>>();
	static Set<String> sorts = new HashSet<String>();
	
	
	// Called by user that reads in the file, sets up our static variables, and calls our helper function
	
	public static HashSet<String> allTopologicalSorts(String filename) throws FileNotFoundException
	{
		
		int vertices, elements;
		
		// Reads the file and stores values into the adjacency list
		// input follows the format: 
		// first number represents total number of vertices
		// first number of each line represents number of elements per vertex
		// following numbers are adjacent vertices
		
		Scanner input = new Scanner(new File(filename));
		
		if(input == null)
			return (HashSet<String>) sorts;
		
		vertices = input.nextInt();
		
		for(int i=1; i<=vertices; i++)
		{
			elements = input.nextInt();
			ArrayDeque<Integer> list = new ArrayDeque<Integer>();
			
			for(int j=0; j<elements; j++)
				list.add(input.nextInt());
			
			adjList.put(i, list);
		}
		input.close();
		
		// Creates the reversed adjacency list used later to check if sorts are topological
		createReverseAdjList();
		
		HashSet<Integer> notValid = new HashSet<Integer>();
		
		int [] sort = new int[adjList.keySet().size()];
		
		// Calls the helper function used to create all possible topological sorts
		return allTopologicalSorts(sort, 0, notValid);	
	}
	
	private static HashSet<String> allTopologicalSorts(int [] sort, int element, HashSet<Integer> takenSpots)
	{
		
		// Base Case: Check if All Topological Sorts have been found
		
		int length = sort.length;
		if(element > length)
			return (HashSet<String>) sorts;
		
		// Generate all possible moves
		
		ArrayList<Integer> moves = new ArrayList<Integer>();
		
		if(element == 0)
		{
			// This is the first move, so we generate a move at
			// every vertex that doesn't have lines going into it.
			// This ensures we only start our list with vertices that work.
			
			for(int i=1; i<=length; i++)
				if(reverseAdjList.get(i).isEmpty())
					moves.add(i);
				
			if(moves.isEmpty())
				return (HashSet<String>) sorts;
		}
		
		else
			for(int i=1; i<=length; i++)
				if(!takenSpots.contains(i))
					moves.add(i);
		
		//a) Check if each moves works (yes continue on; no remove the vertex from the list)
		int possibleMove;
		
		for(int i=0; i<moves.size(); i++)
		{
			possibleMove = moves.get(i);
			ArrayDeque<Integer> t = reverseAdjList.get(possibleMove);
			Iterator<Integer> iter = t.iterator();
			
			while(iter.hasNext())
			{
				if(!(takenSpots.contains(iter.next())))
				{
					moves.remove(i--);
					break;
				}
					
				iter.next();
			}
		}
		
		if(element == length)
		{
			// Add sort to the HashSet
			sort[element-1] = moves.get(0);
			String topoSort = "";
			for(int i=0; i<element; i++)
				topoSort += (element == i+1)? sort[i] + " " : sort[i];
						
				sorts.add(topoSort);
			
			return allTopologicalSorts(sort, element+1, takenSpots);
		}
		
		else if(!moves.isEmpty())
		{
			for(int i=0; i<moves.size(); i++)
			{
				//b) Change parameters to reflect the new state
				possibleMove = moves.get(i);
				sort[element] = possibleMove;
				takenSpots.add(possibleMove);
			
				//c) Make recursive calls passing the changed parameters
				allTopologicalSorts(sort, element+1, takenSpots);
				
				//d) Undo the state change after returning from the recursive call
				takenSpots.remove(possibleMove);
			}	
		}
		
		else
		{
			// Reaches this if there are no possible moves
			return null;
		}
		
		return (HashSet<String>) sorts;
	}
	
	// The reverse adjacency list is of the form:
	// The key represents the vertex
	// The value is a list of values
	// that go into the key.
	
	private static void createReverseAdjList()
	{
		ArrayDeque<Integer> p = new ArrayDeque<Integer>();
		for(int i=1; i<=adjList.keySet().size(); i++)
		{
			p = adjList.get(i);
			for(int ver : p)
			{
				if(reverseAdjList.get(ver) == null)
				{
					ArrayDeque<Integer> q = new ArrayDeque<Integer>();
					q.add(i);
					reverseAdjList.put(ver, q);
				}
				else
				{
					ArrayDeque<Integer> r = reverseAdjList.get(ver);
					r.add(i);
					reverseAdjList.put(ver, r);
				}	
			}
		}
	}
	
	
	public static double difficultyRating()
	{
		return 3.0;
	}
	
	public static double hoursSpent()
	{
		return 17.0;
	}

}

