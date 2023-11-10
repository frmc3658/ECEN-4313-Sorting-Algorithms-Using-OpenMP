#include "../headers/main.h"

int main(int argc, char* argv[])
{
    // Parse command line arguments
    Parser parse(argc, argv);

    // Parse the input file
    std::vector<int>* valuesToSort;
    parse.parseInputFile(valuesToSort);

    // Set the number of theads
    int tid;
    int numThreads = parse.getNumThreads();
    omp_set_num_threads(numThreads);

    #pragma omp parallel default(shared) private(tid)
    {
        // Get thread ID
        tid = omp_get_thread_num();

        
    }



    return 0;
}