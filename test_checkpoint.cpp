#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

TEST_CASE("Single-byte ASCII encoding and decoding") {
    HCTree tree;
    vector<int> freqs(256, 0);
    freqs[10] = 1000;
    freqs[42] = 500;
    freqs[54] = 250;
    tree.build(freqs);

    //tree.printTree();

    ostringstream oss;

    SECTION("compress1") {
        tree.encode(10, oss);
        string result = oss.str();
        CHECK(result == "1");
    }

    SECTION("compress2") {
        tree.encode(42, oss);
        string result = oss.str();
        CHECK(result == "01");
    }

    SECTION("compress3") {
        tree.encode(54, oss);
        string result = oss.str();
        CHECK(result == "00");
    }

    SECTION("uncompress1") {
        istringstream iss("1");
        int result = tree.decode(iss);
        CHECK(result == 10);
    }

    SECTION("uncompress2") {
        istringstream iss("01");
        int result = tree.decode(iss);
        CHECK(result == 42);
    }

    SECTION("uncompress3") {
        istringstream iss("00");
        int result = tree.decode(iss);
        CHECK(result == 54);
    }
}

TEST_CASE("Multi-byte ASCII encoding and decoding") {
    HCTree tree;
    vector<int> freqs(256, 0);
    freqs[10] = 1000;
    freqs[42] = 500;
    freqs[54] = 250;
    tree.build(freqs);

    //tree.printTree();

    ostringstream oss;

    SECTION("compress") {
        tree.encode(54, oss);
        tree.encode(10, oss);
        tree.encode(42, oss);
        tree.encode(42, oss);
        string result = oss.str();
        CHECK(result == "0010101");
    }

    SECTION("uncompress") {
        istringstream iss("11010000");
        vector<int> results;
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        vector<int> expected {10, 10, 42, 54, 54};
        CHECK(results == expected);
    }
}

TEST_CASE("Handle ties: ASCII encoding and decoding") {
    HCTree tree;
    vector<int> freqs(256, 0);
    freqs[10] = 250;
    freqs[42] = 500;
    freqs[54] = 250;
    tree.build(freqs);

    //tree.printTree();

    ostringstream oss;

    SECTION("compress") {
        tree.encode(54, oss);
        tree.encode(10, oss);
        tree.encode(42, oss);
        tree.encode(42, oss);
        string result = oss.str();
        CHECK(result == "111000");
    }

    SECTION("uncompress") {
        istringstream iss("01001011");
        vector<int> results;
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        results.push_back(tree.decode(iss));
        vector<int> expected {42, 10, 42, 10, 54};
        CHECK(results == expected);
    }
}
