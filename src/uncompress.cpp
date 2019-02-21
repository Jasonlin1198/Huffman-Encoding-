#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile)
{
    HCTree tree;
	ifstream theFile;
	int nextChar;
    theFile.open(infile, ios::binary);

    /* holds all counts of symbols to pass in for build */
    vector<int> freqs(256, 0);

    /* loops through each of the 256 ascii chars in the header and 
	 * constructs the frequencies vector to build the Huffman tree */
    for(unsigned int i = 0; i < freqs.size(); i++)
	{
		theFile >> nextChar;
		freqs[i] = nextChar;
    }

    /* build huffman tree from header info */
    tree.build(freqs);

	/* gets rid of the last newline char in the header */
	nextChar = theFile.get();

    /* opens output file */
    ofstream numFile;
    numFile.open(outfile, ios::binary);

    /* loop for the line that contains the bits to uncompress */
    while(1)
	{
		if(theFile.eof())
		{
			break;
		}
		/* adds symbol to output file */
        numFile << (char)tree.decode(theFile);
	}

    theFile.close();
    numFile.close();

    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (ASCII)" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile)
{
    // TODO (final)
    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
}

int main(int argc, char ** argv)
{
    string infile = "";
    string outfile = "";
    bool bitwise = false;

    for(int i = 1; i < argc; i++)
	{
        string currentArg = argv[i];
        if(currentArg == "-b")
		{
            bitwise = true;
        }
		else if(infile == "")
		{
            infile = currentArg;
        } 
		else
		{
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "")
	{
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if(bitwise)
	{
        uncompressBitwise(infile, outfile);
    }
	else
	{
        uncompressAscii(infile, outfile);
    }

    return 0;
}
