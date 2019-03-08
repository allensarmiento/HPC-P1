# HPC-P1

### CPSC 479 - Project 1
#### Ring Election Project

### Group Members:
- Andrew Lopez (alopez8969@csu.fullerton.edu)
- Allen Sarmiento (allensarmiento@csu.fullerton.edu)
- Ryan Shim (rcshim@csu.fullerton.edu)

### Description
This ring communication example will send two values through several processes until
they get back to the first process of rank 0. Each process generates a random value that
can either be even or odd. The program keeps track of "president" and "vice" values
which are the largest even value and the largest odd value respectively. The program
compares both values at each rank and swaps one if it is greater than the current
president or vice. The last two values received back to process 0  will be the
greatest odd and even values from all of the processes. 

### Pseudocode:
    /* This program sends the maximum odd/even value in a ring-like fashion.
     * Each rank receives two values and depending on whether or not the RNG
     * token is odd or even, the process sends it's values to the next process.
     * This repeats for every non-zero rank until we get back to rank 0.
     * Constraints: The value must be from 10-100.
     *              The number of ranks will be from 6-20.
     */

    // Initializtion
    Create process with N ranks
    number = new Random Number
    number = '1' + rank + number

    // Passing values between ranks
    if rank == 0:
        if is max odd:
            send value to next rank
        else:
            send previous rank value
        if is max even:
            send value to next rank
        else:
            send previous rank value
    if rank == 1:
        receive value from previous rank
        if is max odd:
            send value to next rank
        else:
            send previous rank value
        if is max even:
            send value to next rank
        else:
            send previous rank value

    // REPEAT FOR OTHER RANKS

    // Final Step
    if rank == 0:
        print the value sent to it
