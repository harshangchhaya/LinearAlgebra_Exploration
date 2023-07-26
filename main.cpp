// An exploration to find the fastest matrix multiplication
// Future implementation with threads, simd, etc. comping up

#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include "algebra.h"

int main()
{
    // Make your vectors and matrices
    // Run the operation to test different

    std::cout << "Welcome to this program" << std::endl;
    std::array<std::vector<int>, 2> A = {{{1, 2}, {3, 4}}};
    std::array<std::array<int, 2>, 2> B = {{{5, 6}, {7, 8}}};
    std::vector<std::vector<int>> C = {{{0, 0}, {0, 0}}};

    // display_matrix(A, 2, 2);
    // display_matrix(B, 2, 2);
    // display_matrix(add_matrix_naive(B, A), 2, 2);
    // std::cout << std::endl;
    // display_matrix(sub_matrix_naive(B, A), 2, 2);
    // std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    auto X = multiply_222_naive(C, A, B);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    display_matrix(X);
    std::cout << "time: " << duration1 << std::endl;

    start = std::chrono::high_resolution_clock::now();
    auto D = multiply_222_strassen(A, B);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    display_matrix(D);
    std::cout << "time: " << duration2 << " naive" << std::endl;
}