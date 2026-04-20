# Topic 4: MPI Communications

## Part 1: Demonstrating Communications

### Step 1: Run the code as-is

The provided `comm_test_mpi.c` program was compiled and run using `mpicc` and `mpirun`.

Example output:

Hello, I am 1 of 2. Sent 10 to Rank 0  
Hello, I am 0 of 2. Received 10 from Rank 1  

This demonstrates basic point-to-point communication using MPI_Send() and MPI_Recv(). The order of execution may vary between runs due to the independent nature of processes.

