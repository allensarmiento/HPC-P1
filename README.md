# HPC-P1

### CPSC 479 - Project 1
#### Ring Election Project

### Group Members:
- Andrew Lopez (alopez8969@csu.fullerton.edu)
- Allen Sarmiento (allensarmiento@csu.fullerton.edu)
- Ryan Shim (rcshim@csu.fullerton.edu)

### Pseudocode:
    # Initializtion
    Create process with N ranks
    number = new Random Number
    number = '1' + rank + number
    
    # Passing values between ranks
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
    
    REPEAT FOR OTHER RANKS 

    # Final Step
    if rank == 0:
        print the value sent to it 
