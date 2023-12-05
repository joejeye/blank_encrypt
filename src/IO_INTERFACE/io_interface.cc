#include "io_interface.hpp"


namespace IOInterface {

/*
Parse input arguments
*/
int parseArgs(int argc, char** argv, CLI::App& app, MainArgs& args) {
    // CLI::App app;

    bool encr_flag{false};
    app.add_flag("-e,--encrypt", encr_flag, "Perform encryption.");

    bool decr_flag{false};
    app.add_flag("-d,--decrypt", decr_flag, "Perform decryption.");

    string input_file{""};
    app.add_option("-i,--input", input_file, "Specify the input file name");

    string output_file{""};
    app.add_option("-o,--output", output_file, "Specify the output file name");

    bool not_seq{ false }; // Process sequentially
    app.add_flag("-n,--notsequential", not_seq, "Do not process sequentially");

    CLI11_PARSE(app, argc, argv);

    if (!encr_flag && !decr_flag) {
        throw invalid_argument("Please specify whether to encrypt or to decrypt.");
        // return -1;
    } else if (encr_flag && decr_flag) {
        throw invalid_argument("Cannot perform both encryption and decryption at the same time. Please specify either one of them.");
        // return -1;
    } else if (input_file.empty() || output_file.empty()) {
        throw invalid_argument("Input and output file names must not be empty.");
        // return -1;
    }

    // MainArgs args;
    args.encr_flag = encr_flag;
    args.decr_flag = decr_flag;
    args.not_seq = not_seq;
    args.input_file = input_file;
    args.output_file = output_file;

    return 0;
}


/*
Read the text from the input file
*/
string readTxt(const string input_file) {
    ifstream in_f(input_file);
    if (!in_f.is_open()) {
        throw runtime_error("Could not open file: " + input_file);
        return "";
    }

    stringstream buffer;
    buffer << in_f.rdbuf();
    string input_txt = buffer.str();

    in_f.close();
    
    return input_txt;
}


/*
Write out the text to the output file
*/
bool writeTxt(const string& txt, const string output_file) {
    ofstream out_f(output_file);
    if (!out_f.is_open()) {
        throw invalid_argument("Could not open file: " + output_file);
        return false;
    }
    out_f << txt;

    out_f.close();

    return true;
}

/*
Read in each ASCII char from a text file sequentially
*/
bool sequentialRead(ifstream& file, char& ch) {
    if (!file.is_open()) {
        throw invalid_argument("[sequentialRead] File is not open");
    }

    char readin;
    if (file.get(readin)) {
        ch = readin;
        return true;
    }
    else { // Reach the end of file
        return false;
    }
}


/*
Write out each char (not limited to ASCII) to a text file sequentially
*/
bool sequentialWrite(ofstream& file, char ch) {
    string str(1, ch);
    return sequentialWrite(file, str);
}

bool sequentialWrite(ofstream& file, string str) {
    if (!file.is_open()) {
        throw invalid_argument("[sequentialWrite] File is not open");
    }
    // Write the char (casted as a string) to the file without
    // prepending/appending a newline
    file << str;
    return true;
}


}