/*
Perform ASCII encoding and decoding

Function for encoding:
    string txt2bintxt(const string& txt);
Function for decoding:
    string binStr2Txt(const string& binStr);

*/

#include "ascii_endec.hpp"

namespace EncodingLayer {

/*
Convert an integer to 8-bit binary string
*/
string dec2bin8(int num) {
    string bin = "";
    while (num > 0) {
        bin = to_string(num % 2) + bin;
        num /= 2;
    }

    // Prepend zeros to make 8-bit-long binary string
    size_t pre_zero = 8 - bin.length();
    vector<char> zeros(pre_zero, '0');
    string z_str(zeros.begin(), zeros.end());
    return z_str + bin;
}

/*
Convert text (string of ascii characters) to binary string
*/
string txt2bintxt(const string& txt) {
    string bintxt = "";
    for (char c : txt) {
        bintxt += dec2bin8((int) c);
    }
    return bintxt;
}


/*
Convert an 8-bit binary string to an integer in decimal format
*/
int bin8_2dec(const string& bin) {
    if (bin.length() > 8) {
        throw invalid_argument("The length of the input binary string must not exceed 8.");
        return -1;
    }

    int dec = 0;

    for (char dig : bin) {
        dec *= 2;
        if (dig == '1') {
            dec += 1;
        } else if (dig != '0') {
            throw invalid_argument("Invalid digit for binary string.");
            return -1;
        }
    }

    return dec;
}


/*
Convert binary string to vector of ascii values
*/
vector<int> bintxt2asciivec(const string& bintxt) {
    vector<int> asciivec;
    for (auto it = bintxt.begin(); it < bintxt.end(); it += 8) {
        string bin8txt(it, it + 8);
        int asciival = bin8_2dec(bin8txt);
        asciivec.push_back(asciival);
    }
    return asciivec;
}


/*
Convert vector of ascii values to text
*/
string asciivec2txt(const vector<int>& asciivec) {
    string txt = "";
    for (int ascii : asciivec) {
        txt += static_cast<char>(ascii);
    }
    return txt;
}


/*
Decoding binary string to string of ascii characters
*/
string binStr2Txt(const string& binStr) {
    auto asciivec = bintxt2asciivec(binStr);
    auto txt = asciivec2txt(asciivec);
    return txt;
}

} // namespace EncodingLayer