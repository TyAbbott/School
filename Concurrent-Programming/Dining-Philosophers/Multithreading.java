import java.util.*;
import java.io.*;

class Multithreading implements Runnable
{
	public void run()
	{
		try
		{
			System.out.println("Thread " + 
								Thread.currentThread().getId() +
								" is running");
		}
		catch(Exception e)
		{
			System.out.println("Exception caught");
		}
	}
}