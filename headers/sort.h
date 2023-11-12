#ifndef SORT_H
#define SORT_H

class Sort
{
    protected:

    public:
        virtual ~Sort(){}

        // Pure virtual function to make
        // abstract base class
        virtual void sort(void) = 0;
};

#endif /* SORT_H */