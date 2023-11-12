#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

#include "global.h"

#define AUTHOR_NAME     "Frank McDermott\n"
#define HELP_FILE_PATH  "help/help.txt"
#define SHORT_OPTIONS   "i:o:t:"

class Parser
{
    private:
        std::string inputFilePath;
        std::string outputFilePath;
        int numThreads;

        // Validation and argument parsing
        void validateArgc(int argc);
        void parseArgs(int argc, char* argv[]);

        // Helper functions
        void setNumThreads(int n);
        void setInputPath(std::string path);
        void setOutputPath(std::string path);
        void printName(void);
        void printHelpFile(void);

    public:
        Parser(int argc, char* argv[]);
        ~Parser();

        void parseInputFile(std::vector<int>*& storage);
        void writeSortedValues(std::vector<int>*& sortedValues);

        // Member acccessor functions
        int getNumThreads(void){ return numThreads; }
        std::string getInputFilePath(void){ return inputFilePath; }
        std::string getOutputFilePath(void){ return outputFilePath; }
};

#endif /* PARSE_H */