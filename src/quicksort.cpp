#include "../headers/quicksort.h"


QuickSort::QuickSort()
{
    DEBUG_PRINT("QuickSort: Constructor Called %s", "\n");
    sortRanges.resize(omp_get_num_threads());
}


QuickSort::~QuickSort()
{
    if(values != nullptr)
    {
        delete values;
    }
}


void QuickSort::sort(void)
{
    int tid = omp_get_thread_num();

    DEBUG_PRINT("QuickSort: Sort Called by Thread%d\n", tid);
    Range range = getThreadSortRange(tid);
    DEBUG_PRINT("Thread%d: Range = [%d - %d]\n", tid, range.first, range.second);

    int start = range.first;
    int end = range.second;

    // Create an auxiliary stack
    std::vector<int> stack;

    // push initial values of start and end to stack
    stack.push_back(start);
    stack.push_back(end);

    // Keep popping from stack while it's not empty
    while (!stack.empty())
    {
        // Pop end and start
        end = stack.back();
        stack.pop_back();
        start = stack.back();
        stack.pop_back();

        // Set pivot element at its correct position
        // in the sorted array
        int pivot = partition(start, end);

        // If there are elements on the left side of pivot,
        // then push the left side to the stack
        if (pivot - 1 > start)
        {
            stack.push_back(start);
            stack.push_back(pivot - 1);
        }

        // If there are elements on the right side of pivot,
        // then push the right side to the stack
        if (pivot + 1 < end)
        {
            stack.push_back(pivot + 1);
            stack.push_back(end);
        }
    }

    #pragma omp barrier
    #pragma omp master
    {
        merge();
    }
}


Range QuickSort::getThreadSortRange(int threadID)
{
    int numValues = values->size();
    int numThreads = omp_get_num_threads();
    int numElements = numValues / numThreads;

    // Calculate starting point of range (inclusive)
    int startIndex = threadID * numElements;

    // Calculate endpoint of range (inclusive)
    int endIndex = (threadID == numThreads - 1) ? (numValues - 1) : (startIndex + numElements - 1);

    // Encapsulate both points as a range
    Range sortRange = std::make_pair(startIndex, endIndex);

    return sortRange;
}


int QuickSort::partition(int start, int end)
{
    int pivotValue = (*values)[end];
    int pivotIndex = (start - 1);

    for(int i = start; i <= end - 1; i++)
    {
        if((*values)[i] <= pivotValue)
        {
            pivotIndex++;
            std::swap((*values)[pivotIndex], (*values)[i]);
        }
    }
    std::swap((*values)[pivotIndex + 1], (*values)[end]);
    return (pivotIndex + 1);
}

void QuickSort::merge(void)
{
    int start = 0;
    int end = (int)(getValues()->size() - 1);

    // Create an auxiliary stack
    std::vector<int> stack;

    // push initial values of start and end to stack
    stack.push_back(start);
    stack.push_back(end);

    // Keep popping from stack while it's not empty
    while (!stack.empty())
    {
        // Pop end and start
        end = stack.back();
        stack.pop_back();
        start = stack.back();
        stack.pop_back();

        // Set pivot element at its correct position
        // in the sorted array
        int pivot = partition(start, end);

        // If there are elements on the left side of pivot,
        // then push the left side to the stack
        if (pivot - 1 > start)
        {
            stack.push_back(start);
            stack.push_back(pivot - 1);
        }

        // If there are elements on the right side of pivot,
        // then push the right side to the stack
        if (pivot + 1 < end)
        {
            stack.push_back(pivot + 1);
            stack.push_back(end);
        }
    }
}
