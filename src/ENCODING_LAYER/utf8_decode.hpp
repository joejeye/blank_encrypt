#ifndef _H_UTF8_DECODE
#define _H_UTF8_DECODE

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

namespace EncodingLayer {

	char twoHexToOneByteChar(const string);

} // namespace EncodingLayer

#endif // !_H_UTF8_DECODE
