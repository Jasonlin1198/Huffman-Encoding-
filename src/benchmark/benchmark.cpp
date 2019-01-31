#include <iostream>
#include <set>
#include <random>
#include <cmath>
#include <vector>

#include "util.hpp"

using namespace std;

int main() {
    // This is an example of runtime benchmarking
    // TODO (final): Replace the following with a benchmarking comparison
    // of two data structures, as described in the project instructions

    int numTrials = 100;
    int dataSize = 3000;

    vector<long long> times(numTrials, 0);

    Timer t;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(-1.0, 1.0);

    // Run benchmarks and time each trial
    for (int trialIndex = 0; trialIndex < numTrials; trialIndex++) {
        // Set a new random seed
        generator.seed(1 + trialIndex);

        t.begin_timer();

        double total = 0.0;
        for (int dataIndex = 0; dataIndex < dataSize; dataIndex++) {
            double currentRandom = distribution(generator);
            total += currentRandom;
        }

        times[trialIndex] = t.end_timer();
    }

    // Compute statistics from trial times
    double totalTime = 0.0;
    for (int i = 0; i < numTrials; i++) {
        totalTime += times[i];
    }
    double meanTime = totalTime / ((double) numTrials);

    cout << "Elapsed time: " << totalTime << " nanoseconds ("
        << (totalTime / 1.0e9) << " seconds)" << endl;
    cout << "Mean: " << meanTime << " nanoseconds per trial" << endl;

    return 0;
}
