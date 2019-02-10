// Ty Abbott
// COP 3503, Spring 2017
//============================
// GenericBST.java
//============================
// A standard binary search tree in java, that includes
// the standard methods of inserting and deleting nodes.
// This BST can take in any generic type, as long as
// it has a defined compareTo method.


import java.io.*;
import java.util.*;



// Node class of a generic type that has a defined
// compareTo method.  Each node has data and two
// pointers to the Node's left and right child.
class Node<T extends Comparable<T>>
{
	
	T data;
	Node<T> left, right;
	
	Node(T data)
	{
		this.data = data;
	}
}

public class GenericBST<T extends Comparable<T>>
{
	private Node<T> root;

	public void insert(T data)
	{
		root = insert(root, data);
	}

	// Simply navigates the tree to find the location where 
	// the new node fits in.  Lesser values go left and greater
	// values go to the right.  Equal values are not allowed.
	// Uses compareTo to evaluate generic values.
	private Node<T> insert(Node<T> root, T data)
	{
		if (root == null)
		{
			return new Node<T>(data);
		}
		else if (data.compareTo((T) root.data) < 0)
		{
			root.left = insert(root.left, data);
		}
		else if (data.compareTo((T) root.data) > 0)
		{
			root.right = insert(root.right, data);
		}
		else
		{
			// Stylistically, I have this here to explicitly state that we are
			// disallowing insertion of duplicate values. This is unconventional
			// and a bit cheeky.
			;
		}

		return root;
	}

	
	public void delete(T data)
	{
		root = delete(root, data);
	}

	
	// Navigates to the spot of the node that is being deleted.  
	// Once it finds the location of the Node to be deleted, 
	// it finds the node that will replace it and returns 
	// that node in its place.  This effectively deletes it.
	// If there's no node to replace the deleted node, 
	// that node becomes null. Uses compareTo to evaluate generic values.
	private Node<T> delete(Node<T> root, T data)
	{
		if (root == null)
		{
			return null;
		}
		else if (data.compareTo((T) root.data) < 0)
		{
			root.left = delete(root.left, data);
		}
		else if (data.compareTo((T) root.data) > 0)
		{
			root.right = delete(root.right, data);
		}
		else
		{
			if (root.left == null && root.right == null)
			{
				return null;
			}
			else if (root.right == null)
			{
				return root.left;
			}
			else if (root.left == null)
			{
				return root.right;
			}
			else
			{
				root.data = findMax(root.left);
				root.left = delete(root.left, (T) root.data);
			}
		}

		return root;
	}

	// This method assumes root is non-null, since this is only called by
	// delete() on the left subtree, and only when that subtree is non-empty.
	private T findMax(Node<T> root)
	{
		while (root.right != null)
		{
			root = root.right;
		}

		return (T) root.data;
	}

	// Returns true if the value is contained in the BST, false otherwise.
	public boolean contains(T data)
	{
		return contains(root, data);
	}

	// Recursively traverses the tree until it finds a null node, which
	// indicates the node wasn't found and the end of the tree has been 
	// reached, OR it finds the node and returns true.  Right is greater,
	// Left is lesser.
	private boolean contains(Node<T> root, T data)
	{
		if (root == null)
		{
			return false;
		}
		else if (data.compareTo((T) root.data) < 0)
		{
			return contains(root.left, data);
		}
		else if (data.compareTo((T) root.data) > 0)
		{
			return contains(root.right, data);
		}
		else
		{
			return true;
		}
	}
	
	// Traverses by: Left, Root, Right ordering.
	public void inorder()
	{
		System.out.print("In-order Traversal:");
		inorder(root);
		System.out.println();
	}

	private void inorder(Node<T> root)
	{
		if (root == null)
			return;

		inorder(root.left);
		System.out.print(" " + root.data);
		inorder(root.right);
	}

	//Traverses by: Root, Left, Right ordering.
	public void preorder()
	{
		System.out.print("Pre-order Traversal:");
		preorder(root);
		System.out.println();
	}

	private void preorder(Node<T> root)
	{
		if (root == null)
			return;

		System.out.print(" " + root.data);
		preorder(root.left);
		preorder(root.right);
	}
	
	//Traverses by: Left, Right, Root ordering.
	public void postorder()
	{
		System.out.print("Post-order Traversal:");
		postorder(root);
		System.out.println();
	}

	private void postorder(Node<T> root)
	{
		if (root == null)
			return;

		postorder(root.left);
		postorder(root.right);
		System.out.print(" " + root.data);
	}
	
	public static double difficultyRating()
	{
		return 1.5;
	}
	
	public static double hoursSpent()
	{
		return 4.0;
	}
}
