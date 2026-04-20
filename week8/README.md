# Topic 8: Quantum Algorithms

## Overview

This folder contains my work for Topic 8 based on the ENCCS Quantum Computing tutorials. The focus of this topic is on quantum algorithms, specifically Grover’s search algorithm and how it can provide a speedup over classical search methods.

The code builds on the ideas from Topic 7, where quantum states are represented as vectors and manipulated using linear algebra operations.

---

## Part 1: Background

Quantum computing represents information using qubits rather than classical bits. Qubits can exist in superpositions of states, allowing quantum algorithms to explore multiple possibilities simultaneously.

Operations on qubits are represented using matrices (quantum gates), and measurements collapse the system probabilistically to a classical result.

---

## Part 2: Grover’s Search Algorithm

### Description

Grover’s algorithm is a quantum search algorithm that allows us to find a marked item in an unsorted database of size \( N \) in approximately:

\[
O(\sqrt{N})
\]

time, compared to \( O(N) \) for classical search.

The algorithm works by:
- preparing all states in equal superposition
- applying a **phase oracle** to mark the target state
- applying a **diffusion operator** (inversion about the mean)
- repeating this process to amplify the probability of the correct result

---

## Implementation

### File

- `grover_part2.py` — a minimal implementation of Grover’s algorithm using NumPy

### Features

The implementation includes:
- creation of a quantum workspace
- pushing qubits into superposition
- application of quantum gates (X, H)
- implementation of:
  - a **sample phase oracle**
  - a **zero phase oracle**
- repeated Grover iterations
- probabilistic measurement of the final state

---

## How to Run

```bash
python3 grover_part2.py
