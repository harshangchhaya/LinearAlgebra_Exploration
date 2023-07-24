// An exploration to find the fastest matrix multiplication
// Future implementation with threads, simd, etc. comping up

#include <iostream>
#include <vector>
#include <chrono>
#include "algebra.h"

int main()
{
    // Make your vectors and matrices
    // Run the operation to test different
    std::cout << "Welcome to this program" << std::endl;
    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> B = {{5, 6}, {7, 8}};
    // display_matrix(A, 2, 2);
    // display_matrix(B, 2, 2);

    auto start = std::chrono::high_resolution_clock::now();
    auto C = multiply_222_naive(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    display_matrix(C, 2, 2);
    std::cout << "time: " << duration1 << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto D = multiply_222_strassen(A, B);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    display_matrix(D, 2, 2);
    std::cout << "time: " << duration2 << std::endl;
}