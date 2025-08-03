#include <cstddef>
#include <memory>
#include <iostream>
#include <string>
#include <tuple>
#include <iomanip>
#include <algorithm>

class Matrix
{
private:
    std::unique_ptr<double[]> mat; // Store the matrix
    int n = 0;                     // Number of rows
    int m = 0;                     // Number of columns

public:
    Matrix() : n(0), m(0), mat(nullptr) {};             // Empty constructor
    Matrix(int n_) : n(n_), m(1), mat(new double[n_]()) {};        // Constructor, vector like [1xn]
    Matrix(int n_, int m_) : n(n_), m(m_), mat(new double[n_ * m_]()) {}; // Constructor [nxm], n:rows, m: columns
    Matrix(const Matrix &matrix) : n(matrix.n), m(matrix.m) { // Constructor de Copia
        if (n > 0 && m > 0) {
            mat = std::make_unique<double[]>(n * m);
            std::copy(matrix.mat.get(), matrix.mat.get() + n * m, mat.get());
        } else {
            mat = nullptr;
        }
    }


    ~Matrix() {};          // Destructor

    // Setters and getters
    double &operator()(std::size_t x,
                       std::size_t y) { // Set value to (i,j) <row,column>
        if (x >= static_cast<size_t>(n) || y >= static_cast<size_t>(m))
            throw std::out_of_range("[MATRIX] Index out of bounds");
        return mat[x * m + y];
    }

    const double &operator()(
        std::size_t x,
        std::size_t y) const { // Get value from (i,j) <row,column>
        if (x >= static_cast<size_t>(n) || y >= static_cast<size_t>(m))
            throw std::out_of_range("[MATRIX] Index out of bounds");
        return mat[x * m + y];
    };

    void fill(double value) { // Fill all the matrix with a value
        std::fill(mat.get(), mat.get() + n * m, value);
    }

    // Dimensions
    std::tuple<int, int> size() const { // Return the size of the matrix
        return std::make_tuple(n, m);
    }

    int length() const { // Return the length of the matrix
        return std::max(n, m);
        }; // Return max dimension, usefull for vectors, e.g. [2,4] -> 4

    // Values
    double max() const { // Maximum value of the matrix
        if (!mat)
            throw std::logic_error("[MATRIX] Empty matrix has no max value");
        return *std::max_element(mat.get(), mat.get() + n * m);
    }

    double min() const { // Minimum value of the matrix
        if (!mat)
            throw std::logic_error("[MATRIX] Empty matrix has no min value");
        return *std::min_element(mat.get(), mat.get() + n * m);
    }

    // Utilitary functions
    friend std::ostream &operator<<(  // Display matrix to console
        std::ostream &os, const Matrix &mat) {
            for (int i = 0; i < mat.n; ++i) {
                for (int j = 0; j < mat.m; ++j) {
                    os << std::setw(10) << mat(i, j) << " ";
                }
                os << "\n";
            }
            return os;
        };
    
    friend std::istream &operator>>( // Interactive create matrix from console
        std::istream &is, Matrix &mat) {
            for (int i = 0; i < mat.n; ++i)
            for (int j = 0; j < mat.m; ++j)
                is >> mat(i, j);
        return is;
        };

    // Booleans
    bool operator==(const Matrix &matrix) const { // Equal operator
        if (n != matrix.n || m != matrix.m)
            return false;
        for (int i = 0; i < n * m; ++i)
            if (mat[i] != matrix.mat[i])
                return false;
        return true;
    }
    bool operator!=(const Matrix &matrix) const { // Not equal operator
        return !(*this == matrix);
    }

    // Mathematical operation
    Matrix &operator=(const Matrix &matrix) { // Assignment operator (copy)
        if (this != &matrix) {
            n = matrix.n;
            m = matrix.m;
            if (n > 0 && m > 0) {
                mat = std::make_unique<double[]>(n * m);
                std::copy(matrix.mat.get(), matrix.mat.get() + n * m, mat.get());
            } else {
                mat = nullptr;
            }
        }
        return *this;
    }

    Matrix &operator*=(const Matrix &matrix) { // Multiplication
        if (m != matrix.n)
            throw std::logic_error("[MATRIX] Dimension mismatch for multiplication");

        Matrix result(n, matrix.m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < matrix.m; ++j) {
                double sum = 0;
                for (int k = 0; k < m; ++k) {
                    sum += (*this)(i, k) * matrix(k, j);
                }
                result(i, j) = sum;
            }
        }
        *this = result;
        return *this;
    }

    Matrix &operator*=(double a) { // Multiply by a constant
        for (int i = 0; i < n * m; ++i)
            mat[i] *= a;
        return *this;
    }
    Matrix &operator+=(const Matrix &matrix){ // Addition
        if (n != matrix.n || m != matrix.m)
            throw std::logic_error("[MATRIX] Dimension mismatch for addition");
        for (int i = 0; i < n * m; ++i)
            mat[i] += matrix.mat[i];
        return *this;
    } 
    Matrix &operator-=(const Matrix &matrix) { // Substraction
        if (n != matrix.n || m != matrix.m)
            throw std::logic_error("[MATRIX] Dimension mismatch for substraction");
        for (int i = 0; i < n * m; ++i)
            mat[i] -= matrix.mat[i];
        return *this;
    }

    void transpose() { // Transpose the matrix
        std::unique_ptr<double[]> newMat(new double[m * n]);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                newMat[j * n + i] = (*this)(i, j);
        mat = std::move(newMat);
        std::swap(n, m);
    }
};
