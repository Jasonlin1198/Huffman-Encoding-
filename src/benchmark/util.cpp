#include <iostream>
#include "util.hpp"

using std::istream;
using std::endl;
using std::cout;
using std::string;
using std::vector;

/*
 * Starts the timer. Saves the current time.
 */
void Timer::begin_timer()
{
    start = std::chrono::high_resolution_clock::now();
}

/*
 * Ends the timer. Compares end time with the start time and returns number of nanoseconds
 */
long long Timer::end_timer()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    end = std::chrono::high_resolution_clock::now();

    return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/*
 * Load all lines from istream `in` into the vector `v`
 */
void Utils::load_vector(vector<string>& v, istream& in)
{
    string line = "";
    while (true) {
        getline(in, line);
        if (in.eof())
            break;
        v.push_back(line);
    }
}

/*
 * Load the specified number of lines from istream `in` into the vector `v`
 */
void Utils::load_vector(vector<string>& v, istream& in, unsigned int num_lines)
{
    string line = "";
    for (unsigned int i = 0; i < num_lines; i++) {
        getline(in, line);
        if (in.eof()) {
            std::cout << "Warning!  Only " << i << " lines read from file." << endl;
            break;
        }
        v.push_back(line);
    }
}

