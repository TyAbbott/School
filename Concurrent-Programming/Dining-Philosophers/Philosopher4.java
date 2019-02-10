public class Philosopher4 implements Runnable 
{
 
    // The chopsticks on left and right side
    private Object leftChopStick;
    private Object rightChopStick;
 
    public Philosopher4(Object leftChopStick, Object rightChopStick) 
	{
        this.leftChopStick = leftChopStick;
        this.rightChopStick = rightChopStick;
    }
	
    @Override
    public void run() 
	{
        try {
            while (true) 
			{
                // Thinking
                doAction(" is now thinking.");
                synchronized (leftChopStick) 
				{
                    // Hungry (tries to pick up left chop stick)
					doAction(" is now hungry.");
                    synchronized (rightChopStick) 
					{
                        // Eating
                        doAction(" is now eating."); 
                    }
                    // Back to thinking (call different function to add delay)
                    doAction1(" is now thinking.");
                }
            }
        } 
		catch (InterruptedException e) 
		{
            Thread.currentThread().interrupt();
            return;
        }
    }
	
	private void doAction(String action) throws InterruptedException
	{
        System.out.println(
          Thread.currentThread().getName() + " " + action);
        Thread.sleep(((int) (Math.random() * 100)));
    }
	
	// This is only called after a philosopher finishes eating.  
	// It has an extra delay to prevent starvation.
	private void doAction1(String action) throws InterruptedException
	{
        System.out.println(
          Thread.currentThread().getName() + " " + action);
        Thread.sleep(((int) (Math.random() * 100))+ 100);
    }
 
}