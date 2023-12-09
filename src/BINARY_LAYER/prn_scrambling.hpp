#ifndef _H_PRN_SCRAMBLING
#define _H_PRN_SCRAMBLING

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <random>
#include "north_interface.hpp"

using namespace std;

namespace BinaryLayer {

/*
The class that repeatedly generate 8-bit PRN binary sequences
Initialization:
    prn_generator pgen({0, 2, 5, 7});
    prn_generator pgen("0257");
Usage:
    string prn_seq = pgen.next(); // Can be repeatedly called
*/
class prn_generator {
public:
    //prn_generator(vector<int> taps);
    prn_generator(string taps);

    /*
    Get the tap positions, returned as a binary string
    */
    string getTaps();

    /*
    Generate next 8-bit PRN sequence
    */
    string next();

    /*
    Generate an encryption key
    */
    static string genKey();

private:
    /*
    The vector of tap positions. Positions are 0-based
    */
    vector<size_t> prn_taps;

    /*
    The PRN sequence, represented as a 0-1 string
    */
    string prn_seq;

    /*
    The iterator that points to the begin of each 
    scrambling block. Each block has the length 8.
    */
    string::iterator scrm_bgn;

    /*
    The class initialization code that are common to
    overloaded constructors
    */
    void init(vector<size_t> taps);

    /*
    Validate the tap position values
    */
    bool validTaps (const vector<size_t>& taps);

    /*
    Validate the encryption key
    */
    bool validKey(const string);

    /*
    Perform xor on binary characters ('0' and '1')
    */
    char myxor(char a, char b);
};


/*
Draw a random integer from an interval
*/
static int oneRandInt(int l_b, int u_b);


/*
Draw k random distinct numbers from an interval of length N
*/
static unordered_set<int> randKFromN(int l_b, int u_b, int k);


/*
Perform element-wise xor on two binary strings
*/
string strXor(const string& str1, const string& str2);


/*
Apply scrambling to a binary string. This can be used to both
scramble to descramble a string.
*/
string applySramble(const string& binStr, prn_generator& pgen);

} // namespace BinaryLayer

#endif // _H_PRN_SCRAMBLING