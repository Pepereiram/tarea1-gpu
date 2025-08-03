#include <gtest/gtest.h>
#include "../Matrix.h"

TEST(MatrixTest, ConstructorAndFill) {
    Matrix A(2, 3);
    A.fill(5.0);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_EQ(A(i, j), 5.0);
}

TEST(MatrixTest, GetSetOperator) {
    Matrix A(2, 2);
    A(0, 0) = 1.1;
    A(1, 1) = 2.2;
    EXPECT_EQ(A(0, 0), 1.1);
    EXPECT_EQ(A(1, 1), 2.2);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix A(2, 2);
    A.fill(3.0);
    Matrix B = A;
    EXPECT_TRUE(B == A);
}

TEST(MatrixTest, AssignmentOperator) {
    Matrix A(2, 2), B(2, 2);
    A.fill(4.0);
    B = A;
    EXPECT_TRUE(B == A);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix A(2, 2), B(2, 2);
    A.fill(1.0);
    B.fill(2.0);
    A += B;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(A(i, j), 3.0);
}

TEST(MatrixTest, MatrixSubtraction) {
    Matrix A(2, 2), B(2, 2);
    A.fill(5.0);
    B.fill(2.0);
    A -= B;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(A(i, j), 3.0);
}

TEST(MatrixTest, ScalarMultiplication) {
    Matrix A(2, 2);
    A.fill(2.0);
    A *= 3.0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(A(i, j), 6.0);
}

TEST(MatrixTest, MatrixMultiplication) {
    Matrix A(2, 3);
    Matrix B(3, 2);
    A.fill(1.0);
    B.fill(2.0);
    A *= B;
    EXPECT_EQ(std::get<0>(A.size()), 2);
    EXPECT_EQ(std::get<1>(A.size()), 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            EXPECT_EQ(A(i, j), 6.0); // 3*2
}

TEST(MatrixTest, Transpose) {
    Matrix A(2, 3);
    int val = 1;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            A(i, j) = val++;
    A.transpose();
    EXPECT_EQ(std::get<0>(A.size()), 3);
    EXPECT_EQ(std::get<1>(A.size()), 2);
    EXPECT_EQ(A(1, 0), 2); // Was A(0,1)
}

TEST(MatrixTest, MinMax) {
    Matrix A(2, 2);
    A(0, 0) = 3;
    A(0, 1) = -1;
    A(1, 0) = 10;
    A(1, 1) = 5;
    EXPECT_EQ(A.min(), -1);
    EXPECT_EQ(A.max(), 10);
}

TEST(MatrixTest, ExceptionOnInvalidAddition) {
    Matrix A(2, 2), B(3, 3);
    EXPECT_THROW(A += B, std::logic_error);
}

TEST(MatrixTest, ExceptionOnInvalidMultiplication) {
    Matrix A(2, 2), B(1, 3);
    EXPECT_THROW(A *= B, std::logic_error);
}

TEST(MatrixTest, ExceptionOnMinEmptyMatrix) {
    Matrix A;
    EXPECT_THROW(A.min(), std::logic_error);
}
