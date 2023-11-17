#ifndef MERGESORT_H
#define MERGESORT_H

#include <algorithm>
#include <omp.h>

#include "sort.h"

typedef std::pair<int, int> Range;

class MergeSort : public Sort
{
    private:

    public:
        MergeSort();
        virtual ~MergeSort();

        void sort(void) override;
};

#endif /* MERGESORT_H */