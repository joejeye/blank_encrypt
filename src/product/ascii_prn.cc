#include "../ENCODING_LAYER/ascii_endec.hpp"
#include "../BINARY_LAYER/prn_scrambling.hpp"
#include "../BINARY_LAYER/south_interface.hpp"
#include "../IO_INTERFACE/io_interface.hpp"
#include <fstream>
#include <sstream>

using namespace std;


/*
Perform encryption
*/
string encrypt(const string& txt, const string taps) {
    // Encode characters to ascii values
    string binStr = EncodingLayer::txt2bintxt(txt);

    // Create PRN code generator
    BinaryLayer::prn_generator pgen(taps);

    // Perform scrambling using PRN code
    string scrambledBinStr = BinaryLayer::applySramble(binStr, pgen);

    // Translate binary string to space-enter string
    string se_str = BinaryLayer::encrBin(scrambledBinStr);

    return se_str;
}


/*
Perform decryption
*/
string decrypt(const string& se_str, const string taps) {
    // Translate space-enter string to binary string
    string scrambledBinStr = BinaryLayer::encrTxt2bintxt(se_str);
    
    // Create PRN code generator
    BinaryLayer::prn_generator pgen(taps);

    // Perform descrambling using PRN code
    string binStr = BinaryLayer::applySramble(scrambledBinStr, pgen);

    // Decoding ascii binary string to characters
    string txt = EncodingLayer::binStr2Txt(binStr);

    return txt;
}


int main(int argc, char** argv) {
    // Parse input arguments
    CLI::App app;
    IOInterface::MainArgs args;
    int parsed = IOInterface::parseArgs(argc, argv, app, args);

    // Predefined BINARY LAYER PRN code generator tap positions
    string taps = "0257";

    if (args.encr_flag) { // Perform encryption
        string txt = IOInterface::readTxt(args.input_file);
        string se_str = encrypt(txt, taps);
        bool done = IOInterface::writeTxt(se_str, args.output_file);
        if (done) {
            cout << "Encryption succeeded" << endl;
        } else {
            cout << "Encryption failed" << endl;
        }
        return 0;
    }

    if (args.decr_flag) { // Perform decryption
        string encrdtxt = IOInterface::readTxt(args.input_file);
        string txt = decrypt(encrdtxt, taps);
        bool done = IOInterface::writeTxt(txt, args.output_file);
        if (done) {
            cout << "Decryption succeeded" << endl;
        } else {
            cout << "Decryption failed" << endl;
        }
        return 0;
    }

return 0;}