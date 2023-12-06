#ifndef _H_UTF8_ENCODE
#define _H_UTF8_ENCODE

#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace EncodingLayer {
	/*
	Convert one char (one byte, might be a portion of a UTF-8 
	code) to a 2-digit hexadeciaml string
	*/
	string oneByteCharToHex(const char c);

} // namespace EncodingLayer

#endif // !_H_UTF8_ENCODE
