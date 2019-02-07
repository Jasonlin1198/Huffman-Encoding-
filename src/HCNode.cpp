#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other) {

    /* less count checked */
    if( this.count < other.count ){
	return true; 
    }
    else if(other.count < this.count ){
	return false; 
    }
    else{
	/* tie break by symbol */
	if( (int)(this.symbol) < (int)(other.symbol) ){
	    return true; 
	}
	else{
	    return false; 
	}
    }


}
