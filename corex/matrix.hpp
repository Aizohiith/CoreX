#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <immintrin.h>

namespace CoreX {
    namespace Matrix
    {
        template <typename T>
        class Matrix {
        private:
            size_t rows;               // Number of rows
            size_t cols;               // Number of columns
            std::vector<std::vector<T>> data; // 2D vector to hold matrix data

        public:
            // Constructor to initialize matrix with given size and default value
            Matrix(size_t rows, size_t cols, const T& initialValue = T())
                : rows(rows), cols(cols), data(rows, std::vector<T>(cols, initialValue)) {}

            // Access operator for matrix elements (non-const)
            T& operator()(size_t row, size_t col) {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix indices out of range");
                }
                return data[row][col];
            }

            // Access operator for matrix elements (const version)
            const T& operator()(size_t row, size_t col) const {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix indices out of range");
                }
                return data[row][col];
            }

            // Get number of rows
            size_t numRows() const { return rows; }

            // Get number of columns
            size_t numCols() const { return cols; }

            // Matrix addition
            Matrix<T> operator+(const Matrix<T>& other) const {
                if (rows != other.rows || cols != other.cols) {
                    throw std::invalid_argument("Matrices must have the same dimensions for addition");
                }
                Matrix<T> result(rows, cols);
                for (size_t i = 0; i < rows; ++i) {
                    for (size_t j = 0; j < cols; ++j) {
                        result(i, j) = data[i][j] + other(i, j);
                    }
                }
                return result;
            }

            //// Matrix multiplication with SIMD vectorization
            //Matrix<T> operator*(const Matrix<T>& other) const {
            //    if (cols != other.rows) {
            //        throw std::invalid_argument("Matrices must have compatible dimensions for multiplication");
            //    }
            //    Matrix<T> result(rows, other.cols, 0); // Initialize result matrix with zeros

            //    for (size_t i = 0; i < rows; ++i) {
            //        for (size_t j = 0; j < other.cols; ++j) {
            //            float sum[8] = { 0 }; // Temporary array to store the sum of 8 elements
            //            __m256 sum_vec = _mm256_setzero_ps(); // Initialize sum vector to zero

            //            for (size_t k = 0; k < cols; k += 8) { // Process 8 elements at a time
            //                // Load 8 floats from matrix A and B
            //                __m256 a = _mm256_loadu_ps(&data[i][k]);
            //                __m256 b = _mm256_set1_ps(other.data[k][j]); // Broadcast the element of matrix B

            //                // Multiply and accumulate
            //                sum_vec = _mm256_fmadd_ps(a, b, sum_vec); // sum_vec += a * b
            //            }

            //            // Store the sum back to the temporary array
            //            _mm256_storeu_ps(sum, sum_vec);

            //            // Sum the elements of the temporary array to get the final result
            //            result(i, j) = sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7];
            //        }
            //    }
            //    return result;
            //}
            Matrix<T> operator*(const Matrix<T>& other) const {
                if (cols != other.rows) {
                    throw std::invalid_argument("Matrices must have compatible dimensions for multiplication");
                }

                Matrix<T> result(rows, other.cols, 0); // Initialize result matrix with zeros

                for (size_t i = 0; i < rows; ++i) {
                    for (size_t j = 0; j < other.cols; ++j) {
                        for (size_t k = 0; k < cols; ++k) {
                            result(i, j) += (*this)(i, k) * other(k, j); // Standard matrix multiplication formula
                        }
                    }
                }

                return result;
            }


            // Print the matrix
            void print() const {
                for (const auto& row : data) {
                    for (const auto& elem : row) {
                        std::cout << elem << " ";
                    }
                    std::cout << std::endl;
                }
            }
        };
    }
}