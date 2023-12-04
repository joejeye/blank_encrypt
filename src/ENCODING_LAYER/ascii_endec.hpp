/*
Perform ASCII encoding and decoding

Function for encoding:
    string txt2bintxt(const string& txt);
Function for decoding:
    string binStr2Txt(const string& binStr);

*/

#ifndef _H_ASCII_ENDEC
#define _H_ASCII_ENDEC

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace EncodingLayer {
string txt2bintxt(const string& txt);
string binStr2Txt(const string& binStr);
} // namespace EncodingLayer

#endif // _H_ASCII_ENDEC