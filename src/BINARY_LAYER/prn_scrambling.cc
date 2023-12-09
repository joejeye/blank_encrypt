
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
//prn_generator::prn_generator(vector<int> taps) {
//    this->init(taps);
//}

prn_generator::prn_generator(string key) {
    // Validate encryption key
    bool isvalid = this->validKey(key);
    if (!isvalid) {
        throw invalid_argument("[prn_generator::prn_generator] Invalid encryption key");
    }

    // Convert key to binary string
    string binKey = "";
    for (char c : key) {
        binKey += OneHex2FourBin(c);
    }

    // Init the PRN sequence
    this->prn_seq = string(binKey.length(), '1');

    // Get the tap positions
    vector<size_t> tapsvec;
    for (size_t i = 0; i < binKey.length(); i++) {
        if (binKey[i] == '1') {
            tapsvec.push_back(i);
        }
    }

    // Validate the number of taps
    size_t n_taps = tapsvec.size();
    if (n_taps % 2 != 0) {
        throw invalid_argument("[prn_generator::prn_generator] The number of taps must be even");
    }
    
    /*vector<int> tapsvec;
    for (char c : taps) {
        tapsvec.push_back(static_cast<int>(c - '0'));
    }*/
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
    // Check if the scrambling block iterator reaches the end or is at the beginning
    if (this->scrm_bgn < this->prn_seq.end() && this->scrm_bgn > this->prn_seq.begin()) {
        // If it does not, keep the PRN sequence as it is
        // and return the next scrambling block
        string new_scrm_blk(this->scrm_bgn, this->scrm_bgn + 8);
        this->scrm_bgn += 8; // Advance the iterator to the next scrambling block
        return new_scrm_blk;
    }
    // The scrambling block iterator reaches the end, advance 
    // the PRN sequence by one bit

    // Get the vector of values at the tap positions
    string tapped = "";
    for (int t : this->prn_taps) {
        tapped += this->prn_seq[t];
    }

    // Compute the total XOR of the tapped values
    char newbit = '0';
    for (char c : tapped) {
        newbit = this->myxor(newbit, c);
    }

    // Prepend the resultant bit to the PRN sequence and
    // discard the last bit
    string new_prn = newbit + this->prn_seq.substr(0, this->prn_seq.length() - 1);
    this->prn_seq = new_prn;

    // Move the iterator to the beginning
    this->scrm_bgn = this->prn_seq.begin();
    // Attain the scrambling block
    string new_scrm_blk(this->scrm_bgn, this->scrm_bgn + 8);
    // Advance the iterator to the next scrambling block
    this->scrm_bgn += 8;
    return new_scrm_blk;
}

// private:
// vector<int> prn_generator::prn_taps;

// string prn_generator::prn_seq;

/*
The class initialization code that are common to
overloaded constructors
*/
void prn_generator::init(vector<size_t> taps) {
    if (!this->validTaps(taps)) {
        throw invalid_argument("Invail tap positions. The values must be distinct integers selected from the range [0, 127]");
    }

    this->prn_taps = taps; // Store the tap positions
    //this->prn_seq = string(8, '1'); // Intialize the PRN sequence
    this->scrm_bgn = this->prn_seq.begin(); // Init the scrambling block beginning iterator
}
    
/*
Validate the tap position values
*/
bool prn_generator::validTaps (const vector<size_t>& taps) {
    unordered_set<int> S; // For checking uniqueness
    auto goodValue = [](int d) -> bool {
        if (d >= 0 && d <= 127) {
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
Validate the encryption key
*/
bool prn_generator::validKey(const string key) {
    // Validate the key length
    size_t klen = key.length();
    if (klen % 2 != 0) { // Key length is odd
        return false;
    }
    
    int numBytes = klen / 2;
    if (numBytes < 1 || numBytes > 16) { // Key length out of range
        return false;
    }

    // Validate the hexadecimal characters
    HexDecMap HDM;
    for (char c : key) {
        if (HDM.Hex2Dec.find(c) == HDM.Hex2Dec.end()) { // Invalid hexadecimal character
            return false;
        }
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
Generate an encryption key
*/
string prn_generator::genKey() {
    // Determine the key byte-length, which is a random integer
    // drawn from the interval [1, 16]. Thereby the maximum key
    // bit-length is 128
    int keyLen = oneRandInt(1, 16);

    // Determine the number of taps
    int t_base = oneRandInt(1, keyLen * 4);
    int n_taps = 2 * t_base; // The number of taps must be even

    // Randomly place the taps over the binary key
    unordered_set<int> S_taps = randKFromN(1, keyLen * 8, n_taps);
    string binKey(keyLen * 8, '0'); // Init the binary key
    for (int p : S_taps) {
        binKey[p] = '1';
    }

    // Convert the binary key to the hex key
    string hexKey = "";
    for (auto it = binKey.begin(); it < binKey.end(); it += 4) {
        string bin4(it, it + 4);
        hexKey.push_back(fourBin2OneHex(bin4));
    }

    return hexKey;
}


/*
Draw a random integer from an interval
*/
static int oneRandInt(int l_b, int u_b) {
    random_device rd; // Get a random seed
    mt19937 gen(rd());
    uniform_int_distribution<> distr(l_b, u_b);
    int rand_int = distr(gen);
    return rand_int;
}


/*
Draw k random distinct numbers from an interval of length N
*/
static unordered_set<int> randKFromN(int l_b, int u_b, int k) {
    unordered_set<int> drawn;
    do {
        int rand_int = oneRandInt(l_b, u_b);
        if (drawn.find(rand_int) != drawn.end()) { // The number has been drawn already
            continue;
        }
        drawn.insert(rand_int);
    } while (drawn.size() <= k);

    return drawn;
}


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
