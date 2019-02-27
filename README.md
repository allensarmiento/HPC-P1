# HPC-P1

### CPSC 479 - Project 1
#### Ring Election Project

### Group Members:
- Andrew Lopez (alopez8969@csu.fullerton.edu)
- Allen Sarmiento (allensarmiento@csu.fullerton.edu)
- Ryan Shim (rcshim@csu.fullerton.edu)

### Pseudocode:
    /* This program sends the maximum odd/even value in a ring-like fashion.
     * Each rank receives a value and determines which value should be sent to
     * the next rank. This process repeats until we get back to rank 0.
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
