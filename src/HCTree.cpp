#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {
    deleteAll(root);
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    /* if tree is non-empty */
    if(!root){
	deleteAll(root);
    }

    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;

    /* intialize leaves in priority queue */
    for(int i = 0; i < freq.size() ; i++ ){
	if(freqs[i] != 0){
	    leaves[i]->count = freqs[i];
	    pq.push(leaves[i]);
	}
    } 

    HCNode* add1;
    HCNode* add2;
    NCNode* parental;
    int sum = 0;
    /* loop to create tree */
    while(pq.size() > 0){

	if(pq.size() == 1){
	    parental = pq.top();
	    break; 
	}

	add1 = pq.top();
	pq.pop();
	add2 = pq.top();
	pq.pop();
	
	/* sum of 2 node counts */
	sum = add1->count + add2->count; 
	parental->count = sum; 
	
	/* attach nodes to parent and parent's children*/
	parental->c0 = add1;
	parental->c1 = add2; 
	add1->parent = parental;
	add2->parent = parental; 
	
	/* sets symbol to be larger sym */
	parental->symbol = add2->symbol;

	pq.push(parental);
	


		


    }

}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // TODO (checkpoint)
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const {
    return 0;  // TODO (checkpoint)
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
