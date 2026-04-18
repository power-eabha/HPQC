# Topic 3: Introduction to MPI

## Part 1: MPI Hello World

A simple MPI program was implemented in C. The program initialises MPI using `MPI_Init()`, obtains the rank of each process using `MPI_Comm_rank()`, and obtains the total number of processes using `MPI_Comm_size()`.

Each process prints a message containing its rank and the total number of processes.

### Example Output

Hello from process 3 of 4  
Hello from process 2 of 4  
Hello from process 0 of 4  
Hello from process 1 of 4  

The order of output is not sequential because processes execute independently in parallel.

### Timing Results

| Processes | Real Time (s) | User Time (s) | Sys Time (s) |
|----------:|--------------:|--------------:|-------------:|
| 2         | 0.354         | 0.035         | 0.094        |
| 4         | 0.373         | 0.178         | 0.073        |

The results show that multiple processes are executed simultaneously. For such a simple program, increasing the number of processes does not significantly reduce runtime because overhead dominates.
