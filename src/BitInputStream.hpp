#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
    unsigned char buf;
    int nbits;
    istream & in;

public:
    BitInputStream(istream & i);
    bool readBit();
};

#endif // BITINPUTSTREAM_HPP
