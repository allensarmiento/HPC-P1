// Names: Andrew Lopez, Allen Sarmiento, Ryan Shim
// Course: CPSC 479 - Intro to HPC
// Suject: Project 1 - Ring Leader Election
// Last Updated: 2-28-2019
//
// NOTES:
//  - Run alpine-mpich container in docker:
//      docker run --rm -it -v $(pwd):/project nlknguyen/alpine-mpich
//
//  - Position buffer format:
//      - position[0] = president max value 
//      - position[1] = vice max value
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MAX_NUMBERS = 2;
    int positions[MAX_NUMBERS];
    int token, pres, vice;

    // Init each non-rank 0 process 
    if (rank != 0) {
        MPI_Recv(&positions, MAX_NUMBERS, MPI_INT, rank-1,
                0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("PROC-%d received positions[0]=%d and positions[1]=%d"
                " from PROC-%d\n", rank, positions[0], positions[1], rank-1);

        srand(time(NULL) * rank);
        token = rand() % 100;

        if (token <= 10)
            token += 10;
        token = 1000 + (rank*100) + token;

        // Determine new president and vice
        if (token % 2 == 0 && token > positions[0]) {
            positions[0] = token;
        } else if (token % 2 != 0 && token > positions[1]) {
            positions[1] = token;
        }

    } else {
        srand(time(NULL) * rank);
        token = rand() % 100;
        
        // Token digit format: 1-rank-xx
        if (token <= 10)
            token += 10;
        token = 1000 + (rank*100) + token;

        // Init election values
        if (token % 2 == 0) {
            positions[0] = token;
            positions[1] = 1;
        } else {
            positions[0] = 0;
            positions[1] = token;
        }
        printf("PROC-0 init positions[0]=%d and positions[1]=%d\n",
                positions[0], positions[1]);
    }

    // All processes send
    MPI_Send(&positions, MAX_NUMBERS, MPI_INT, (rank + 1) % size,
            0, MPI_COMM_WORLD);

    // PROC-0 receives the final values from PROC-(n-1)
    if (rank == 0) {
        MPI_Recv(&positions, MAX_NUMBERS, MPI_INT, size - 1,
                0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("PROC-0 received positions[0]=%d and positions[1]=%d"
                " from final PROC\n", rank, positions[0], positions[1]);

        if (token % 2 == 0 && token > positions[0]) {
            positions[0] = token;
        } else if (token % 2 != 0 && token > positions[1]) {
            positions[1] = token;
        }

        // Determine president and vice ranks
        int p_rank = positions[0] / 100 - 10;
        int v_rank = positions[1] / 100 - 10;
        printf("\nPresident Value: %d\nVice Value: %d\n", 
                positions[0], positions[1]);
        printf("\nPROC-%d is President.\nPROC-%d is Vice President.\n",
                p_rank, v_rank);
    }

    MPI_Finalize();
    return 0;
}
