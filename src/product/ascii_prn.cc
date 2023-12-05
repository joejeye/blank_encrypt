#include "ascii_prn.hpp"

namespace BEProd {

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

SeqEndecr::SeqEndecr(
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


bool SeqEndecr::readOneChar(string& txt) {
    char ch;
    bool reading = IOInterface::sequentialRead(this->readfile, ch);
    if (!reading) {
        return false;
    }
    txt = string(1, ch);
    return true;
}


bool SeqEndecr::read8Chars(string& txt) {
    string str = "";
    for (int i = 0; i < 8; i++) {
        string onechar_str;
        bool readOK = this->readOneChar(onechar_str);
        if (!readOK) {
            return false;
        }

        str += onechar_str;
    }
    txt = str;
    return true;
}


bool SeqEndecr::encrOneChar(string& se_str) {
    string txt;
    bool readOK = this->readOneChar(txt);
    if (!readOK) {
        return false;
    }
    string binStr = EncodingLayer::txt2bintxt(txt);
    string scrambledBinStr = BinaryLayer::applySramble(binStr, this->pgen);
    se_str = BinaryLayer::encrBin(scrambledBinStr);
    return true;
}


bool SeqEndecr::decrOneChar(string& txt) {
    string se_str;
    bool readOK = this->read8Chars(se_str);
    if (!readOK) {
        return false;
    }
    string scrambledBinStr = BinaryLayer::encrTxt2bintxt(se_str);
    string binStr = BinaryLayer::applySramble(scrambledBinStr, this->pgen);
    txt = EncodingLayer::binStr2Txt(binStr);
    return true;
}


bool SeqEndecr::procOneStep() {
    string str_to_write;
    bool done;
    if (this->direction) {
        // Encrypt one character
        done = this->encrOneChar(str_to_write);
    }
    else {
        // Decrypt one character (read in 8 char's from
        // the encrypted text, write out 1 char)
        done = this->decrOneChar(str_to_write);
    }

    if (!done) {
        return false;
    }
    
    bool charDone = IOInterface::sequentialWrite(this->writefile, str_to_write);
    if (!charDone) {
        throw runtime_error("[SeqEndecr::procOneChar] Failed processing one of the char's");
    }

    return true;
}


void SeqEndecr::run() {
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

    if (args.encr_flag) { // Perform encryption
        if (args.not_seq) {
            string txt = IOInterface::readTxt(args.input_file);
            string se_str = encrypt(txt, taps);
            bool done = IOInterface::writeTxt(se_str, args.output_file);
            if (done) {
                cout << "Encryption succeeded" << endl;
            }
            else {
                cout << "Encryption failed" << endl;
            }
        }
        else {
            SeqEndecr encryptor(
                args.input_file,
                args.output_file,
                true,
                taps
            );
            encryptor.run();
        }
        return 0;
    }

    if (args.decr_flag) { // Perform decryption
        if (args.not_seq) {
            string encrdtxt = IOInterface::readTxt(args.input_file);
            string txt = decrypt(encrdtxt, taps);
            bool done = IOInterface::writeTxt(txt, args.output_file);
            if (done) {
                cout << "Decryption succeeded" << endl;
            }
            else {
                cout << "Decryption failed" << endl;
            }
        }
        else {
            SeqEndecr decryptor(
                args.input_file,
                args.output_file,
                false,
                taps
            );
            decryptor.run();
        }
        return 0;
    }

return 0;}