
#include "prn_scrambling.hpp"

namespace BinaryLayer
{

/*
The class that repeatedly generate 8-bit PRN binary sequences
Initialization:
    prn_generator pgen({0, 2, 5, 7});
    prn_generator pgen("0257");
Usage:
    string prn_seq = pgen.next(); // Can be repeatedly called
*/
//public:
prn_generator::prn_generator(vector<int> taps) {
    this->init(taps);
}

prn_generator::prn_generator(string taps) {
    vector<int> tapsvec;
    for (char c : taps) {
        tapsvec.push_back((int) (c - '0'));
    }
    this->init(tapsvec);
}

/*
Get the tap positions, returned as a binary string
*/
string prn_generator::getTaps() {
    string str = "";
    for (int n : this->prn_taps) {
        str += to_string(n);
    }
    return str;
}

/*
Generate next 8-bit PRN sequence
*/
string prn_generator::next() {
    string tapped = "";
    for (int t : this->prn_taps) {
        tapped += this->prn_seq[t];
    }

    char newbit = '0';
    for (char c : tapped) {
        newbit = this->myxor(newbit, c);
    }

    string new_prn = newbit + this->prn_seq.substr(0, 7);
    this->prn_seq = new_prn;
    return new_prn;
}

// private:
// vector<int> prn_generator::prn_taps;

// string prn_generator::prn_seq;

/*
The class initialization code that are common to
overloaded constructors
*/
void prn_generator::init(vector<int> taps) {
    if (!this->vailTaps(taps)) {
        throw invalid_argument("Invail tap positions. The values must be distinct integers selected from the range [0, 7]");
    }

    this->prn_taps = taps; // Store the tap positions
    this->prn_seq = string(8, '1'); // Intialize the PRN sequence
}
    
/*
Validate the tap position values
*/
bool prn_generator::vailTaps (const vector<int>& taps) {
    unordered_set<int> S; // For checking uniqueness
    auto goodValue = [](int d) -> bool {
        if (d >= 0 && d <= 7) {
            return true;
        } else {
            return false;
        }
    };
    for (int t : taps) {
        if (!goodValue(t)) { // The number is out of [0, 7]
            return false;
        }

        if (S.find(t) != S.end()) { // The number is not unique
            return false;
        }

        S.insert(t);
    }
    return true;
}

/*
Perform xor on binary characters ('0' and '1')
*/
char prn_generator::myxor(char a, char b) {
    // Validate input
    auto isBin = [](char c) -> bool {
        return c == '0' || c == '1';
    };
    if (!isBin(a) || !isBin(b)) {
        throw invalid_argument("Invalid input. The arguments must be either '0' or '1'");
    }

    auto char2Bool = [](char c) -> bool {
        return c == '1';
    };
    auto bool2Char = [](bool tf) -> char {
        if (tf) {
            return '1';
        } else {
            return '0';
        }
    };
    
    // Perform xor
    return bool2Char(char2Bool(a) ^ char2Bool(b));
}
// };


/*
Perform element-wise xor on two binary strings
*/
string strXor(const string& str1, const string& str2) {
    auto validChar = [](char c) -> void {
        if (c != '0' && c != '1') {
            throw invalid_argument("Invalid input string. It must consist of '1' and '0'");
        }
    };
    auto charXor = [&validChar](char a, char b) -> char {
        validChar(a);
        validChar(b);
        char ans = a != b ? '1' : '0';
        return ans;
    };
    auto theStrXor = [&charXor](const string& str1, const string& str2) -> string {
        size_t n = str1.length();
        if (n != str2.length()) {
            throw invalid_argument("Invalid input strings. Their lengths must be equal");
        }

        string ans = "";
        for (int i = 0; i < n; i++) {
            ans += charXor(str1[i], str2[i]);
        }
        return ans;
    };

    return theStrXor(str1, str2);
}


/*
Apply scrambling to a binary string. This can be used to both
scramble to descramble a string.
*/
string applySramble(const string& binStr, prn_generator& pgen) {
    // Validate the input string length
    if (binStr.length() % 8 != 0) {
        throw invalid_argument("Invalid input binary string. Its length must be a mulitple of 8");
    }

    string scrambledStr = "";
    for (auto it = binStr.begin(); it < binStr.end(); it += 8) {
        string prn_seq = pgen.next();
        string segm(it, it + 8);
        scrambledStr += strXor(prn_seq, segm);
    }

    return scrambledStr;
}

} // namespace BinaryLayer
