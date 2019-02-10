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
public class OrderedPairs<K, V> implements Pairs<K, V> 
{
    private K key;
    private V value;

    @Override
    public K getKey() {
        return key;
    }

    @Override
    public V getValue() {
        return value;
    }
    public OrderedPairs(K key, V value) {
	this.key = key;
	this.value = value;
    }

}
