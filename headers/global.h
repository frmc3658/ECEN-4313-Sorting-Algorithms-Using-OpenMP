#ifndef GLOBAL_H
#define GLOBAL_H

// Make with DEBUG=1 to compile with DEBUG defined
// $ make DEBUG=1
#ifdef DEBUG
    #define DEBUG_PRINT(msg, var)   \
    {                               \
        printf(msg, var);           \
    }
#else
    #define DEBUG_PRINT(msg, var) do{}while(0)
#endif

#endif /* GLOBAL_H */