#include <iostream>

// Multiplication
//-----------------------------------------------------------------------------
template <typename Matrix>
Matrix multiply_222_naive(const Matrix &A, const Matrix &B)
{
    // 2,2,2 shows the size of the two matrices
    // it means 2x2 * 2x2
    // based on the convention nxp * pxm
    // p has to be common to multiply
    // This is the simplest approach
    // output = A * B

    Matrix output = A;

    output[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    output[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    output[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    output[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    return output;
}

template <typename Matrix>
Matrix multiply_222_strassen(const Matrix &A, const Matrix &B)
{
    // This implementation using Strassen Algorithm
    // It uses one less multiplication operation than before
    //
    // 2,2,2 shows the size of the two matrices
    // it means 2x2 * 2x2
    // based on the convention nxp * pxm
    // p has to be common to multiply
    // This is the simplest approach
    // output = A * B

    Matrix output = A;

    auto p1 = A[0][0] * (B[0][1] - B[1][1]);
    auto p2 = (A[0][0] + A[0][1]) * B[1][1];
    auto p3 = (A[1][0] + A[1][1]) * B[0][0];
    auto p4 = A[1][1] * (B[1][0] - B[0][0]);
    auto p5 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    auto p6 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
    auto p7 = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]);

    output[0][0] = p5 + p4 - p2 + p6;
    output[0][1] = p1 + p2;
    output[1][0] = p3 + p4;
    output[1][1] = p5 + p1 - p3 - p7;

    return output;
}

// Display
//-----------------------------------------------------------------------------
template <typename Matrix>
void display_matrix(const Matrix &m, const int rows, const int cols)
{
    // Displays the Matrix
    // Asking for rows and columns in case they are not available in datastructure
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
