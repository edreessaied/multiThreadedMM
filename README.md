# Welcome to My MultiThreaded Matrix Multiplication Program!
This program uses a multi-threaded algorithm to execute
matrix multiplication of potentially large matrices 
(~ 1000 x 1000) in just a matter of seconds!

## How To Build and Run The Program
Download the `MultiThreadMM` project onto your machine. Move 
the project into a folder of your choosing. You may
open the project in an IDE/Text Editor that can compile 
C code or choose to build/run the code from the terminal, so long 
as you make sure that you have a C compiler installed 
on your machine (clang, gcc, etc.). For context, I've 
compiled the code using clang on VSCode. 

The project contains two directories:

`/MultiThreadMM/matrices/`

`/MultiThreadMM/src/`

The `/MultiThreadMM/matrices/` directory contains the text files
where the left, right, and product matrices will be read from and
written to.

The `/MultiThreadMM/src/` directory is where all the code lives.
Once you've downloaded and moved the project into a 
comfortable environment of your choosing, you can 
open a terminal and `cd` into this directory. In this directory, 
I've also written a `Makefile`. In order to compile and run the program, 
run these commands in the terminal in the current directory:

`make`

`./mmProgram`

The first command will generate an executable file
titled `mmProgram`. `./mmProgram` will then run this
executable. If you receive an issue when running `make` that
complains about a missing compiler, open the `Makefile` and
change the `CC` variable on line 3 to your C compliler. By default,
I have it assigned to `clang`.

## How To Interact With The Program
The file `mmProgram.c` is the main driver of the program.
When the program begins, it will ask you to input the
dimensions of the matrices that you want to multiply.
It will first ask you for the number of rows of the left matrix,
followed by the number of columns of the left matrix. The number
of rows of the right matrix will be automatically set to the 
number of columns that you assigned to the left matrix. Therefore,
I'll finally ask you to input the number of columns for the right matrix.
After providing me this information, I will generate your left and right
matrices using random values ranging from 0 to 9 and write the matrices directly
to files `/MultiThreadMM/matrices/matrixA.txt` and 
`/MultiThreadMM/matrices/matrixB.txt`, where the first file corresponds to
the left matrix and the second corresponds to the right matrix. The matrices
will be written with appropriate formatting, following the natural representation
of matrices except without the brackets. After writing both to their respective files,
I will load the matrices into memory by stor ingthem into two 2-dimensional arrays
allocated on the heap.

## How I've Executed The MultiThreaded Matrix Multiplication
I've used the `pthread` library to implement multithreading functionality as 
well as synchronization. The main program thread will first allocate appropriate 
space for the product matrix on the heap and then create threads to fill in 
this matrix using `pthread_create()`. The main thread will wait for all the threads
to complete their operations using `pthread_join()`. After all of the threads have
completed their assigned tasks, the main thread will finally write the product matrix
to `/MultiThreadMM/matrices/matrixC.txt` and complete.

### Thread Assignment and Thread Count
I've considered various ways to assign threads to specific sections of the matrix
multiplication operation, and I finally decided to assign each thread the task
of computing a specific row of the resulting matrix. Since my input matrices can be
potentially large and considering the overhead of multithreading, I've set my program 
to create a maximum of 500 threads. However, if the resulting matrices has fewer rows 
than 500, then I'll only create as many threads as there are rows. If there are more 
rows than the number of threads that I can create, threads will be assigned multiple 
rows over the coarse of the matrix multiplication. After a given thread completes its 
assigned row, it will check if there's any unassigned rows left and assign itself 
appropriately. A thread will only terminate once it finds that there no more rows 
left to compute.

### Synchronization
As I create threads to assign to unassigned rows, I will also be 
keeping track of the number of unassigned rows still left to compute. In order to 
synchronize access to the state of the number of unassigned rows across all threads, 
I initialized and required threads to acquire a global mutex lock, called `cRowNumberLock`. 
Since the computation of a given row of the product matrix is independent of the 
computation of other rows, I did not need to synchronze any of the specific row computations. When 
a thread is created, it will need to acquire the `cRowNumberLock` and update the number
of unassigned rows still remaining. Afterwards, it can quickly release the lock and
proceed to computing its assigned row. 

### Time Logging
To keep track of how long it takes my program to complete, I've tracked time stamps right before I create/assign threads and directly after joining on all the threads. Using the `time` library, I calculated the number of seconds that had passed in the process and recorded it in the output, although this time log seems a little higher than the time you'd record if you manually timed the 
program executation.

### Error Handling 
I've tried my best to account for all potential issues throughout my program by checking 
the return value of each of my function calls. If a particular function returns a value indicating
that it failed in its execution, I will alert you in the program output and end the program. These
functions include operations for memory allocations, opening/reading/writing a file, 
initializing/locking/unlocking the global mutex lock, creating/joining threads, etc. 
