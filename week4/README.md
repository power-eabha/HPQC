# Topic 4: MPI Communications

## Part 1: Demonstrating Communications

### Step 1: Run the code as-is

The provided `comm_test_mpi.c` program was compiled and run using `mpicc` and `mpirun`.

Example output:

Hello, I am 1 of 2. Sent 10 to Rank 0  
Hello, I am 0 of 2. Received 10 from Rank 1  

This demonstrates basic point-to-point communication using MPI_Send() and MPI_Recv(). The order of execution may vary between runs due to the independent nature of processes.

### Step 2: Functionalise the code

The original `comm_test_mpi.c` program was rewritten into smaller functions to improve readability and maintainability. The communication logic was split into:
- `root_task()` for rank 0
- `client_task()` for non-root ranks
- `print_warning()` for invalid communicator sizes

This made the structure of the program much clearer while preserving the same behaviour as the original code.

#### Example output with 2 processes

```text
Hello, I am 0 of 2. Received 10 from Rank 1
Hello, I am 1 of 2. Sent 10 to Rank 0

#### Example output with 4 processes

Hello, I am 1 of 4. Sent 10 to Rank 0
Hello, I am 2 of 4. Sent 20 to Rank 0
Hello, I am 3 of 4. Sent 30 to Rank 0
Hello, I am 0 of 4. Received 10 from Rank 1
Hello, I am 0 of 4. Received 20 from Rank 2
Hello, I am 0 of 4. Received 30 from Rank 3

### Step 3: Experiment with Send Types

The communication program was modified to use four different variants of the `MPI_Send()` function:

- `MPI_Ssend()` (synchronous send)
- `MPI_Bsend()` (buffered send)
- `MPI_Rsend()` (ready send)
- `MPI_Isend()` (non-blocking send)

Each version was compiled and run using 2 processes.

#### Results

All four versions successfully compiled and executed without errors in this case. The output for each version was similar:

```text
Hello, I am 1 of 2. Sent 10 to Rank 0
Hello, I am 0 of 2. Received 10 from Rank 1

### Step 4: Benchmark the communication code

Internal timing was added to the communication code using `MPI_Wtime()`. Timing was measured separately around the send and receive calls so that the communication cost for each rank could be observed directly inside the program.

The logic used was:

1. Record the start time
2. Execute the send or receive operation
3. Record the end time
4. Print the elapsed time

#### Example output with 2 processes

