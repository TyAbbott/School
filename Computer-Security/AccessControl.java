/* AccessControl.java
 * Ty Abbott
 * Fall 2017
 * CIS 3360
 */
 
import java.util.*;
import java.io.*;

public class AccessControl
{
	public static void main(String args[])
	{
		String fileone = args[0];
		String filetwo = args[1];
		String filethree = args[2];
		
		int[][] matrix = createMatrix(fileone);
		LinkedList<String> = createControlList(filetwo);
		LinkedList<String> = createCapabilityList(filethree);
	}
	
	public int[][] createMatrix(String file)
	{	
		try
		{
			Scanner scan = new Scanner(file);
			int rows = scan.nextInt();
			int cols = scan.nextInt();
			
			int[][] matrix = new int[rows][cols];
			
			for(int i=0; i<rows; i++)
				for(int j=0; j<cols; j++)
					matrix[i][j] = scan.nextInt();
		
		}
		
		catch(Exception e)
		{
			e.printStackTrace();
		}
		
		return matrix;
		
	}
	
	
	
}