#include "../headers/mergesort.h"


MergeSort::MergeSort()
{
    DEBUG_PRINT("MergeSort Constructor called%s", "\n");
}


MergeSort::~MergeSort()
{
    if(values != nullptr)
    {
        delete values;
    }
}

void MergeSort::sort(void)
{
    DEBUG_PRINT("MergeSort: Sort called by thread%d\n", omp_get_thread_num());
}