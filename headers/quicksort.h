#ifndef QUICKSORT_H
#define QUICKSORT_H1

#include <algorithm>

#include "sort.h"

typedef std::pair<int, int> Range;

class QuickSort : public Sort
{
    private:


    public:
        QuickSort();
        virtual ~QuickSort();

        // Virtual wrapper
        void sort(void) override;

        
};

#endif /* QUICKSORT_H */