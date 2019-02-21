#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv)
{
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
void compressAscii(const string & infile, const string & outfile)
{
	HCTree tree; /* Huffman Tree */
    ifstream theFile; /* Input filestream */
    int nextByte; /* Stores the next byte to be read */
    theFile.open(infile, ios::binary); /* opens input filestream */
    
    vector<int> freqs(256, 0);

    /* Reads in the input file and then updates the frequency of each symbol */
    while((nextByte = theFile.get()) != EOF)
	{
		/* increments the index of the symbol that was read */
		freqs[nextByte]++;
    }
    
    /* build huffman tree with corresponding counts */ 
    tree.build(freqs);

    /* opens output file */
    ofstream numFile;
    numFile.open(outfile, ios::binary);

    /* creates the header by printing each count on a new line */
    for(unsigned int i = 0; i < freqs.size(); i++)
	{
        numFile << freqs[i] << endl;
    }

    /* reset reading input file back to the start */ 
    theFile.clear();
    theFile.seekg(0, theFile.beg);

    /* for each character, encode the symbol and print it
	 * to the same output stream */
    while((nextByte = theFile.get()) != EOF)
	{
        tree.encode(nextByte, numFile);
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
void compressBitwise(const string & infile, const string & outfile)
{
    // TODO (final)
    cerr << "TODO: compress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
}

int main(int argc, char ** argv)
{
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
