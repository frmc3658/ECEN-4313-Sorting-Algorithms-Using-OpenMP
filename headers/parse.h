#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

#include "global.h"
#include "mergesort.h"
#include "quicksort.h"

#define AUTHOR_NAME     "Frank McDermott\n"
#define HELP_FILE_PATH  "help/help.txt"
#define SHORT_OPTIONS   "i:o:t:"

class Parser
{
    private:
        Sort* sortObj;
        std::string inputFilePath;
        std::string outputFilePath;
        int numThreads;
        bool algRequested;

        // Validation and argument parsing
        void validateArgc(int argc);
        void parseArgs(int argc, char* argv[]);

        // Helper functions
        void setNumThreads(int n);
        void setInputPath(std::string path);
        void setOutputPath(std::string path);
        void setAlgorithm(std::string algRequest);
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
        Sort* getSortObj(void){ return sortObj; }
};

#endif /* PARSE_H */