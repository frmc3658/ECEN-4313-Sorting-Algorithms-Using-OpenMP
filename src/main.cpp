#include "../headers/main.h"

int main(int argc, char* argv[])
{
    Sort* sortObj;

    // Parse command line arguments
    Parser parse(argc, argv);

    // Parse the input file
    std::vector<int>* valuesToSort;
    parse.parseInputFile(valuesToSort);

    // Set the number of theads
    int numThreads = parse.getNumThreads();
    omp_set_num_threads(numThreads);

    // Initialize timer
    Timer timer;


    #pragma omp parallel default(shared) private(timer)
    {
        // All threads get their own threadID
        int tid = omp_get_thread_num();
        DEBUG_PRINT("Thread %d: in parallel section\n", tid);

        // Have the master thread start the timer
        #pragma omp master
        {
            DEBUG_PRINT("Thread %d: Starting timer\n", tid);
            timer.setStartTime();
        }

        // omp master doesn't have an implicit barrier
        // Adding one here for synchronization
        #pragma omp barrier


        // Have the master thread stop the timer
        #pragma omp master
        {
            DEBUG_PRINT("Thread %d: Stopping timer\n", tid);
            timer.setEndTime();
        }
    }



    return 0;
}