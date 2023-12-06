#include "utf8_prn.hpp"

namespace BEProd {

	SeqEndecrU8::SeqEndecrU8(
		const string infilename,
		const string outfilename,
		const bool endecrFlag,
		const string taps
	) {
		this->readfile = ifstream(infilename, ios::binary);
		this->writefile = ofstream(outfilename, ios::app);
		this->pgen = BinaryLayer::prn_generator(taps);
		this->direction = endecrFlag;
	}


	bool SeqEndecrU8::procOneStep() {
		string str_to_write;
		bool done;
		if (this->direction) { // Encryption
			done = this->encrOneByte(str_to_write);
		}
		else { // Decryption
			done = this->decryptOneBlk(str_to_write);
		}

		if (!done) {
			return false;
		}

		bool writeOK = IOInterface::sequentialWrite(this->writefile, str_to_write);
		if (!writeOK) {
			throw runtime_error("[SeqEndecrU8::procOneStep] Failed to write to the file");
		}

		return true;
	}


	bool SeqEndecrU8::encrOneByte(string& se_str) {
		// Read one byte from the unencrypted text
		char byteChar;
		bool readOK = IOInterface::sequentialRead(this->readfile, byteChar);
		if (!readOK) {
			return false;
		}

		// Encode the byte into a 2-digit hexadecimal string
		string hex2 = EncodingLayer::oneByteCharToHex(byteChar);

		// Some encrypting algos yet to be implemented in
		// the encoding layer

		// Convert each 2-digit hexadecimal string to an
		// eight-bit binary string
		if (hex2.length() != 2) {
			throw runtime_error("[encrOneByte] Invalid hexadecimal string. It must have length 4");
		}
		string bin8 = "";
		for (char h : hex2) {
			bin8 += BinaryLayer::OneHex2FourBin(h);
		}

		// Apply PRN scrambling in the binary layer
		string scrambledBinStr = BinaryLayer::applySramble(bin8, this->pgen);

		// Map scrambled binary string to space-enter symbols
		// Store the symbols in the input reference
		se_str = BinaryLayer::encrBin(scrambledBinStr);	
		return true;
	}


	bool SeqEndecrU8::decryptOneBlk(string& txt) {
		// Read one block from the encrypted file
		string blk;
		bool readOK = this->readOneBlk(blk);
		if (!readOK) {
			return false;
		}

		// Map the block of space-enter symbols to 
		// an 8-bit binary string
		string scrambledBinStr = BinaryLayer::encrTxt2bintxt(blk);

		// Perform PRN descrambling
		string binStr = BinaryLayer::applySramble(scrambledBinStr, this->pgen);

		// Convert the 8-bit descrambled binary
		// string to a 2-digit hexadecimal
		// string
		string first4(binStr.begin(), binStr.begin() + 4);
		string last4(binStr.end() - 4, binStr.end());
		auto bin4_2hex1 = [](string bin4) {
			char c = BinaryLayer::fourBin2OneHex(bin4);
			string str(1, c);
			return str;
		};
		string hex2 = bin4_2hex1(first4) + bin4_2hex1(last4);

		// Some decryption algos yet to be implemented
		// in the encoding layer

		// Convert the 2-digit hexadecimal string
		// to a 1-byte char
		char byteChar = EncodingLayer::twoHexToOneByteChar(hex2);

		// Construct a 1-char-long string from the
		// resultant char
		txt = string(1, byteChar);
		return true;
	}


	bool SeqEndecrU8::readOneBlk(string& blk) {
		string str;
		int i = 0;
		while (i < 8) {
			char oneChar;
			bool readOK = IOInterface::sequentialRead(this->readfile, oneChar);
			if (!readOK) {
				return false;
			}

			if (oneChar != '\n' && oneChar != ' ') {
				continue;
			}

			string onechar_str = string(1, oneChar);
			str += onechar_str;
			i++;
		}
		blk = str;
		return true;
	}


	void SeqEndecrU8::run() {
		bool running;
		do {
			running = this->procOneStep();
		} while (running);
		if (this->direction) {
			cout << "Encryption succeeded" << endl;
		}
		else {
			cout << "Decryption succeeded" << endl;
		}
	}


	void SeqEndecrU8::closeFiles() {
		if (this->readfile.is_open()) {
			this->readfile.close();
		}

		if (this->writefile.is_open()) {
			this->writefile.close();
		}
	}


	void SeqEndecrU8::flush(const string filename) {
		ofstream file(filename, ofstream::out | ofstream::trunc);
		if (!file.is_open()) {
			throw runtime_error("[SeqEndecr::flush] Failed to flush the file: " + filename);
		}
		file.close();
	}
} // namespace BEProd


using namespace BEProd;


int main(int argc, char** argv) {
	// Parse input arguments
	CLI::App app;
	IOInterface::MainArgs args;
	int parsed = IOInterface::parseArgs(argc, argv, app, args);
	if (parsed != 0) {
		throw invalid_argument("[main] Error in parsing input arguments");
	}

	// Predefined BINARY LAYER PRN code generator tap positions
	string taps = "0257";

	// Flush output file upon being requested
	if (args.flush) {
		SeqEndecrU8::flush(args.output_file);
	}

	if (args.encr_flag) { // Perform encryption
		SeqEndecrU8 encryptor(
			args.input_file,
			args.output_file,
			true,
			taps
		);
		encryptor.run();
		encryptor.closeFiles();
		return 0;
	}

	if (args.decr_flag) { // Perform decryption
		SeqEndecrU8 decryptor(
			args.input_file,
			args.output_file,
			false,
			taps
		);
		decryptor.run();
		decryptor.closeFiles();
		return 0;
	}
}