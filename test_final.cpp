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

unsigned char makeByte(vector<int> x) {
    REQUIRE(x.size() == 8);
    unsigned char result = 0;
    for (int i = 0; i < 8; i++) {
        result <<= 1;
        if (x[i]) {
            result |= 1;
        }
    }
    return result;
}

TEST_CASE("Test makeByte") {
    CHECK(makeByte({0, 0, 0, 0, 0, 0, 0, 0}) == 0);
    CHECK(makeByte({0, 0, 0, 0, 0, 0, 0, 1}) == 1);
    CHECK(makeByte({0, 0, 1, 0, 1, 0, 1, 0}) == 42);
    CHECK(makeByte({1, 0, 0, 0, 0, 0, 0, 0}) == 128);
    CHECK(makeByte({1, 1, 1, 1, 1, 1, 1, 1}) == 255);
}

TEST_CASE("Single-byte bitwise encoding and decoding") {
    HCTree tree;
    vector<int> freqs(256, 0);
    freqs[10] = 1000;
    freqs[42] = 500;
    freqs[54] = 250;
    tree.build(freqs);

    //tree.printTree();

    ostringstream oss;
    BitOutputStream bos(oss);

    SECTION("compress1") {
        tree.encode(10, bos);
        bos.flush();
        string result_str = oss.str();
        vector<unsigned char> result(result_str.begin(), result_str.end());
        vector<unsigned char> expected { makeByte({1, 0, 0, 0, 0, 0, 0, 0}) };
        CHECK(result == expected);
    }

    SECTION("compress2") {
        tree.encode(42, bos);
        bos.flush();
        string result_str = oss.str();
        vector<unsigned char> result(result_str.begin(), result_str.end());
        vector<unsigned char> expected { makeByte({0, 1, 0, 0, 0, 0, 0, 0}) };
        CHECK(result == expected);
    }

    SECTION("compress3") {
        tree.encode(54, bos);
        bos.flush();
        string result_str = oss.str();
        vector<unsigned char> result(result_str.begin(), result_str.end());
        vector<unsigned char> expected { makeByte({0, 0, 0, 0, 0, 0, 0, 0}) };
        CHECK(result == expected);
    }

    SECTION("uncompress1") {
        string input_str = "";
        input_str.push_back(makeByte({1, 0, 0, 0, 0, 0, 0, 0}));
        istringstream iss(input_str);
        BitInputStream bis(iss);
        int result = tree.decode(bis);
        CHECK(result == 10);
    }

    SECTION("uncompress2") {
        string input_str = "";
        input_str.push_back(makeByte({0, 1, 0, 0, 0, 0, 0, 0}));
        istringstream iss(input_str);
        BitInputStream bis(iss);
        int result = tree.decode(bis);
        CHECK(result == 42);
    }

    SECTION("uncompress3") {
        string input_str = "";
        input_str.push_back(makeByte({0, 0, 0, 0, 0, 0, 0, 0}));
        istringstream iss(input_str);
        BitInputStream bis(iss);
        int result = tree.decode(bis);
        CHECK(result == 54);
    }
}

TEST_CASE("Multi-byte bitwise encoding and decoding") {
    HCTree tree;
    vector<int> freqs(256, 0);
    freqs[10] = 1000;
    freqs[42] = 500;
    freqs[54] = 250;
    tree.build(freqs);

    //tree.printTree();

    ostringstream oss;
    BitOutputStream bos(oss);

    SECTION("compress (8 bit result)") {
        tree.encode(10, bos);
        tree.encode(10, bos);
        tree.encode(42, bos);
        tree.encode(54, bos);
        tree.encode(54, bos);
        bos.flush();
        string result_str = oss.str();
        vector<unsigned char> result(result_str.begin(), result_str.end());
        vector<unsigned char> expected { makeByte({1, 1, 0, 1, 0, 0, 0, 0}) };
        CHECK(result == expected);
    }

    SECTION("compress (7 bit result)") {
        tree.encode(54, bos);
        tree.encode(10, bos);
        tree.encode(42, bos);
        tree.encode(42, bos);
        bos.flush();
        string result_str = oss.str();
        vector<unsigned char> result(result_str.begin(), result_str.end());
        vector<unsigned char> expected { makeByte({0, 0, 1, 0, 1, 0, 1, 0}) };
        CHECK(result == expected);
    }

    SECTION("uncompress (8 bit input)") {
        string input_str = "";
        input_str.push_back(makeByte({0, 0, 1, 0, 1, 0, 1, 0}));
        istringstream iss(input_str);
        BitInputStream bis(iss);
        vector<int> results;
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        vector<int> expected {54, 10, 42, 42};
        CHECK(results == expected);
    }

    SECTION("uncompress (7 bit input)") {
        string input_str = "";
        input_str.push_back(makeByte({1, 1, 0, 1, 0, 0, 0, 0}));
        istringstream iss(input_str);
        BitInputStream bis(iss);
        vector<int> results;
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        results.push_back(tree.decode(bis));
        vector<int> expected {10, 10, 42, 54, 54};
        CHECK(results == expected);
    }
}
