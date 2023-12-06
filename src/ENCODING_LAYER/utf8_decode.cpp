#include "utf8_decode.hpp"

namespace EncodingLayer {

	char twoHexToOneByteChar(const string HexStr) {
		if (HexStr.length() != 2) {
			throw invalid_argument("[twoHexToOneByteStr] Invalid hexadecimal format. The input must be a 2-digit hexadecimal string");
		}

		int oneByte;
		stringstream ss;
		ss << hex << HexStr;
		ss >> oneByte;
		char oneByteChar = static_cast<char>(oneByte);
		return oneByteChar;
	}

} // namespace EncodingLayer