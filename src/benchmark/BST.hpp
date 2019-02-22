//
// BST.hpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;

template <typename Data>
class BST {
protected:
    // Pointer to the root of this BST, or 0 if the BST is empty.
    BSTNode<Data> *root;

    // Number of elements stored in this BST.
    unsigned int isize;

    // Height of this BST.
    unsigned int iheight;

public:
    // Define iterator as an aliased typename for BSTIterator<Data>.
    typedef BSTIterator<Data> iterator;

    /** 
     * Default constructor. Initializes an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** 
     * Default destructor. Frees all memory allocated by this BST.
     */
    // TODO
    virtual ~BST() 
	{
		deleteAll(root);
		isize = 0;
		iheight = 0;
	}

    /** 
     * Inserts the given item into this BST.
     *
     * This function should use only the '<' operator when comparing
     * Data items. (do not use ==, >, <=, >=). For the reasoning
     * behind this, see the assignment writeup.
     *
     * Parameters:
     *     item Data item to insert into this BST
     *
     * Returns:
     *     true if the item was inserted as a consequence of calling
     *     this function, false otherwise (e.g. item is a duplicate).
     */
    // TODO
    virtual bool insert(const Data &item) 
	{
		int currHeight = 0;

		//If the BST is empty, insert the new node as the root.
		if(root == nullptr)
		{
			root = new BSTNode<Data>(item);
			isize++;
			iheight++;
			return true;
		}

		BSTNode<Data> *curr = root;
		BSTNode<Data> *prev = nullptr;

		//Iterates through the BST, updating curr and prev as we go.
		while(curr != nullptr)
		{
			//If the new node's data is smaller, go to the left child.
			if(item < curr->data)
			{
				prev = curr;
				curr = curr->left;
				currHeight++;
			}
			//If the new node's data is larger, go to the right child.
			else if(curr->data < item)
			{
				prev = curr;
				curr = curr->right;
				currHeight++;
			}
			//If the new node's data is equal to another, return false.
			else
			{
				return false;
			}
		}

		//Set the new node's parent to prev as the left or right child.
		if(item < prev->data)
		{
			prev->left = new BSTNode<Data>(item);
			prev->left->parent = prev;
			currHeight++;
		}
		else
		{
			prev->right = new BSTNode<Data>(item);
			prev->right->parent = prev;
			currHeight++;
		}

		//Updates the isize and iheight variables and returns true.
		isize++;
		if(currHeight > iheight)
		{
			iheight = currHeight;
		}

		return true;
	}

    /**
     * Searches for the given item in this BST.
     *
     * This function should use only the '<' operator when comparing
     * Data items. (should not use ==, >, <=, >=). For the reasoning
     * behind this, see the assignment writeup.
     *
     * Parameters:
     *     item Data item to search for in this BST.
     *
     * Returns:
     *     An iterator pointing to the item if found, or pointing 
     *     past the last node in this BST if item is not found.
     */
    // TODO
    virtual iterator find(const Data &item) const
	{
		//If the tree is empty, return an iterator pointing past the last node.
		if(root == nullptr)
		{
			return typename BST<Data>::iterator(0);
		}	

		BSTNode<Data> *curr = root;

		//Iterates through the BST, updating curr as we go.
		while(curr != nullptr)
		{
			//If the new node's value is equal to the current node's,
			//then return an iterator pointing to the current node.
			if(!(item < curr->data) && !(curr->data < item))
			{
				return typename BST<Data>::iterator(curr);
			}
			else if(item < curr->data)
			{
				curr = curr->left;
			}
			else if(curr->data < item)
			{
				curr = curr->right;
			}
		}

		return typename BST<Data>::iterator(0);
	}

    /** 
     * Returns the number of items currently in the BST.
     */
    // TODO
    unsigned int size() const 
	{
		return isize;
	}

    /** 
     * Returns the height of this BST.
     */
    // TODO
    unsigned int height() const 
	{
		return iheight;
	}

    /** 
     * Returns true if this BST is empty, false otherwise.
     */
    // TODO
    bool empty() const 
	{
		//If the tree has 0 elements, return true. Otherwise, return false.
		if(size() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    /** 
     * Returns an iterator pointing to the first item in the BST (not the root).
     */
    // TODO
    iterator begin() const 
	{
		BSTNode<Data> *node = first(root);
		return typename BST<Data>::iterator(node);
	}

    /** 
     * Returns an iterator pointing past the last item in the BST.
     */
    iterator end() const { 
        return typename BST<Data>::iterator(0); 
    }

    /** 
     * Prints the elements in this BST in ascending order.
     */
    void inorder() const { 
        inorder(root); 
    }

private:
    /*
     * Find the first node in the given subtree with root curr.
     */
    static BSTNode<Data>* first(BSTNode<Data> *curr) {
        if (!curr) return 0;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    /* 
     * Do an inorder traversal, printing the data in ascending order.
     *
     * You can achieve an inorder traversal recursively by following 
     * the order below.
     *
     *     recurse left - print node data - recurse right
     */
    // TODO
    static void inorder(BSTNode<Data> *n) 
	{
		//If the tree is empty, do nothing.
		if(n == nullptr)
		{
			return;
		}

		inorder(n->left);
		cout << n->data << endl;
		inorder(n->right);
	}

    /* 
     * Do a postorder traversal, deleting nodes.
     *
     * You can achieve a postorder traversal recursively by following 
     * the order below.
     *
     *     recurse left - recurse right - delete node
     */
    // TODO
    static void deleteAll(BSTNode<Data> *n) 
	{
		//If the tree is empty, do nothing.
		if(n == nullptr)
		{
			return;
		}

		deleteAll(n->left);
		deleteAll(n->right);
		delete(n);
	}
};

#endif  // BST_HPP
