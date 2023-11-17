#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>

#include "sort.h"

typedef std::pair<int, int> Range;

class QuickSort : public Sort
{
    private:
        std::vector<Range> sortRanges;

        Range getThreadSortRange(int threadID);
        int partition(int start, int end);
        void merge(void);

    public:
        QuickSort();
        virtual ~QuickSort();

        // Virtual wrapper
        void sort(void) override;
};

#endif /* QUICKSORT_H */