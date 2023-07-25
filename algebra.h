#include <iostream>
#include <array>

// Processing
//-----------------------------------------------------------------------------

// Internal processing elements shared by polymorphic functions

template <typename matrix_A, typename matrix_B, typename matrix_C>
void process_add_matrix_naive(matrix_C &C, const matrix_A &A, const matrix_B &B)
{
    int rows = A.size();
    int cols = A[0].size();
    int row, col;

    for (int i = 0; i < rows * cols; i++)
    {
        row = i / cols;
        col = i % cols;

        C[row][col] = A[row][col] + B[row][col];
    }
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
void process_sub_matrix_naive(matrix_C &C, const matrix_A &A, const matrix_B &B)
{
    int rows = A.size();
    int cols = A[0].size();
    int row, col;

    for (int i = 0; i < rows * cols; i++)
    {
        row = i / cols;
        col = i % cols;

        C[row][col] = A[row][col] - B[row][col];
    }
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
void process_mul_222_naive(matrix_C &C, matrix_A &A, matrix_B &B)
{
    C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
void process_mul_222_strassen(matrix_C &C, matrix_A &A, matrix_B &B)
{
    // Not using data structure for p_i
    // Array creation adds overhead and speed decreases
    auto p0 = A[0][0] * (B[0][1] - B[1][1]);
    auto p1 = (A[0][0] + A[0][1]) * B[1][1];
    auto p2 = (A[1][0] + A[1][1]) * B[0][0];
    auto p3 = A[1][1] * (B[1][0] - B[0][0]);
    auto p4 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    auto p5 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
    auto p6 = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]);

    C[0][0] = p4 + p3 - p1 + p5;
    C[0][1] = p0 + p1;
    C[1][0] = p2 + p3;
    C[1][1] = p4 + p0 - p2 - p6;
}
// Addition
//-----------------------------------------------------------------------------

// Simple addition of two matrices
// C = A + B

template <typename matrix>
matrix add_matrix_naive(const matrix &A, const matrix &B)
{
    matrix C = A;
    process_add_matrix_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B>
matrix_A add_matrix_naive(const matrix_A &A, const matrix_B &B)
{
    matrix_A C = A;
    process_add_matrix_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
matrix_C add_matrix_naive(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_add_matrix_naive(C, A, B);

    return C;
}

// Simple subtraction of two matrices
// C = A - B

template <typename matrix>
matrix sub_matrix_naive(const matrix &A, const matrix &B)
{
    matrix C = A;
    process_sub_matrix_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B>
matrix_A sub_matrix_naive(const matrix_A &A, const matrix_B &B)
{
    matrix_A C = A;
    process_sub_matrix_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
matrix_C sub_matrix_naive(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_sub_matrix_naive(C, A, B);

    return C;
}

// Multiplication
//-----------------------------------------------------------------------------

// 2,2,2 shows the size of the two matrices
// it means 2x2 * 2x2
// based on the convention nxp * pxm being multiplied
// p has to be common to multiply
// This is the simplest approach
// C = A * B

template <typename matrix>
matrix multiply_222_naive(const matrix &A, const matrix &B)
{
    matrix C = A;
    process_mul_222_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B>
matrix_A multiply_222_naive(const matrix_A &A, const matrix_B &B)
{
    matrix_A C = A;
    process_mul_222_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
matrix_A multiply_222_naive(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_mul_222_naive(C, A, B);

    return C;
}

// This implementation using Strassen Algorithm
// https://en.wikipedia.org/wiki/Strassen_algorithm
// It uses one less multiplication operation than before
//
// 2,2,2 shows the size of the two matrices being multiplied
// it means 2x2 * 2x2
// based on the convention nxp * pxm
// p has to be common to multiply
// This is the simplest approach
// C = A * B

template <typename matrix>
matrix multiply_222_strassen(const matrix &A, const matrix &B)
{
    matrix C = A;
    process_mul_222_strassen(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B>
matrix_A multiply_222_strassen(const matrix_A &A, const matrix_B &B)
{
    matrix_A C = A;
    process_mul_222_strassen(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
matrix_C multiply_222_strassen(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_mul_222_strassen(C, A, B);

    return C;
}

// Display
//-----------------------------------------------------------------------------

template <typename matrix>
void display_matrix(const matrix &m)
{
    int rows = m.size();
    int cols = m[0].size();

    for (int i = 0; i < rows * cols; i++)
    {
        if (i % cols == 0 && i != 0)
        {
            std::cout << std::endl;
        }

        std::cout << m[i / cols][i % cols] << "\t";
    }
    std::cout << std::endl;
}
