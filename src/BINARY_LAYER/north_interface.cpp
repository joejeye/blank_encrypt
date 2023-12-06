#include "north_interface.hpp"

namespace BinaryLayer {

	string dec2FourBin(int d) {
		if (d < 0 || d > 16) {
			throw invalid_argument("[dec2FourBin] The decimal integer must be within the range [0, 15]");
		}

		string str;
		do {
			str.insert(0, to_string(d % 2));
			d /= 2;
		} while (d > 0);
		stringstream ss;
		ss << setfill('0') << setw(4) << str;
		return ss.str();
	}


	string OneHex2FourBin(const char oneHex) {
		// Convert hex to dec
		HexDecMap hdm;
		if (hdm.Hex2Dec.find(oneHex) == hdm.Hex2Dec.end()) {
			throw invalid_argument("[OneHex2FourBin] Invalid hexadecimal digit");
		}
		int d = hdm.Hex2Dec[oneHex];

		// Convert dec to 4-bit bin
		string bin4 = dec2FourBin(d);
		return bin4;
	}


	int fourBin2dec(const string bin4) {
		if (bin4.length() != 4) {
			throw invalid_argument("[fourBin2dec] Invalid bin string format. It must has the length 4");
		}
		int d = 0;
		for (char b : bin4) {
			d = 2 * d + static_cast<int>(b - '0');
		}
		return d;
	}


	char fourBin2OneHex(const string bin4) {
		if (bin4.length() != 4) {
			throw invalid_argument("[fourBin2OneHex] Invalid bin string format. It must has the length 4");
		}
		// Convert a 4-bit string to decimal int
		int d = fourBin2dec(bin4);

		// Convert decimal int to hex char
		HexDecMap hdm;
		char oneHex = hdm.Dec2Hex[d];
		return oneHex;
	}

} // namespace BinaryLayer