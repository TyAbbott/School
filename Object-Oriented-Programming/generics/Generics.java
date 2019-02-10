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
public class Generics {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        // invoking a generic type
        // no = new so no instantiation
        GenericBox<Integer> integerBoxV;
        
        // instantiating a generic type
        GenericBox<Integer> integerBoxI = new GenericBox<Integer>();
        GenericBox<String> integerBoxS = new GenericBox<String>();
        GenericBox<Float> integerBoxF = new GenericBox<Float>();

        // also valid since Java 7!
        GenericBox<Integer> integerBox = new GenericBox<>(); 

        // multiple parameters
        Pairs<String, Integer> p1 = new OrderedPairs<String, Integer>("Even", 8);
        Pairs<String, String>  p2 = new OrderedPairs<String, String>("hello", "world");
    
        // also valid
        OrderedPairs<String, Integer> p3 = new OrderedPairs<>("Even", 8);
        OrderedPairs<String, String>  p4 = new OrderedPairs<>("hello", "world");
        
        // passing parameterized type as a type
        OrderedPairs<String, GenericBox<Integer>> p = new OrderedPairs<>("primes", new GenericBox<Integer>());
    }
    
}
