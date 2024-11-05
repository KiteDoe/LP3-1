#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <cassert>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int numRows, numCols;

public:
    Matrix(int rows, int cols) : numRows(rows), numCols(cols) {
        data.resize(rows, std::vector<int>(cols, 0));
    }

    void setData() {
        std::cout << "Enter elements for " << numRows << "x" << numCols << " matrix:\n";
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    int getNumRows() const { return numRows; }
    int getNumCols() const { return numCols; }

    std::vector<int> getRow(int row) const {
        return data[row];
    }

    std::vector<int> getColumn(int col) const {
        std::vector<int> column(numRows);
        for (int i = 0; i < numRows; ++i) {
            column[i] = data[i][col];
        }
        return column;
    }

    void setElement(int row, int col, int value) {
        data[row][col] = value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (const auto& row : matrix.data) {
            for (int val : row) {
                os << val << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

int dotProduct(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    int dotProduct = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        dotProduct += vec1[i] * vec2[i];
    }
    return dotProduct;
}

void multiplyRowCol(const Matrix& m1, const Matrix& m2, Matrix& product, int row, int col) {
    product.setElement(row, col, dotProduct(m1.getRow(row), m2.getColumn(col)));
}

Matrix multiply(const Matrix& m1, const Matrix& m2) {
    int m = m1.getNumRows();
    int n = m2.getNumCols();
    Matrix product(m, n);
    std::vector<std::future<void>> futures;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            futures.push_back(std::async(std::launch::async, multiplyRowCol, std::cref(m1), std::cref(m2), std::ref(product), i, j));
        }
    }

    for (auto& future : futures) {
        future.get();
    }

    return product;
}

int main() {
    int rows1, cols1, rows2, cols2;

    // Get dimensions and elements for the first matrix
    std::cout << "Enter number of rows and columns for Matrix 1: ";
    std::cin >> rows1 >> cols1;
    Matrix m1(rows1, cols1);
    m1.setData();

    // Get dimensions and elements for the second matrix
    std::cout << "Enter number of rows and columns for Matrix 2: ";
    std::cin >> rows2 >> cols2;
    Matrix m2(rows2, cols2);
    m2.setData();

    // Check if matrix multiplication is possible
    if (cols1 != rows2) {
        std::cerr << "Error: Number of columns in Matrix 1 must match number of rows in Matrix 2 for multiplication.\n";
        return 1;
    }

    // Display the matrices
    std::cout << "Matrix 1:\n" << m1 << std::endl;
    std::cout << "Matrix 2:\n" << m2 << std::endl;

    // Perform matrix multiplication
    Matrix product = multiply(m1, m2);

    // Display the product matrix
    std::cout << "Product Matrix:\n" << product << std::endl;

    return 0;
}