```text
Hello, I am 0 of 2. Received 10 from Rank 1
Rank 0 took 0.000019 seconds to receive from Rank 1
Hello, I am 1 of 2. Sent 10 to Rank 0
Rank 1 took 0.000009 seconds to send to Rank 0

## Part 2: Benchmarking Latency and Bandwidth

## Part 2: Benchmarking Latency and Bandwidth

### Step 1: Ping-pong program

A `pingpong.c` program was implemented to measure communication time between two MPI processes. The root process sends an integer counter to the client process, which increments it and sends it back. This continues until the required number of pings is reached.

#### Results

| Number of Pings | Elapsed Time (s) | Average Time per Ping-Pong (s) |
|----------------:|-----------------:|--------------------------------:|
| 10              | 0.000214         | 0.000021                        |
| 100             | 0.000412         | 0.000004                        |
| 1000            | 0.002983         | 0.000002                        |
| 10000           | 0.028761         | 0.000002                        |

#### Observations

- The total elapsed time increases with the number of pings, as expected.
- The average time per ping-pong decreases rapidly at first and then stabilises.
- For larger numbers of pings (1000 and above), the average time converges to approximately:

\[
\text{Latency} \approx 2 \times 10^{-6} \text{ seconds}
\]

- This shows that small runs are dominated by startup overhead, while larger runs give a more accurate estimate of communication latency.

This experiment demonstrates that repeated message passing can be used to estimate the baseline latency of MPI communication.

### Step 2: Measuring latency

The ping-pong program was run with increasing numbers of pings to determine whether the average communication time converges.

#### Results

| Number of Pings | Average Time per Ping-Pong (s) |
|----------------:|-------------------------------:|
| 10              | 0.000021                       |
| 100             | 0.000004                       |
| 1000            | 0.000002                       |
| 10000           | 0.000002                       |

#### Observations

- The average time per ping-pong decreases rapidly for small numbers of pings.
- As the number of pings increases, the average time stabilises.
- For large numbers of pings (1000 and above), the average time converges to approximately:

\[
\text{Latency} \approx 2 \times 10^{-6} \text{ seconds}
\]

- This shows that startup overhead dominates small runs, while larger runs provide a more accurate estimate of communication latency.

#### Conclusion

The stabilised average time provides an estimate of the latency of MPI communication between two processes. Repeating the communication many times reduces the impact of overhead and improves the reliability of the measurement.

### Step 3: Measuring bandwidth

A second program, `pingpong_bandwidth.c`, was implemented to investigate how communication time depends on message size. Instead of sending a single integer, arrays of increasing size were sent between the two processes.

The program was run with a fixed number of pings (1000) while varying the message size.

#### Results

| Message Size (ints) | Elapsed Time (s) | Average Time per Ping-Pong (s) |
|--------------------:|-----------------:|--------------------------------:|
| 1                   | 0.000712         | 0.000001                        |
| 10                  | 0.001130         | 0.000001                        |
| 100                 | 0.001184         | 0.000001                        |
| 1000                | 0.003894         | 0.000004                        |
| 10000               | 0.016084         | 0.000016                        |

#### Observations

- For small message sizes (1–100 integers), the average time per ping-pong remains approximately constant at around \(1 \times 10^{-6}\) seconds.
- This indicates that communication time is dominated by **latency** for small messages.
- As the message size increases (1000–10000 integers), the average time increases significantly.
- This shows that for larger messages, the cost of transferring data becomes important, and communication time is dominated by **bandwidth**.

#### Interpretation

The total communication time can be modelled as:

\[
\text{time} = \text{latency} + (\text{message size} \times \text{transfer cost})
\]

- The constant part corresponds to **latency**, which was previously estimated to be approximately \(2 \times 10^{-6}\) seconds.
- The increasing part corresponds to the cost of sending more data, which is related to the **bandwidth** of the system.

#### Conclusion

This experiment demonstrates two key properties of MPI communication:

- **Latency** dominates for small messages, resulting in nearly constant communication time.
- **Bandwidth** dominates for larger messages, causing communication time to increase with message size.

The results clearly show the transition from latency-dominated to bandwidth-dominated communication as message size increases.


## Part 3: Collective Communications

### Step 1: Broadcast vs Scatter vs DIY

Three different approaches were tested for distributing vector data across MPI processes.

- **DIY/manual approach**: based on the previous MPI vector code, where each process worked out its own portion of the problem itself.
- **Broadcast approach**: the root process created the full vector and sent a copy of the whole array to every process using `MPI_Bcast()`.
- **Scatter approach**: the root process created the full vector and distributed only the relevant chunk to each process using `MPI_Scatter()`.

Each version was first tested with small input values of known output to confirm correctness.

#### Results

| Version   | Input | Expected Sum | Output Sum | Internal Runtime (s) |
|----------|------:|-------------:|-----------:|---------------------:|
| DIY      | 10    | 55           | 55         | 0.000044             |
| Broadcast| 10    | 55           | 55         | 0.000041             |
| Scatter  | 12    | 78           | 78         | 0.000053             |

#### Observations

- All three versions produced the correct result.
- The broadcast version was slightly faster than the DIY version for this small test.
- The scatter version was also correct, though it used a slightly different input (`12`) so that the vector could be divided evenly across 4 processes.
- `MPI_Bcast()` sends the whole vector to every process, which is simple but may use more communication and memory overall.
- `MPI_Scatter()` sends only the relevant chunk to each process, which is expected to be more efficient for larger problems.

#### Conclusion

For these small test cases, the differences in runtime were extremely small. However, the collective communication methods worked correctly and showed the expected differences in communication strategy. In particular, scattering only the required chunk of the array should scale better than broadcasting the full vector to every process.
