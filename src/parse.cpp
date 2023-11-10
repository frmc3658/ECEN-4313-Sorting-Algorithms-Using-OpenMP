#include "../headers/parse.h"

/* Long options for getopt_long */
static option longOptions[] = {
    /* name         has_arg             flag,       val */
    {"inputFile",   required_argument,  nullptr,    'i'},
    {"outputFile",  required_argument,  nullptr,    'o'},
    {"numThreads",  required_argument,  nullptr,    't'},
    {"algorithm",   required_argument,  nullptr,    'a'},
    {"name",        no_argument,        nullptr,    'n'},
    {"help",        no_argument,        nullptr,    'h'}
};


Parser::Parser(int argc, char* argv[])
{
    validateArgc(argc);
    parseArgs(argc, argv);
}


Parser::~Parser()
{
    
}


void Parser::parseInputFile(std::vector<int>*& storage)
{

}


void Parser::validateArgc(int argc)
{
    try
    {
        if(argc < 2)
        {
            throw std::runtime_error("ERROR: Not enough Arguments\n");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what()<< std::endl;
        exit(EXIT_FAILURE);
    }
}


void Parser::parseArgs(int argc, char* argv[])
{
    while(true)
    {
        int optIndex = 0;
        int option = getopt_long(argc, argv, "i:o:t:", longOptions, &optIndex);

        if(option == -1){ break; }

        switch(option)
        {
            case 'i':
                setInputPath((std::string)optarg);
                break;
            case 'o':
                setOutputPath((std::string)optarg);
                break;
            case 't':
                setNumThreads(std::stoi(optarg));
                break;
            case 'h':
                printHelpFile();
                exit(EXIT_SUCCESS);
                break;
            case 'n':
                printName();
                exit(EXIT_SUCCESS);
                break;
            case '?':
                try
                {
                    throw std::runtime_error("Error Unknown Option\n");
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    exit(EXIT_FAILURE);
                }
        }
    }
}


void Parser::setNumThreads(int n)
{   
    
    numThreads = n;
    std::cout << "Num Threads: " << numThreads << std::endl;
}


void Parser::setInputPath(std::string path)
{
    inputFilePath = path;
    std::cout << "Input File Path: " << inputFilePath << std::endl;
}


void Parser::setOutputPath(std::string path)
{
    outputFilePath = path;
    std::cout << "Output File Path: " << outputFilePath << std::endl;
}


void Parser::printName(void)
{
    std::cout << "Frank McDermott\n";
}


void Parser::printHelpFile(void)
{

}

