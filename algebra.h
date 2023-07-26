#include <iostream>

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

template <typename matrix_A, typename matrix_B, typename matrix_C>
void process_mul_333_naive(matrix_C &C, matrix_A &A, matrix_B &B)
{
    C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0];
    C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1];
    C[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2];

    C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0];
    C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1];
    C[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2];

    C[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0];
    C[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1];
    C[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2];
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
void process_mul_333_laderman(matrix_C &C, matrix_A &A, matrix_B &B)
{
    auto p1 = (A[0][0] + A[0][1] + A[0][2] - A[1][0] - A[1][1] - A[2][1] - A[2][2]) * B[1][1];
    auto p2 = (A[0][0] - A[1][0]) * (-B[0][1] + B[1][1]);
    auto p3 = A[1][1] * (-B[0][0] + B[0][1] + B[1][0] - B[1][1] - B[1][2] - B[2][0] + B[2][2]);
    auto p4 = (-A[0][0] + A[1][0] + A[1][1]) * (B[0][0] - B[0][1] + B[1][1]);
    auto p5 = (A[1][0] + A[1][1]) * (-B[0][0] + B[0][1]);
    auto p6 = A[0][0] * B[0][0];
    auto p7 = (-A[0][0] + A[2][0] + A[2][1]) * (B[0][0] - B[0][2] + B[1][2]);
    auto p8 = (-A[0][0] + A[2][0]) * (B[0][2] - B[1][2]);
    auto p9 = (A[2][0] + A[2][1]) * (-B[0][0] + B[0][2]);
    auto p10 = (A[0][0] + A[0][1] + A[0][2] - A[1][1] - A[1][2] - A[2][0] - A[2][1]) * B[1][2];
    auto p11 = A[2][1] * (-B[0][0] + B[0][2] + B[1][0] - B[1][1] - B[1][2] - B[2][0] + B[2][1]);
    auto p12 = (-A[0][2] + A[2][1] + A[2][2]) * (B[1][1] + B[2][0] - B[2][1]);
    auto p13 = (A[0][2] - A[2][2]) * (B[1][1] - B[2][1]);
    auto p14 = A[0][2] * B[2][0];
    auto p15 = (A[2][1] + A[2][2]) * (-B[2][0] + B[2][1]);
    auto p16 = (-A[0][2] + A[1][1] + A[1][2]) * (B[1][2] + B[2][0] - B[2][2]);
    auto p17 = (A[0][2] - A[1][2]) * (B[1][2] - B[2][2]);
    auto p18 = (A[1][1] + A[1][2]) * (-B[2][0] + B[2][2]);
    auto p19 = A[0][1] * B[1][0];
    auto p20 = A[1][2] * B[2][1];
    auto p21 = A[1][0] * B[0][2];
    auto p22 = A[2][0] * B[0][1];
    auto p23 = A[2][2] * B[2][2];

    C[0][0] = p6 + p14 + p19;
    C[0][1] = p1 + p4 + p5 + p6 + p12 + p14 + p15;
    C[0][2] = p6 + p7 + p9 + p10 + p14 + p16 + p18;
    C[1][0] = p2 + p3 + p4 + p6 + p14 + p16 + p17;
    C[1][1] = p2 + p4 + p5 + p6 + p20;
    C[1][2] = p14 + p16 + p17 + p18 + p21;
    C[2][0] = p6 + p7 + p8 + p11 + p12 + p13 + p14;
    C[2][1] = p12 + p13 + p14 + p15 + p22;
    C[2][2] = p6 + p7 + p8 + p9 + p23;
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
matrix_C multiply_222_naive(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_mul_222_naive(C, A, B);

    return C;
}

// This implementation using Strassen Algorithm
// https://en.wikipedia.org/wiki/Strassen_algorithm
// It uses one less multiplication operation than before

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

// 3,3,3 shows the size of the two matrices
// it means 3x3 * 3x3
// based on the convention nxp * pxm being multiplied
// p has to be common to multiply
// This is the simplest approach
// C = A * B

template <typename matrix>
matrix multiply_333_naive(const matrix &A, const matrix &B)
{
    matrix C = A;
    process_mul_333_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B>
matrix_A multiply_333_naive(const matrix_A &A, const matrix_B &B)
{
    matrix_A C = A;
    process_mul_333_naive(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
matrix_A multiply_333_naive(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_mul_333_naive(C, A, B);

    return C;
}

// This implementation using Laderman's technique
// https://www.ams.org/journals/bull/1976-82-01/S0002-9904-1976-13988-2/
// Uses 23 multiplication instead of 27

template <typename matrix>
matrix multiply_333_laderman(const matrix &A, const matrix &B)
{
    matrix C = A;
    process_mul_333_laderman(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B>
matrix_A multiply_333_laderman(const matrix_A &A, const matrix_B &B)
{
    matrix_A C = A;
    process_mul_333_laderman(C, A, B);

    return C;
}

template <typename matrix_A, typename matrix_B, typename matrix_C>
matrix_A multiply_333_laderman(matrix_C C, const matrix_A &A, const matrix_B &B)
{
    process_mul_333_laderman(C, A, B);

    return C;
}
