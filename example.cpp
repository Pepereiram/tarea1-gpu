#include <iostream>
#include <cassert>
#include "Matrix.h"

void test_constructor_and_fill() {
    Matrix A(2, 3);
    A.fill(5.0);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            assert(A(i, j) == 5.0);
    std::cout << "[OK] Constructor and fill\n";
}

void test_get_set() {
    Matrix A(2, 2);
    A(0, 0) = 1.1;
    A(1, 1) = 2.2;
    assert(A(0, 0) == 1.1);
    assert(A(1, 1) == 2.2);
    std::cout << "[OK] Get and set operator()\n";
}

void test_copy_constructor() {
    Matrix A(2, 2);
    A.fill(3.0);
    Matrix B = A;
    assert(B == A);
    std::cout << "[OK] Copy constructor and ==\n";
}

void test_assignment_operator() {
    Matrix A(2, 2), B(2, 2);
    A.fill(4.0);
    B = A;
    assert(B == A);
    std::cout << "[OK] Assignment operator\n";
}

void test_addition() {
    Matrix A(2, 2), B(2, 2);
    A.fill(1.0);
    B.fill(2.0);
    A += B;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            assert(A(i, j) == 3.0);
    std::cout << "[OK] Matrix addition\n";
}

void test_subtraction() {
    Matrix A(2, 2), B(2, 2);
    A.fill(5.0);
    B.fill(2.0);
    A -= B;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            assert(A(i, j) == 3.0);
    std::cout << "[OK] Matrix subtraction\n";
}

void test_scalar_multiplication() {
    Matrix A(2, 2);
    A.fill(2.0);
    A *= 3.0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            assert(A(i, j) == 6.0);
    std::cout << "[OK] Scalar multiplication\n";
}

void test_matrix_multiplication() {
    Matrix A(2, 3);
    Matrix B(3, 2);
    A.fill(1.0);
    B.fill(2.0);
    A *= B;
    assert(std::get<0>(A.size()) == 2 && std::get<1>(A.size()) == 2);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            assert(A(i, j) == 6.0); // 3*2
    std::cout << "[OK] Matrix multiplication\n";
}

void test_transpose() {
    Matrix A(2, 3);
    int val = 1;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            A(i, j) = val++;
    A.transpose();
    assert(std::get<0>(A.size()) == 3);
    assert(std::get<1>(A.size()) == 2);
    assert(A(1, 0) == 2); // Was A(0,1)
    std::cout << "[OK] Transpose\n";
}

void test_min_max() {
    Matrix A(2, 2);
    A(0, 0) = 3;
    A(0, 1) = -1;
    A(1, 0) = 10;
    A(1, 1) = 5;
    assert(A.min() == -1);
    assert(A.max() == 10);
    std::cout << "[OK] Min and max\n";
}

void test_exceptions() {
    try {
        Matrix A(2, 2), B(3, 3);
        A += B;
        assert(false); // Should not reach here
    } catch (std::logic_error &e) {
        std::cout << "[OK] Exception on invalid addition\n";
    }

    try {
        Matrix A(2, 2), B(1, 3);
        A *= B;
        assert(false);
    } catch (std::logic_error &e) {
        std::cout << "[OK] Exception on invalid multiplication\n";
    }

    try {
        Matrix A;
        A.min();
        assert(false);
    } catch (std::logic_error &e) {
        std::cout << "[OK] Exception on min() of empty matrix\n";
    }
}

int main() {
    test_constructor_and_fill();
    test_get_set();
    test_copy_constructor();
    test_assignment_operator();
    test_addition();
    test_subtraction();
    test_scalar_multiplication();
    test_matrix_multiplication();
    test_transpose();
    test_min_max();
    test_exceptions();

    std::cout << "\nAll tests passed successfully!\n";
    return 0;
}

