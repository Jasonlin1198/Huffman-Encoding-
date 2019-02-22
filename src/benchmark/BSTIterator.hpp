//
// BSTIterator.hpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP

#include <iterator>
#include <list>

#include "BSTNode.hpp"

using namespace std;

template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
private:
    BSTNode<Data> *curr;

public:
    /** 
     * Constructor that initializes a BSTIterator pointing to curr. 
     */
    // TODO
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** 
     * Dereference operator. 
     */
    Data operator*() const { 
        return curr->data; 
    }

    /** 
     * Pre-increment operator. 
     */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** 
     * Post-increment operator. 
     */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** 
     * Equality test operator. 
     */  
    // TODO
    bool operator==(BSTIterator<Data> const& other) const 
	{
		//Returns true if the curr field of the current BSTIterator and that
		//of the given BSTIterator point to the same memory address.
		if(curr == other.curr)
		{
			return true;
		}
		return false;
	}

    /** 
     * Inequality test operator. 
     */  
    // TODO
    bool operator!=(BSTIterator<Data> const& other) const 
	{
		//Returns true if the curr field of the current BSTIterator and that
		//of the given BSTIterator point to different memory addresses.
		if(curr != other.curr)
		{
			return true;
		}
		return false;
	}
};

#endif  // BSTITERATOR_HPP
