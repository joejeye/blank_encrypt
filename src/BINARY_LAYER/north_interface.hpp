#ifndef _H_NORTH_INTERFACE
#define _H_NORTH_INTERFACE

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

namespace BinaryLayer {

	struct HexDecMap
	{
		unordered_map<char, int> Hex2Dec;
		unordered_map<int, char> Dec2Hex;

		HexDecMap() {
			vector<int> decvec = { 10, 11, 12, 13, 14, 15 };
			string hexdigit = "ABCDEF";
			for (int i = 0; i < 6; i++) {
				Hex2Dec[hexdigit[i]] = decvec[i];
				Dec2Hex[decvec[i]] = hexdigit[i];
			}
			for (int i = 0; i < 10; i++) {
				Hex2Dec[static_cast<char>(i + '0')] = i;
				Dec2Hex[i] = static_cast<char>(i + '0');
			}
		}
	};


	/*
	Convert decimal int to four binary digits
	*/
	string dec2FourBin(int);

	/*
	Convert one hexadecimal digit to four binary digits
	*/
	string OneHex2FourBin(const char);

	/*
	Convert 4-bit binary string to decimal int
	*/
	int fourBin2dec(const string);

	/*
	Convert a 4-bit binary string to one hexadecimal character
	*/
	char fourBin2OneHex(const string);

} // namespace BinaryLayer

#endif // !_H_NORTH_INTERFACE
