#ifndef GLOBAL_H
#define GLOBAL_H

// #define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(msg, var)   \
    {                               \
        printf(msg, var);           \
    }
#else
    #define DEBUG_PRINT(msg, var) do{}while(0)
#endif

#endif /* GLOBAL_H */