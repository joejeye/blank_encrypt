
#include "south_interface.hpp"

namespace BinaryLayer {

/*
Transform binary string to space-enter encrypted
text by following the mapping: 
    '0' -> ' '
    '1' -> '\n'
*/
string encrBin(const string& bintxt) {
    string encrd = "";
    auto bin2SE = [](char bindig) -> string {
        return bindig == '0' ? " " : "\n";
    };

    for (char bindig : bintxt) {
        encrd += bin2SE(bindig);
    }
    return encrd;
}


/*
Transform space-enter encrypted text to binary
string by following the mapping:
    ' ' -> '0'
    '\n' -> '1'
*/
string encrTxt2bintxt(const string& txt) {
    if (txt.length() % 8 != 0) {
        throw invalid_argument("Wrong encrypted text format");
        return "";
    }

    string bintxt = "";
    for (char c : txt) {
        if (c == ' ') {
            bintxt += '0';
        } else if (c == '\n') {
            bintxt += '1';
        } else {
            continue;
        }
    }
    return bintxt;
}

} // namespace BinaryLayer