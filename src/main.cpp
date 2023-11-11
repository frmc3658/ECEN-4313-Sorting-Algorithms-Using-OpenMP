#include "../headers/main.h"

int main(int argc, char* argv[])
{
    // Parse command line arguments
    Parser parse(argc, argv);

    // Parse the input file
    std::vector<int>* valuesToSort;
    parse.parseInputFile(valuesToSort);

    // Set the number of theads
    int numThreads = parse.getNumThreads();
    omp_set_num_threads(numThreads);

    #pragma omp parallel default(shared)
    {
        // All threads get their own threadID
        int tid = omp_get_thread_num();
        DEBUG_PRINT("Thread %d: in parallel section\n", tid);

        // Master thread performs this section
        #pragma omp master
        {
           DEBUG_PRINT("Thread %d: In master section\n", tid);
        }
        
        DEBUG_PRINT("Thread %d: Passed Master barrier\n", tid);
    }

    

    return 0;
}