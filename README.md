# Sorting Algorithms Benchmark

This project compares the performance of classical sorting algorithms (Bubble, Merge, Quick, Heap, etc.) on arrays of size 10,000 in C++.

## Features
- Measures runtime on:
  - Random arrays
  - Sorted arrays (best case)
  - Reversed arrays (worst case)
- Outputs results in milliseconds

## Build and Run

```bash
g++ -std=c++17 main.cpp -o sort_benchmark
./sort_benchmark
