# LinearAlgebra_Exploration
Exploring optimization techniques for common matrix and vector operations

This project aims to do two things:
- Provide multiple implementations of common matrix operations (especially multiplication)
- Benchmark the performance of all implementations

The result will be a resuable library for linear algebra.

### Current Functions
- `add_matrix_naive`
    addition of two any-size matrices
- `sub_matrix_naive`
    subtraction of two any-size matrices
- `multiply_222_naive`
    multiplication of two 2x2 matrices normally
- `multiply_222_strassen`
    multiplication of two 2x2 matrices with [Strassen's Algorithm](https://en.wikipedia.org/wiki/Strassen_algorithm)

> Please feel free to contribute different ways to implement the same operations
