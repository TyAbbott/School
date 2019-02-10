import java.util.Scanner;

public class DiningPhilosophers4
{
    public static void main(String[] args) throws Exception 
	{
        Scanner scan = new Scanner(System.in);
		System.out.println("How many Philosophers? ");
		int n = scan.nextInt();
		
		Philosopher4[] philosophers = new Philosopher4[n];
        Object[] chopSticks = new Object[philosophers.length];
 
        for (int i=0; i<chopSticks.length; i++) 
		{
            chopSticks[i] = new Object();
        }
 
        for (int i=0; i<philosophers.length; i++) 
		{
            Object leftChopStick = chopSticks[i];
            Object rightChopStick = chopSticks[(i + 1) % chopSticks.length];
			
			// last philosopher
			if (i == philosophers.length - 1) 
			{
                // we just switch up the left and right chopstick to prevent a deadlock
                philosophers[i] = new Philosopher4(rightChopStick, leftChopStick); 
            } 
			else 
			{
                philosophers[i] = new Philosopher4(leftChopStick, rightChopStick);
            }
			
            Thread t = new Thread(philosophers[i], "Philosopher " + (i+1));
            t.start();
        }
    }
}