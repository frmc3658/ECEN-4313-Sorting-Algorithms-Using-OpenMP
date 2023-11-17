## Lab 3: OpenMP ##
### Frank McDermott ###

#### Ease of Implementation ####
Compared to pthreads, OpenMP is much easier to implement. OpenMP abstracts away the whole fork/join process, which is mostly a quality of life improvment over pthreads as it abstracts away the handling of threads and function pointers and allows the programmer to focus more on worksharing paradigms. Another positive with Openmp is not having to worry about synchronize-with or consisency models.

#### Performance ####
My lab1 and lab3 implementations are kind of an apples-to-oranges comparison (as far as design implementation is concerned), but the sorting algorithm code is the same. OpenMp is significantly slower (relatively speaking) than my pthread fork/join implementation of quicksort.

|---------------------------------------------------|
|               **pthread Quicksort**               |
|---------------------------------------------------|
| Num Threads   | Runtime (ns)  |   Runtime (s)     |
|---------------|---------------|-------------------|
| 1             |   14919148972 |       14.9        |
| 2             |   10758644067 |       10.7        |
| 3             |   8286764496  |       8.2         |
| 4             |   6806801207  |       6.8         |
| 5             |   5560071439  |       5.5         |
| 6             |   4774923970  |       4.7         |
| 7             |   4485420280  |       4.4         |
| 8             |   3758937187  |       3.7         |
| 9             |   3492135849  |       3.4         |
| 10            |   3167000720  |       3.1         |
|---------------------------------------------------|


|---------------------------------------------------|
|               **OpenMP Quicksort**                |
|---------------------------------------------------|
| Num Threads   | Runtime (ns)  |   Runtime (s)     |
|---------------|-------------- |-------------------|
| 1             |   32952835926 |       32.9        |
| 2             |   16717522474 |       16.7        |
| 3             |   11495286014 |       11.4        |
| 4             |   8725374179  |       8.7         |
| 5             |   6668353207  |       6.6         |
| 6             |   5904071100  |       5.9         |
| 7             |   4813296646  |       4.8         |
| 8             |   4223445802  |       4.2         |
| 9             |   4003656506  |       4.0         |
| 10            |   3325376828  |       3.3         |
|---------------------------------------------------|

I wanted to run perf on the code to see the difference in cache and branch prediction performance, but I'm unable to ssh into the 