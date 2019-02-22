#include "BitOutputStream.hpp"


BitOutputStream::BitOutputStream(ostream & o) : stream(o), buf(0), nbits(0) {}

void BitOutputStream::writeBit(bool bit)
{
	//flush the bitwise buffer if it is full
	if(nbits == 8)
	{
	    flush();
	}

	//shifts bits left one assuming there are 7 or less bits filled
	buf = buf << 1;

	//sets right most bit to be value of the bool bit
	buf = buf | bit; 

	//increment number of bits in bitwise buffer
	nbits++;
}

void BitOutputStream::flush()
{
	//handle the case of not full
	if(nbits != 8 && nbits != 0)
	{
		//shifts bits to rightmost with padded 0's
		buf = buf << (8 - nbits); 
	}
	//continues full buf to write to ostream 

	stream.put(buf); //write the bitwise buffer to the ostream 
	stream.flush();

	//resets buf and its counter when flushed
	buf = 0;
	nbits = 0;
}

