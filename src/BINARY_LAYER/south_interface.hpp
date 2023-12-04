#ifndef _H_SOUTH_INTERFACE
#define _H_SOUTH_INTERFACE

#include <string>
#include <iostream>

using namespace std;

namespace BinaryLayer {

/*
Transform binary string to space-enter encrypted
text by following the mapping: 
    '0' -> ' '
    '1' -> '\n'
*/
string encrBin(const string& bintxt);

/*
Transform space-enter encrypted text to binary
string by following the mapping:
    ' ' -> '0'
    '\n' -> '1'
*/
string encrTxt2bintxt(const string& txt);

}

#endif // _H_SOUTH_INTERFACE