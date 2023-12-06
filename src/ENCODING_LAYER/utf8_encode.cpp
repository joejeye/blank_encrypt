#include "utf8_encode.hpp"

namespace EncodingLayer {

	string oneByteCharToHex(const char c) {
		string byteHex;
		stringstream hexStm;
		hexStm << hex << uppercase << setfill('0') << setw(2)
			<< static_cast<unsigned int>(static_cast<unsigned char>(c));
		byteHex = hexStm.str();
		return byteHex;
	}

} // namespace EncodingLayer