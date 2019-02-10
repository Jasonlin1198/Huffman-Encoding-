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
    theFile.open(infile);
    
    vector<int> freqs (256, 0);

    /* gets freq of symbols in file in vector */
    while(1)
	{
		nextChar = theFile.get();
        if(theFile.eof()) 
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
    numFile.open(outfile);

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
        if(theFile.eof())
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
    // TODO (final)
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
