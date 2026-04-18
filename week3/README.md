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

---

## Part 2: Breakdown of `proof.c`

The `proof.c` program is an MPI program that splits work between a root process and a set of client processes. The program takes one numerical argument from the command line. Each client process calculates a value and sends it to the root process, and the root process receives all of these values and adds them together.

### `main()`

The `main()` function controls the overall structure of the program. It first checks that the user has supplied the required numerical argument. It then initialises MPI with `MPI_Init()`, gets the rank of the current process using `MPI_Comm_rank()`, and gets the total number of processes using `MPI_Comm_size()`. After this, it checks that the communicator size is valid, decides which task the current process should perform, and finally finalises MPI with `MPI_Finalize()`.

### `check_args()`

This function checks that the correct number of command-line arguments has been supplied. If one numerical argument is present, it converts it from a string to an integer using `atoi()`. If not, it prints an error message and exits.

### `check_uni_size()`

This function checks that the MPI communicator has a valid size. If there are too few processes available, it prints an error and exits.

### `check_task()`

This function decides which task a process should carry out based on its rank. If the rank is 0, the process is the root and it calls `root_task()`. Otherwise, the process is a client and it calls `client_task()`.

### `client_task()`

Each client process creates a value using:

`send_message = my_rank * num_arg`

This value is then sent to the root process using `MPI_Send()`.

### `root_task()`

The root process loops over all client ranks from 1 up to `uni_size - 1`. It receives one integer from each client using `MPI_Recv()` and adds these received values to a running total called `output_sum`. At the end, it prints the combined result.

### Overall Program Logic

1. Check the input argument.  
2. Initialise MPI.  
3. Get process rank and communicator size.  
4. Check the communicator size is valid.  
5. If rank = 0, receive and sum messages.  
6. If rank > 0, calculate a message and send it to root.  
7. Finalise MPI.  

### Equivalent Mathematical Formula

Each client sends:

`my_rank * num_arg`

So the root calculates:

`num_arg * (1 + 2 + 3 + ... + (uni_size - 1))`

Using the formula for the sum of the first `n` integers, the final result can be written directly as:

\[
\text{output\_sum} = \text{num\_arg} \cdot \frac{(\text{uni\_size}-1)\text{uni\_size}}{2}
\]

This means the MPI program is demonstrating communication and task splitting, but the final answer could also be obtained directly with a single mathematical expression.

---

## Part 3: Vector Addition

### Serial Implementation

The provided `vector_serial.c` program was first compiled and executed. In its original form, it produced a trivial result because every element of the vector was initialised to zero. To make the program non-trivial, the vector was modified so that each element was assigned the value `i + 1`. This created a vector containing the integers from 1 up to the input size.

For example, when the input size was 10, the output was:

```text
Sum: 55
