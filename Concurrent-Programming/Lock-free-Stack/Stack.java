// Ty Abbott
// COP 4520
// Homework 1
// Stack.java

import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.*;

// Generic concurrent stack class
public class Stack<T>
{
	private AtomicReference<Node<T>> head;
	private AtomicInteger numOps = new AtomicInteger(0);
	
	public Stack()
	{
		head = new AtomicReference<Node<T>>();
	}
	
	public int getNumOps()
	{
		return numOps.get();
	}
	
	private static class Node<T>
	{
		private T val;
		Node<T> next = null;
		
		Node(final T val)
		{
			this.val = val;
		}
	}
	
	public boolean push(T x)
	{
		Node<T> n = new Node<T>(x);
		Node<T> headN = null;
		int existingVal, newVal;
		
		// Atomically push x into the stack
		do
		{
			headN = head.get();
			n.next = headN;
		} while(!head.compareAndSet(headN, n));
		
		// Atomically increment numOps
		do
		{
			existingVal = getNumOps();
			newVal = existingVal + 1;
		} while(!numOps.compareAndSet(existingVal, newVal));
			
		return true;
	}
	
	public T pop()
	{
		Node<T> n = head.get();
		int existingVal, newVal;
		
		// Atomically pop the head of the stack
		do
		{
			n = head.get();
			if(n == null)
				return null;
		} while(!head.compareAndSet(n, n.next));
		
		// Atomically increment numOps
		do
		{
			existingVal = getNumOps();
			newVal = existingVal + 1;
		} while(!numOps.compareAndSet(existingVal, newVal));
			
		return n.val;
	}
}