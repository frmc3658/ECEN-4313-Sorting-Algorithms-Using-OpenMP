#include "../headers/timer.h"


Timer::Timer()
{
    startTime.tv_nsec   = 0;
    startTime.tv_sec    = 0;
    endTime.tv_nsec     = 0;
    endTime.tv_sec      = 0;
}


Timer::~Timer()
{

}


void Timer::calculateRuntime(void)
{
    epochNs = (endTime.tv_sec - startTime.tv_sec) * 1000000000;
    epochNs += (endTime.tv_nsec - startTime.tv_nsec);

    epochSec = static_cast<double>(epochNs) / 1000000000.0;
}


void Timer::printRuntime(void)
{
    // Calculate runtime
    calculateRuntime();

    // Print runtime
    printf("Printing Runtime:\n");
    printf("Runtime: %llu ns\n", getRuntimeNS());
    printf("Runtime: %llu sec\n", getRuntimeSec());
}