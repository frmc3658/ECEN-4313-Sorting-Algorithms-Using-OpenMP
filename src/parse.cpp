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
    delete sortObj;
}


void Parser::parseInputFile(std::vector<int>*& storage)
{
    storage = new std::vector<int>;
    std::ifstream file(inputFilePath);

    try
    {
        if(!file)
        {
            DEBUG_PRINT("Attempted to open input file at: %s\n", inputFilePath.c_str());
            throw std::runtime_error("ERROR: Input File Error\n");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    
    std::string line;

    while(std::getline(file, line))
    {
        storage->push_back(std::stoi(line));
    }

    file.close();
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
        algRequested = false;
        int optIndex = 0;
        int option = getopt_long(argc, argv, SHORT_OPTIONS, longOptions, &optIndex);

        if(option == -1){ break; }

        switch(option)
        {
            case 'a':
                setAlgorithm((std::string)optarg);
                break;
            case 'h':
                printHelpFile();
                exit(EXIT_SUCCESS);
                break;
            case 'i':
                setInputPath((std::string)optarg);
                break;
            case 'n':
                printName();
                exit(EXIT_SUCCESS);
                break;
            case 'o':
                setOutputPath((std::string)optarg);
                break;
            case 't':
                setNumThreads(std::stoi(optarg));
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

    if(algRequested == false)
    {
        setAlgorithm("quick");
    }

}


void Parser::setNumThreads(int n)
{   
    
    numThreads = n;
    DEBUG_PRINT("Set numThreads: %d\n", n);
}


void Parser::setInputPath(std::string path)
{
    inputFilePath = path;
    DEBUG_PRINT("Set input file path: %s\n", path.c_str());
}


void Parser::setOutputPath(std::string path)
{
    outputFilePath = path;
    DEBUG_PRINT("Set output file path: %s\n", path.c_str());
}


void Parser::setAlgorithm(std::string algRequest)
{
    algRequested = true;

    if(algRequest == "quick")
    {
        sortObj = new QuickSort();
    }
    else if(algRequest == "merge")
    {
        sortObj = new MergeSort();
    }
    else
    {
        sortObj = nullptr;
        DEBUG_PRINT("%s is not a valid algorithm\n", algRequest.c_str());
        exit(EXIT_FAILURE);
    }
}


void Parser::writeSortedValues(std::vector<int>*& sortedValues)
{
    std::ofstream outFile(outputFilePath);

    try
    {
        if(!outFile)
        {
            DEBUG_PRINT("Attempted to open output file at: %s", outputFilePath.c_str());
            throw std::runtime_error("ERROR: Error opening output file\n");
        }
        else
        {
            for(size_t i = 0; i < sortedValues->size(); i++)
            {
                outFile << (*sortedValues)[i] << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    
    outFile.close();
}


void Parser::printName(void)
{
    std::cout << AUTHOR_NAME;
}


void Parser::printHelpFile(void)
{
    std::ifstream file(HELP_FILE_PATH);

    try
    {
        if(!file)
        {
            DEBUG_PRINT("Attempted to open help file at: %s\n", HELP_FILE_PATH);
            throw std::runtime_error("ERROR: Error opening help file\n");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    
    std::string line;

    while(std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}

