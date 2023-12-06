
#ifndef _H_IO_INTERFACE
#define _H_IO_INTERFACE

#include "../../lib/CLI11.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace IOInterface {

/*
The struct that holds the input arguments
*/
struct MainArgs {
    bool encr_flag = false;
    bool decr_flag = false;
    bool not_seq = false;
    bool flush = false;
    string input_file = "";
    string output_file = "";
};


/*
Parse input arguments
*/
int parseArgs(int argc, char** argv, CLI::App& app, MainArgs& args);


/*
Read the text from the input file
*/
string readTxt(const string input_file);


/*
Write out the text to the output file
*/
bool writeTxt(const string& txt, const string output_file);


/*
Read in each char from a text file sequentially
*/
bool sequentialRead(ifstream& file, char& ch);


/*
Write out each char (not limited to ASCII) to a text file sequentially
*/
bool sequentialWrite(ofstream& file, char ch);
bool sequentialWrite(ofstream& file, string str);

}


#endif // _H_IO_INTERFACE