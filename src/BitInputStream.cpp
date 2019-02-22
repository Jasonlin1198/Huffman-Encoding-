#include "BitInputStream.hpp"


BitInputStream::BitInputStream(istream & i) : in(i), buf(0), nbits(8){}


//returns 1 or 0 based on next bit in stream 
bool BitInputStream::readBit()
{
	if(nbits == 8)
	{
	    buf = in.get(); // read one byte from istream to bitwise buffer
	    nbits = 0; // resets counters of read bits to 0   
	}

	// gets left most bit in buffer
	bool nextBit = buf & 128;
	buf = buf << 1; 

	//increments the number of bits read from the bitwise buffer
	nbits++;

	return nextBit; 
}

