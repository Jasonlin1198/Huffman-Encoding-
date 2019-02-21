#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
    
    unsigned char buf;
    int nbits;
    ostream & stream;

public:
    BitOutputStream(ostream & o);
    void writeBit(bool bit);
    void flush();
};

#endif // BITOUTPUTSTREAM_HPP
