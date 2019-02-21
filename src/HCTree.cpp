#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree()
{
    deleteAll(root);
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs)
{
    /* if tree is non-empty */
    if(root)
	{
		delete(root);
    }

    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;

    /* intialize leaves in priority queue */
    for(unsigned int i = 0; i < freqs.size(); i++)
	{
		if(freqs[i] != 0)
		{
	    	/* makes new node, fills data, pushes on queue */
	    	HCNode* node = new HCNode(freqs[i], i);
	    	leaves[i] = node; 
	    	pq.push(node);
		}
    } 

    HCNode* add1;
    HCNode* add2;
	HCNode * parental;
    int sum = 0;

    /* loop to create tree */
    while(pq.size() > 1)
	{
        add1 = pq.top();
		pq.pop();
		add2 = pq.top();
		pq.pop();

		/* sum of 2 node counts */
		sum = add1->count + add2->count;

		/* set new parent to have larger symbol, c0 as lower count, c1 as higher count*/
		if(add1->symbol < add2->symbol)
		{
            parental = new HCNode(sum, add2->symbol, add1, add2);
        }
        else
		{
            parental = new HCNode(sum, add1->symbol, add1, add2);
		}

		/* attach nodes to parent and parent's children*/
		add1->p = parental;
		add2->p = parental;
	
		pq.push(parental);
    }

    root = pq.top();
	pq.pop();
}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const
{
    /* gets ref to node with corresponding symb */
    HCNode * leaf;
    leaf = leaves[symbol];

    /* stack to hold and reverse code */
    std::stack<int> code;

    /* while not at root yet */
    while(leaf != root)
	{
        if(leaf->p->c0 == leaf)
		{
	    	code.push(0);
		}
		else
		{
	    	code.push(1);
		}
		/* moves up one level */
		leaf = leaf->p;
    }

    /* writes out the entire stack content */
    while(!code.empty())
	{
        out << code.top();
		code.pop();
    }
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const
{
    HCNode * top = root;
    char nextChar;

    /* while there are bits to read, go down tree */
    while(top->c0 != nullptr || top->c1 != nullptr)
	{
		/* gets the next bit from the input stream */
        nextChar = in.get();
		if(in.eof())
		{
			break;
		}

        /* reads next 0/1 bit if and only if node is not a leaf yet */
        if(nextChar == '0' && top->c0 != nullptr)
		{
            top = top->c0;
		}
		else if(nextChar == '1' && top->c1 != nullptr)
		{
	    	top = top->c1; 
		}
    }

    return top->symbol;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const {
    return 0;  // TODO (final)
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}

/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }
}
 
void HCTree::deleteAll(HCNode * n)
{
	if(!n)
	{
	    return; 
	}
	deleteAll(n->c0);
	deleteAll(n->c1);
    
	delete n;
	return;
}
