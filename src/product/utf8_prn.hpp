#ifndef _H_UTF8_PRN
#define _H_UTF8_PRN

//#include <filesystem>
#include "../IO_INTERFACE/io_interface.hpp"
#include "../ENCODING_LAYER/utf8_encode.hpp"
#include "../ENCODING_LAYER/utf8_decode.hpp"
#include "../BINARY_LAYER/north_interface.hpp"
#include "../BINARY_LAYER/prn_scrambling.hpp"
#include "../BINARY_LAYER/south_interface.hpp"


using namespace std;
//namespace fs = filesystem;

// BEProd stands for Blank Encrypt Product
namespace BEProd {

	/*
	Perform sequential encryption/decryption for UTF-8 encoded text
	*/
	class SeqEndecrU8 {
	public:
		ifstream readfile;

		ofstream writefile;

		BinaryLayer::prn_generator pgen;// = BinaryLayer::prn_generator("0"); // Dummy instance

		/*
		True for encryption, false for decryption
		*/
		bool direction;

		/*
		Constructor
		*/
		SeqEndecrU8(
			const string infilename,
			const string outfilename,
			const bool endecrFlag,
			const string taps
		);

		/*
		Encrypt/decrypt one step.
		For encryption, one step processes one byte (could be a portion of a UTF-8 char).
		For decryption, one step decrypt a block of 8 space-enter symbols.
		*/
		bool procOneStep();

		/*
		Encrypt one byte. `se_str` is for storing output
		*/
		bool encrOneByte(string& se_str);

		/*
		Decrypt one block. A block consists of 8 consecutive space-enter symbols.
		`txt` is one byte of decrypted text, could be a portion of a UTF-8 encoded
		char.
		*/
		bool decryptOneBlk(string& txt);

		/*
		Read one block from the encrypted file. This member function is for
		decryption only
		*/
		bool readOneBlk(string& blk);

		/*
		Run the encryption/decryption sequentially all the way to the end
		*/
		void run();

		/*
		Close opened files
		*/
		void closeFiles();

		/*
		Flush the output file in preparation for writing new text
		*/
		static void flush(const string filename);
	}; // class SeqEndecrU8

	
	/*
	Create the encryption in the cach directory
	*/
	static bool createCachedkey(const string cachDir, const string hexKey);
} // namespace BEProd

#endif // !_H_UTF8_PRN
