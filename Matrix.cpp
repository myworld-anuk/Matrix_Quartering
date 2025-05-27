#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cassert>

// Default constructor
Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

// Parameterized constructor
Matrix::Matrix(unsigned int r, unsigned int c, double fill) : rows(r), cols(c) 
{
    allocateMemory();
    for (unsigned int i = 0; i < rows; ++i) 
    {
        for (unsigned int j = 0; j < cols; ++j) 
        {
            data[i][j] = fill;  // Initialize all elements with the fill value
        }
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other) 
{
    if (this == &other) 
    {
        return;  // does not self-assign
    }
    rows = other.rows;
    cols = other.cols;

    if (rows == 0 || cols == 0) 
    {
        data = nullptr;
        return;
    }

    data = new double*[rows];
    for (unsigned int i = 0; i < rows; i++) 
    {
        data[i] = new double[cols];
        for (unsigned int j = 0; j < cols; j++) 
        {
            data[i][j] = other.data[i][j];  // cretaes a deep copy each element
        }
    }
}

// Allocate memory for the matrix with rows and cols set
void Matrix::allocateMemory()
{
    data = new double*[rows];
    for (unsigned int i = 0; i < rows; ++i) 
    {
        data[i] = new double[cols]();  // Initialize with zero
    }
}

// Deallocate memory for the matrix
void Matrix::deallocateMemory() 
{
    if (data) 
    { // Only deallocate if memory exsists
        for (unsigned int i = 0; i < rows; i++) 
        {
            if (data[i] != nullptr) {
                delete[] data[i];  // Delete each row
                data[i] = nullptr;  // Prevent dangling pointer
            }
        }
        delete[] data;  // Delete the array of pointers
        data = nullptr;
    }
    rows = 0;
    cols = 0;
}

// Destructor
Matrix::~Matrix() 
{
    if (data) 
    {
        for (unsigned int i = 0; i < rows; i++) 
        {
            delete[] data[i];  // Delete each row
            data[i] = nullptr; // Avoid double delete
        }
        delete[] data;  // Delete row pointers
        data = nullptr; // Avoid dangling pointer
    }
}

// Clears the values in the matrix
void Matrix::clear()
{
    deallocateMemory();
    rows = 0;
    cols = 0;
    data = nullptr;
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) 
{
    if (this == &other) 
    {
        return *this;  // avoids self-assignment
    }

    // Deallocate existing memory
    deallocateMemory();

    // copies other's data to rows and cols
    rows = other.rows;
    cols = other.cols;

    if (rows == 0 || cols == 0) 
    {
        data = nullptr;
        return *this;
    }

    allocateMemory();
    for (unsigned int i = 0; i < rows; i++) 
    {
        for (unsigned int j = 0; j < cols; j++) 
        {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

// Equality operator
bool Matrix::operator==(const Matrix& other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        return false; // does not match if different dimensions
    }

    for (unsigned int i = 0; i < rows; ++i) 
    {
        for (unsigned int j = 0; j < cols; ++j) 
        {
            if (data[i][j] != other.data[i][j])
            {
                return false; //data in each cell does not match
            }
        }
    }
    return true;
}

// Inequality operator
bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

// Output stream operator
std::ostream& operator<<(std::ostream& out, const Matrix& m) 
{
    out << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
    
    // Check if the matrix is empty
    if (m.num_rows() == 0 || m.num_cols() == 0) 
    {
        out << "[ ]" << std::endl;
        return out;
    }

    out << "[ ";

    for (unsigned int i = 0; i < m.num_rows(); i++) 
    {
        for (unsigned int j = 0; j < m.num_cols(); j++) 
        {
            double value;

            // Get the value at the current position
            if (m.get(i, j, value)) 
            {
                // small tolerance to avoid printing large floating-point (makes it 0)
                if (std::abs(value) < 1e-10) 
                {
                    value = 0.0;
                }

                out << value << " ";
            }
        }
        // Add a newline and indentation for all rows except the last one
        if (i < m.num_rows() - 1) 
        {
            out << "\n  ";
        }
    }
    out << "]" << std::endl;
    
    return out;
}

// Add another matrix to given matrix
bool Matrix::add(const Matrix& other) 
{
    if (rows != other.rows || cols != other.cols)
    {
        return false; //does not add if different dimensions
    }
    for (unsigned int i = 0; i < rows; i++) 
    {
        for (unsigned int j = 0; j < cols; j++) 
        {
            data[i][j] += other.data[i][j]; //adds the values of each cell
        }
    }
    return true;
}

// Subtract another matrix from given matrix
bool Matrix::subtract(const Matrix& other) {
    if (rows != other.rows || cols != other.cols)
    {
        return false; //does not subtract if different dimensions
    }
    for (unsigned int i = 0; i < rows; i++) 
    {
        for (unsigned int j = 0; j < cols; j++) 
        {
            data[i][j] -= other.data[i][j]; //subtracts the values of each cell
        }
    }
    return true;
}

// Get the value at a specific position
bool Matrix::get(unsigned int row, unsigned int col, double& value) const
{
    if (data == nullptr || row >= rows || col >= cols)
    {
        return false; // out of bounds position or invalid value
    }
    value = data[row][col]; 
    return true;
}

// Set the value at a specific position
bool Matrix::set(unsigned int row, unsigned int col, double value)
{
    if (row >= rows || col >= cols || data == nullptr)
    {
        return false; // out of bounds position or invalid value
    }
    data[row][col] = value;
    return true;
}

// Multiply all elements by a coefficient
void Matrix::multiply_by_coefficient(double coefficient)
{
    // Handle case where matrix is empty or uninitialized
    if (rows == 0 || cols == 0 || data == nullptr)
    {
        return; // No matrix to multiply
    }

    for (unsigned int i = 0; i < rows; ++i) 
    {
        for (unsigned int j = 0; j < cols; ++j)
        {
            data[i][j] *= coefficient; // Multiply each element by the coefficient
        }
    }
}

// Swap two rows in the matrix
bool Matrix::swap_row(unsigned int row1, unsigned int row2)
{
    // Handle empty matrix
    if (rows == 0 || data == nullptr)
    {
        return false;
    }

    // Handle out-of-bounds row indices
    if (row1 >= rows || row2 >= rows)
    {
        return false;
    }

    // Handle self-swap
    if (row1 == row2)
    {
        return true;
    }

    // Swap row pointers
    std::swap(data[row1], data[row2]);

    return true;
}

// Transpose the matrix
void Matrix::transpose()
{
    // Allocate new transposed matrix
    double** new_data = new double*[cols];

    for (unsigned int i = 0; i < cols; i++) 
    {
        new_data[i] = new double[rows]; // Allocate new row

        for (unsigned int j = 0; j < rows; j++) 
        {
            new_data[i][j] = data[j][i];  // Swap values correctly
        }
    }

    // Free old memory before reassigning
    for (unsigned int i = 0; i < rows; i++) 
    {
        delete[] data[i];  // Delete each row
    }
    delete[] data;  // Delete row pointers

    // Assign new transposed matrix
    data = new_data;
    std::swap(rows, cols);  // Swap dimensions
}

// Get a specific row as a new array
double* Matrix::get_row(unsigned int row) const 
{
    if (rows == 0 || data == nullptr) 
    {
        return nullptr;  // No matrix exists
    }

    if (row >= rows) 
    {
        return nullptr;  // Out of bounds row index
    }

    double* row_data = new double[cols];
    for (unsigned int col = 0; col < cols; ++col) 
    {
        row_data[col] = data[row][col];
    }
    return row_data;
}

// Get a specific column as a new array
double* Matrix::get_col(unsigned int col) const 
{
    if (rows == 0 || cols == 0 || data == nullptr) 
    {
        return nullptr;  // No matrix exists
    }

    if (col >= cols) 
    {
        col = 0;  // Default to first column
    }

    double* column = new double[rows];

    for (unsigned int i = 0; i < rows; i++) 
    {
        column[i] = data[i][col]; // Copy each element in the column
    }

    return column;
}

// Quarter the matrix into four smaller matrices
Matrix* Matrix::quarter() const 
{
    if (rows == 0 || cols == 0) 
    {
        return NULL; // No matrix to quarter
    }

    unsigned int new_rows = (rows + 1) / 2; // Round up for odd rows
    unsigned int new_cols = (cols + 1) / 2; // Round up for odd cols

    Matrix* quartered = new Matrix[4]; // Allocate memory for 4 matrices
    quartered[0] = Matrix(new_rows, new_cols, 0.0);
    quartered[1] = Matrix(new_rows, new_cols, 0.0);
    quartered[2] = Matrix(new_rows, new_cols, 0.0);
    quartered[3] = Matrix(new_rows, new_cols, 0.0);

    for (unsigned int i = 0; i < rows; i++) 
    {
        for (unsigned int j = 0; j < cols; j++) 
        {
            bool is_upper_half = (i < new_rows); // Check if in upper half
            bool is_lower_half = (i >= rows - new_rows); // Check if in lower half
            bool is_left_half = (j < new_cols); // Check if in left half
            bool is_right_half = (j >= cols - new_cols); // Check if in right half

            if (is_upper_half && is_left_half) 
            {
                quartered[0].set(i, j, data[i][j]); // Upper left matrix (UL)
            }

            if (is_upper_half && is_right_half) 
            {
                quartered[1].set(i, j - (cols - new_cols), data[i][j]); // Upper right matrix (UR)
            }

            if (is_lower_half && is_left_half) 
            {
                quartered[2].set(i - (rows - new_rows), j, data[i][j]); // Lower left matrix (LL)
            }

            if (is_lower_half && is_right_half) 
            {
                quartered[3].set(i - (rows - new_rows), j - (cols - new_cols), data[i][j]); // Lower right matrix (LR)
            }
        }
    }
    return quartered;
}
