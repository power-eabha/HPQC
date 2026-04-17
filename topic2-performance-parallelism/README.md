## Results

### File Writing (Python)

| Input Size | Runtime (s) |
|-----------:|------------:|
| 100        | 0.000329    |
| 1000       | 0.000145    |
| 5000       | 0.000412    |

### File Reading (Python)

| File Size (chars) | Runtime (s) |
|------------------:|------------:|
| 88890             | 0.000130    |

### File Writing (C)

| Input Size | Runtime (s) |
|-----------:|------------:|
| 100        | 0.000152    |
| 1000       | 0.000373    |
| 5000       | 0.001626    |

### File Reading (C)

| File Size (chars) | Runtime (s) |
|------------------:|------------:|
| 88890             | 0.000656    |





## Conclusion

This exercise investigated runtime in Python and C for file writing and file reading operations. The results showed that execution times were very small for all tests, so some fluctuations were expected, especially for the Python writing measurements. At such short timescales, small differences in system activity can affect the measured runtime.

For the C file-writing program, the runtime increased clearly as the input size increased from 100 to 5000 lines. This made the scaling behaviour easier to observe. The Python writing results were less consistent, but still showed that larger workloads generally take longer.

Both the Python and C reading programs were able to read the file quickly. In this case, the Python read time was lower than the C read time, which shows that performance can depend not only on the language but also on how the task is implemented and how small the timings are. Since the measured times are extremely short, these results should be interpreted cautiously.

Overall, the exercise showed that runtime depends on both the size of the workload and the type of operation being performed. File input/output introduces overhead because the program must interact with the operating system. The results also showed that very small timing measurements can be noisy, so repeated tests or larger workloads would give a more reliable comparison.
