#ifndef SORT_H
#define SORT_H

#include <omp.h>
#include <vector>

#include "global.h"

class Sort
{
    protected:
        std::vector<int>* values = nullptr;

    public:
        virtual ~Sort(){}

        // Pure virtual function to make abstract base class
        virtual void sort(void) = 0;

        // Accessor functions
        inline std::vector<int>* getValues(void) const { return values; }
        inline size_t getSize(void) const { return values->size(); }

        // Modifier functions
        inline void setValues(std::vector<int>*& vect){ values = new std::vector<int>(*vect); }
};

#endif /* SORT_H */