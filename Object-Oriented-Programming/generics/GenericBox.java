/*
 * Karin Whiting
 * COP 3330 Object Oriented Programming
 * University of Central Florida
 */
package generics;

/**
 *
 * @author kwhiting
 */
public class GenericBox<T> 
{
    // T stands for "Type"
    private T t;

    public void set(T t) 
    { 
        this.t = t; 
    }
    
    public T get() 
    { 
        return t; 
    }
}
