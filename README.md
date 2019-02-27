# HPC-P1

### CPSC 479 - Project 1
#### Ring Election Project

### Group Members:
- Andrew Lopez (alopez8969@csu.fullerton.edu)
- Allen Sarmiento (allensarmiento@csu.fullerton.edu)
- Ryan Shim (rcshim@csu.fullerton.edu)

### Pseudocode:
    Create a process with N ranks.  
    Assign random values to each rank.
    Start from process 0:
      - For odd election: the max odd number gets sent to the next rank.
      - For even election: the max even number gets sent to the next rank.
    Process 0 should end up with the largest odd/even number.

