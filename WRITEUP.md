## Lab 3: OpenMP - Frank McDermott ##

#### Ease of Implementation ####
Compared to pthreads, OpenMP is much easier to implement. OpenMP abstracts away the whole fork/join process, which is mostly a quality of life improvment over pthreads as it abstracts away the handling of threads and function pointers and allows the programmer to focus more on worksharing paradigms. Another positive with Openmp is not having to worry about synchronize-with or consisency models.

#### Performance ####
My lab1 and lab3 implementations are kind of an apples-to-oranges comparison (as far as design implementation is concerned), but the sorting algorithm code is the same. OpenMp is significantly slower (relatively speaking) than my pthread fork/join implementation of quicksort.

**pthread Quicksort**

| Num Threads   | Runtime (ns)  |   Runtime (s)     | L1 cache miss (%)| Branch Pred Miss Rate (%)| Page Fault Count (#)|
|---------------|---------------|-------------------|------------------|--------------------------|---------------------|
| 1             |   14919148972 |       14.9        |       0.384 %    |        0.02%             |         948         |
| 2             |   10758644067 |       10.7        |       0.472 %    |        0.03%             |         952         |
| 3             |   8286764496  |       8.2         |       0.690 %    |        0.04%             |         954         |
| 4             |   6806801207  |       6.8         |       0.719 %    |        0.05%             |         959         |
| 5             |   5560071439  |       5.5         |       0.991 %    |        0.07%             |         960         |
| 6             |   4774923970  |       4.7         |       1.227 %    |        0.08%             |         964         |
| 7             |   4485420280  |       4.4         |       1.139 %    |        0.09%             |         967         |
| 8             |   3758937187  |       3.7         |       1.319 %    |        0.10%             |         967         |
| 9             |   3492135849  |       3.4         |       1.600 %    |        0.11%             |         975         |
| 10            |   3167000720  |       3.1         |       1.608 %    |        0.12%             |         979         |




**OpenMP Quicksort**

| Num Threads   | Runtime (ns)  |   Runtime (s)     | L1 cache miss (%)| Branch Pred Miss Rate (%)| Page Fault Count (#)|
|---------------|-------------- |-------------------|------------------|--------------------------|---------------------|
| 1             |   32952835926 |       32.9        |       0.214 %    |        0.01%             |         1,257       |
| 2             |   16717522474 |       16.7        |       0.328 %    |        0.02%             |         1,259       |
| 3             |   11495286014 |       11.4        |       0.496 %    |        0.03%             |         1,264       |
| 4             |   8725374179  |       8.7         |       0.648 %    |        0.04%             |         1,265       |
| 5             |   6668353207  |       6.6         |       0.802 %    |        0.06%             |         1,268       |
| 6             |   5904071100  |       5.9         |       0.851 %    |        0.06%             |         1,269       |
| 7             |   4813296646  |       4.8         |       0.980 %    |        0.07%             |         1,274       |
| 8             |   4223445802  |       4.2         |       1.122 %    |        0.08%             |         1,280       |
| 9             |   4003656506  |       4.0         |       1.261 %    |        0.09%             |         1,281       |
| 10            |   3325376828  |       3.3         |       1.283 %    |        0.11%             |         1,283       |


Having done some `perf` analysis on both sets of code:
`pthreads` is less efficient in terms of L1 cache and branch prediction hit rate, while being approximately 25% more efficient in terms of page fault count.

While the design of the code if vastly different for this lab (OOP vs proceedural), the quicksort algorithm is largely the same.


#### Parallelization Strategy ####
My strategy for parallelization is to implement fork/join parallelism in a way that is essentially analogous to how i implemented `pthread` fork/join parallelism for lab1. I think the most efficient strategy would be to use `#pragma omp for schedule(guided)` in order to implement a more efficient work sharing paradigm to divide up the `values` vector rather than a static range. I use a pair of `pragma omp master` sections to start/stop the timer. Within the `sort()` function, I use a `#pragma omp barrier` at the end of the quicksort algorithm to synchronize all of he threads before using a `#pragma omp master` section in order to perform a `merg()`. This is probably the least efficient merge strategy possible, but I couldn't figure out how to use a `reduction` to merge each thread's sort "chunk". I'm not sure if a reduction would work here, since it's not a primitive datatype but rather a container, but if it's possible I would think a `reduction` would be the most efficient method to merge.


#### Code Organization #####
My code is written in a more OOP fashion. I created an abstract-base class (`Sort`) and a pair of derived classes (`QuickSort` and `MergeSort`) which override the `Sort::sort()` function. This allows me to leverage a pointer to the base `Sort` class in order to make the code more general and reduce complexity (in terms of branching). I like this design as it provides a single, consistent, interface. Ideally, I would abstract away the parallelization from the main driver code; however this is more analagous to the lab1 `pthread` code. The OpenMP parallelization represent the `threadMain()` function as it's written now. If I had some more time, I'd abstract that away completely such that after initializtion of `Sort*`, the driver code would simply call `sort()`.

I also wrote a `Parse` class which is used to, as the name implies, parse the command line arguments.

#### Files Submitted ####
- `main.cpp`: the main driver code in which the argument parsing, object initialization, fork/join parallelization, and writing to file occurs.
- `mergesort.cpp/.h`: Derived MergeSort class translation unit. Not fully implemented skeleton code for mergesort.
- `quicksort.cpp/.h`: Derived QuickSort class translation unit. Implements the quicksort functionality
- `timer.cpp/.h`: Timer class translation unit. Ecapsulates timer functionality.
- `parse.cpp/.h`: Parse class tranlation unit. Parses commandline arguments.
- `global.h`: Provides a DEBUG_PRINT macro function which can be included in other header files in order to implement debug printing. I made this macro function in order to enable/disable debug prints at compile-time with `$ make DEBUG=1` or `$ make` respectively. When the debug flag is not included at compile-time (`$ make`) the DEBUG_PRINT macro is defined as an empty do-while loop which get optimized out completely.


#### Extant Bugs ####
There aren't any extant bugs that I've come across.