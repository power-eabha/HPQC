# Topic 5: Communicators and Topologies

This folder contains my work for Topic 5. I completed the serial string simulation, removed hard-coded input/output values by creating an argument-based version, tested and benchmarked the serial implementation, and visualised the output using the provided Python animation script.

Due to the remote teaching server becoming unavailable before final testing, the MPI extension of the string model was not completed to the same level as the earlier weeks. However, the serial implementation, argument handling, debugging notes, and benchmarking are fully documented below.
## Part 1: Oscillations on a String (Serial Implementation)

### Step 1: Running the provided code

The provided `string_wave.c` program was compiled using:

```bash
gcc string_wave.c -o string_wave -lm
