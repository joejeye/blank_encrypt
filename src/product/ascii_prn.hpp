#ifndef _H_ASCII_PRN
#define _H_ASCII_PRN

#include "../ENCODING_LAYER/ascii_endec.hpp"
#include "../BINARY_LAYER/prn_scrambling.hpp"
#include "../BINARY_LAYER/south_interface.hpp"
#include "../IO_INTERFACE/io_interface.hpp"
#include <fstream>
#include <sstream>

using namespace std;

// BEProd stands for Blank Encrypt Product
namespace BEProd {
	
	string encrypt(const string& txt, const string taps);

	string decrypt(const string& se_str, const string taps);

	/*
	Perform sequential encryption/decryption
	*/
	class SeqEndecr {
	public:
		ifstream readfile;

		ofstream writefile;

		BinaryLayer::prn_generator pgen = BinaryLayer::prn_generator("0"); // Dummy instance

		/*
		True for encryption, false for decryption
		*/
		bool direction;

		SeqEndecr(
			const string infilename, 
			const string outfilename, 
			const bool endecrFlag,
			const string taps
		);

		/*
		Process one char: read in the char and encrypt it and then wirte it out to the output file
		*/
		bool procOneChar();

		/*
		Encrypt one character
		*/
		bool encrOneChar(string& se_str);


		/*
		Decrypt one charactor
		*/
		bool decrOneChar(string&);

		/*
		Read in one character and cast it to a string
		*/
		bool readOneChar(string& txt);

		/*
		Run the object for encryption/decryption
		*/
		void run();
	};

} // namespace BEProd


#endif // !_H_ASCII_PRN


