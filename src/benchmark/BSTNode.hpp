//
// BSTNode.hpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#ifndef BSTNODE_HPP
#define BSTNODE_HPP

#include <iostream>
#include <iomanip>

using namespace std;

template <typename Data>
class BSTNode {
public:
    BSTNode<Data> *left;
    BSTNode<Data> *right;
    BSTNode<Data> *parent;
    Data const data;

    /** 
     * Constructor that initializes a BSTNode with the given data.
     */
    BSTNode(const Data &d) : data(d) {
        left = right = parent = nullptr;
    }

    /**
     * Find the successor of this node.
     *
     * The successor of a node is the node in the BST whose data
     * value is the next in the ascending order.
     *
     * Returns:
     *     the BSTNode that is the successor of this BSTNode,
     *     or 0 if there is none (this is the last node in the BST).
     */
    // TODO
    BSTNode<Data> *successor() 
	{
		BSTNode<Data> *curr = this;

		//If the current node has a right child, check the right subtree for
		//the successor node.
		if(curr->right != nullptr)
		{
			curr = curr->right;

			//Sets curr to the smallest node in the right subtree and returns.
			while(curr->left != nullptr)
			{
				curr = curr->left;
			}
			return curr;
		}

		//If the current node does not have a right child, then we know the
		//successor node must be one of the parent nodes.
		BSTNode<Data> *parent = curr->parent;

		//Recurses up through the BST until either of two conditions are met:
		//1) The parent node is null. (No successor node).
		//2) The current node is no longer the parent's right child. This
		//	 means that the parent node is now the successor of the current
		//	 node and we can simply return the parent.
		while(parent != nullptr && curr == parent->right)
		{
			//Set the current node to its parent
			//in order to recurse up the tree.
			curr = parent;

			//Updates the parent node to prepare for another iteration
			//through the while loop.
			parent = parent->parent;
		}
		return parent;
	}
};
		
/** 
 * Overload operator<< to print a BSTNode's fields to an ostream. 
 */
template <typename Data>
ostream &operator<<(ostream &stm, const BSTNode<Data> &n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
