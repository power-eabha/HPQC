# Topic 9: Quantum Computing on GPUs

## Overview

This topic explores how a quantum computer simulator can be accelerated using GPUs.

The main idea is to move the quantum workspace from CPU memory to GPU memory and replace NumPy operations with PyTorch operations.

---

## Key Concept

Quantum simulations involve large matrix and vector operations, which are well suited to GPUs due to their parallel processing capabilities.

---

## Implementation

### File

- `gpu_part3.py` — minimal PyTorch-based simulation

### Features

- uses PyTorch instead of NumPy
- checks if GPU is available
- runs on CPU if GPU is not available
- performs basic tensor operations

---

## How to run

```bash
python3 gpu_part3.py
