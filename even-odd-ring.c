/* This program is implementing the EVEN counting problem only.
 * Status: Incorrect output 
 * This program is creating only a 2 random values at rank 0 and not 0 rank. 
 * We want a random value generated each time so that we can compare which value to
 * send over. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[]) {
  // Initialization
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Generate Random Number
  srand(time(NULL));
  int rand_num=rand();
  if (rand_num < 10) rand_num += 10;
  if (rand_num > 100) rand_num %= 100;

  int token;
  if (rank != 0) {
    MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Generate Random Number
    rand_num=rand();
    if (rand_num < 10) rand_num += 10;
    if (rand_num > 100) rand_num %= 100;
    printf("I am process %d with a value of %d\n", rank, rand_num);

    printf("Process %d received token %d from process %d\n", rank, token, rank - 1);
  } else {
    token = rand_num;
    printf("I am process %d with a value of %d\n", rank, rand_num);
  }
  
  // Even counting ring
  if (token %2 == 0 && rand_num % 2 == 0 && rand_num > token) {
    token = rand_num;
  }
  MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

  // Now process 0 can receive from the last process.
  if (rank == 0) {
    MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received token %d from process %d\n", rank, token, size - 1);
  }

  MPI_Finalize();

  return 0;
}
