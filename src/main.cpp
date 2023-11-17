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

    // Set the sort vector
    Sort* sorter = parse.getSortObj();
    sorter->setValues(valuesToSort);

    #pragma omp parallel default(shared) shared(sorter)
    {
        #ifdef DEBUG
        // All threads get their own threadID
        int tid = omp_get_thread_num();
        #endif

        // All threads get their own timer object
        // but only master uses it
        Timer timer;

        // Have the master thread start the timer
        #pragma omp master
        {   
            DEBUG_PRINT("Thread %d: Starting timer\n", tid);
            timer.setStartTime();
        }

        // omp master doesn't have an implicit barrier
        // Adding one here for synchronization
        #pragma omp barrier

        // Call sorting algorithm
        sorter->sort();

        // Synchronization barrier post-sorting
        #pragma omp barrier

        // Have the master thread stop the timer
        #pragma omp master
        {
            DEBUG_PRINT("Thread %d: Stopping timer\n", tid);
            timer.setEndTime();

            // Calculate and print timing
            timer.calculateRuntime();
            timer.printRuntime();
        }

        #pragma omp barrier
    }
    
    // Write the values to the output file
    valuesToSort = sorter->getValues();
    parse.writeSortedValues(valuesToSort);

    return 0;
}