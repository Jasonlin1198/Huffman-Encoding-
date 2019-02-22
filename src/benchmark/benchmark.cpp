#include <iostream>
#include <set>
#include <random>
#include <cmath>
#include <vector>

#include "BST.hpp"
#include "util.hpp"

using namespace std;

int main()
{
	/* Prompts the user to choose between inserting/finding elements
	 * in the BST or Red-Black Tree. */
	char c = '0';
	bool flag = false;

	cout << "Please enter 'i' for insert or 'f' for find: ";
	cin  >> c;

	if(c == 'i')
	{
		flag = true;
	}
	else if(c == 'f')
	{
		flag = false;
	}
	else
	{
		cout << "Error: Invalid input.";
		return(0);
	}

	/* Prompts the user for the number of trials and input size */
    int numTrials = 0; /* Number of times we will insert/find */
    int dataSize = 0; /* The input size of the BST */
	cout << "Please enter the number of trials: ";
	cin  >> numTrials;
	cout << "Please enter the datasize: ";
	cin  >> dataSize;

	/* 1. Benchmark test for non self-balancing BST */
	BST<double> tree; /* Defines a BST<Double> */

    vector<long long> times(numTrials, 0);

    Timer t;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(-1.0, 1.0);

    // Run benchmarks and time each trial
    for(int trialIndex = 0; trialIndex < numTrials; trialIndex++)
	{
        // Set a new random seed
        generator.seed(1 + trialIndex);

        t.begin_timer(); /* Starts the timer */

		//if the user specified insert
		if(flag)
		{
        	for(int dataIndex = 0; dataIndex < dataSize; dataIndex++)
			{
            	double currentRandom = distribution(generator);
            	tree.insert(currentRandom);
			}
        }
		else //if the user specified find
		{
        	for(int dataIndex = 0; dataIndex < dataSize; dataIndex++)
			{
            	double currentRandom = distribution(generator);
            	tree.find(currentRandom);
			}
        }

        times[trialIndex] = t.end_timer(); /* Ends the timer */
    }

	/* 2. Benchmark test for Red-Black Tree */
	set<double> tree2; /* Defines a set<Double> */

    vector<long long> times2(numTrials, 0);

    // Run benchmarks and time each trial
    for(int trialIndex = 0; trialIndex < numTrials; trialIndex++)
	{
        // Set a new random seed
        generator.seed(1 + trialIndex);

        t.begin_timer(); /* Starts the timer */

		//if the user specified insert
		if(flag)
		{
        	for(int dataIndex = 0; dataIndex < dataSize; dataIndex++)
			{
            	double currentRandom = distribution(generator);
            	tree2.insert(currentRandom);
			}
        }
		else //if the user specified find
		{
        	for(int dataIndex = 0; dataIndex < dataSize; dataIndex++)
			{
            	double currentRandom = distribution(generator);
            	tree2.find(currentRandom);
			}
        }

        times2[trialIndex] = t.end_timer(); /* Ends the timer */
    }

    //Finds the total time for the BST
    double bstTime = 0.0;
    for(int i = 0; i < numTrials; i++)
	{
        bstTime += times[i];
    }

	//Finds the total time for the RBT
	double rbtTime = 0.0;
	for(int i = 0; i < numTrials; i++)
	{
		rbtTime += times2[i];
	}

    double meanTime = bstTime / ((double) numTrials);
	double meanTime2 = rbtTime / ((double) numTrials);

	/* Output the data from both trials */
    cout << "Elapsed time: " << bstTime << " nanoseconds ("
        << (bstTime / 1.0e9) << " seconds)" << endl;
    cout << "Mean: " << meanTime << " nanoseconds per trial" << endl;

	cout << "\n";

    cout << "Elapsed time: " << rbtTime << " nanoseconds ("
        << (rbtTime / 1.0e9) << " seconds)" << endl;
    cout << "Mean: " << meanTime2 << " nanoseconds per trial" << endl;

    return 0;
}
