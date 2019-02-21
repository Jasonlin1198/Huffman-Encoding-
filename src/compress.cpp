#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    
    HCTree tree;
    ifstream theFile;
    int nextChar;
    theFile.open(infile, ios::binary);
    
    vector<int> freqs (256, 0);

    /* gets freq of symbols in file in vector */
    while(1)
	{
	nextChar = theFile.get();
        if(nextChar == theFile.eof()) 
		{
			break;
		}
		/* increments index of symbol that was read */
		freqs[nextChar]++;
    }
    
    /* build huffman tree with corresponding counts */ 
    tree.build(freqs);        

    /* opens output file */
    ofstream numFile;
    numFile.open(outfile, ios::binary);

    /* prints each count on new line */
    for(unsigned int i = 0; i < freqs.size() ; i++){
        numFile << freqs[i];
		numFile << '\n'; 
    }

    /* reset reading input file back to start */ 
    theFile.clear();
    theFile.seekg(0, theFile.beg);

    /* for each char, encode the symbol which prints to the same output stream*/
    while(1)
	{
	nextChar = theFile.get();
        if(nextChar == theFile.eof())
		{
			break;
		}
        tree.encode(nextChar, numFile);
    }

    theFile.close();
    numFile.close();

    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (ASCII)" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile) {
    HCTree tree;
    ifstream theFile;
    theFile.open(infile, ios::binary);
    unsigned char nextChar; 
    int nextByte;
    
    // checks if file exists 
    if(theFile.fail()){
	return;
    }
    
    vector<int> freqs (256, 0);
    
    // if file is empty, write 256 0's as header
    if(theFile.peek() == EOF){
	for(unsigned int x = 0; x < freqs.size() ; x++){
	    freqs[x] = 0; 
	}
    }
    else{ 
        /* gets freq of symbols in file in vector */
        while((nextByte = theFile.get()) != EOF) {
        
	/* increments index of symbol that was read */
	freqs[nextByte]++;
        }
    }   

    /* build huffman tree with corresponding counts */ 
    tree.build(freqs);        

    /* opens output file */
    ofstream numFile;
    numFile.open(outfile, ios::binary);

    // prints all 4 byte int freq values each with 4 bytes (not ascii value) without new line into compressed file header
    for(unsigned int x = 0; x < freqs.size() ; x++){
        numFile.write( (char*)&freqs[x], sizeof(freqs[x]) ); 
    }

    //resets the file back to the start
    theFile.close();
    theFile.open(infile, ios::binary);

    // creates bit stream to contain all raw bit data, 
    // initialized to have 0 buffer and counter 0 with the same outfile stream as header
    BitOutputStream stream = BitOutputStream(numFile);


    // reading raw data from a file
    while((nextByte = theFile.get()) != EOF){
	//casts to a byte size for encode parameter
	nextChar = (unsigned char)nextByte;

	//takes byte, puts in bitwise buffer and prints to ostream when full
        tree.encode(nextChar, stream);

    }

    //last call to flush to write out any last bits 
    stream.flush();

    //closes both input and output streams 
    theFile.close();
    numFile.close();

    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
}

int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
