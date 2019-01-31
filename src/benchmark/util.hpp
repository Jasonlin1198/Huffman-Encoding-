#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <vector>
#include <string>
#include <iostream>

using std::istream;

class Timer{
private:
    /* start the timer */
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    /*
     * Function called when starting the timer.
     */
    void begin_timer();

    /*
     * Function called when ending the timer. Returns duration in nanoseconds
     * PRECONDITION: begin_timer() must be called before this function
     */
    long long end_timer();
};

class Utils{
public:
    /*
     * Load all lines from istream `in` into the vector `v`
     */
    void static load_vector(std::vector<std::string>& v, istream& in);

    /*
     * Load the specified number of lines from istream `in` into the vector `v`
     */
    void static load_vector(std::vector<std::string>& v, istream& in, unsigned int num_lines);
};

#endif //UTIL_H
