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

    /* opens output file */
    ofstream numFile;
    numFile.open(outfile, ios::binary);

	/* counts how many elements appear at least once */
	int numUnique = 0;
	int index = 0;
	for(unsigned int i = 0; i < freqs.size(); i++)
	{
		if(freqs[i] != 0)
		{
			numUnique++;
			index = i;
		}
	}

	/* if we only have one node in our tree */
	if(numUnique == 1)
	{
		for(int i = 0; i < freqs[index]; i++)
		{
			numFile << (unsigned char)index;
		}
	}

	/* if we have multiple nodes in our tree */
    if(numUnique > 1)
	{
   		while(!theFile.eof())
		{
			/* if we have already decoded the last letter, break the loop */
			if(theFile.peek() == EOF)
			{
				break;
			}
			/* adds symbol to output file */
        	numFile << (unsigned char)tree.decode(theFile);
		}
	}

    theFile.close();
    numFile.close();
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    HCTree tree;
    ifstream theFile;
    theFile.open(infile, ios::binary);

    /* holds all counts of symbols to pass in for build */
    vector<int> freqs (256, 0);

    // hold 4 bytes which is the value of the frequecy of symbols 
    int readN; 
    int numberOfCharsRead;

    // reads 1024 total bytes: loops 256 * 4 bytes per read
    for(unsigned int x = 0; x < freqs.size() ; x++){
        theFile.read( (char*)&readN, sizeof(readN) ); 
    
	//fills in freq vector with successive 4 bytes from compressed infile 
	freqs[x] = readN;

        //tracks how many characters were in the file based on header 
        numberOfCharsRead += freqs[x];  
    }

    //builds huffman tree
    tree.build(freqs);

    // opens output file 
    ofstream numFile;
    numFile.open(outfile, ios::binary);

    //creates a bitwise buffer stream 
    BitInputStream input = BitInputStream(theFile);

    int index = 0;

    //decodes only for exactly the number of symbols in the original file 
    while(index < numberOfCharsRead ) {

        numFile << (unsigned char)tree.decode(input);	

	index++;
    }

    theFile.close();
    numFile.close();

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
