#include "../headers/main.h"

int main(int argc, char* argv[])
{
    // Parse command line arguments
    Parser parse(argc, argv);

    // Parse the input file
    std::vector<int>* valuesToSort;
    parse.parseInputFile(valuesToSort);

    


    return 0;
}