#ifndef _H_PRN_SCRAMBLING
#define _H_PRN_SCRAMBLING

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

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
    prn_generator(vector<int> taps);
    prn_generator(string taps);

    /*
    Get the tap positions, returned as a binary string
    */
    string getTaps();

    /*
    Generate next 8-bit PRN sequence
    */
    string next();

private:
    vector<int> prn_taps;
    string prn_seq;

    /*
    The class initialization code that are common to
    overloaded constructors
    */
    void init(vector<int> taps);

    /*
    Validate the tap position values
    */
    bool vailTaps (const vector<int>& taps);

    /*
    Perform xor on binary characters ('0' and '1')
    */
    char myxor(char a, char b);
};



/*
Apply scrambling to a binary string. This can be used to both
scramble to descramble a string.
*/
string applySramble(const string& binStr, prn_generator& pgen);

} // namespace BinaryLayer

#endif // _H_PRN_SCRAMBLING