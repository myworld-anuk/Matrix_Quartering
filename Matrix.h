#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix 
{
private:
    unsigned int rows;
    unsigned int cols;
    double** data;

    /**
     * Allocates memory for the matrix data
     */
    void allocateMemory();

    /**
     * Deallocates memory for the matrix data
     */
    void deallocateMemory();

public:
    /**
     * Default constructor
     * Initializes an empty matrix
     */
    Matrix();

    /**
     * Parameterized constructor
     * Initializes a matrix with given dimensions and fills it with a specified value
     */
    Matrix(unsigned int rows, unsigned int cols, double fill);

    /**
     * Copy constructor
     * Initializes a matrix as a copy of another matrix
     */
    Matrix(const Matrix& other);

    /**
     * Destructor
     * Deallocates the matrix data
     */
    ~Matrix();

    /**
     * Clears the matrix data and resets dimensions to zero
     */
    void clear();

    /**
     * Assignment operator
     * Assigns the contents of one matrix to another
     */
    Matrix& operator=(const Matrix& other);

    /**
     * Equality operator
     * Checks if two matrices are equal
     * return true if matrices are equal, false otherwise
     */
    bool operator==(const Matrix& other) const;

    /**
     * Inequality operator
     * Checks if two matrices are not equal
     * returns true if matrices are not equal, false otherwise
     */
    bool operator!=(const Matrix& other) const;

    /**
     * Adds another matrix to this matrix
     * returns true if addition is successful, false otherwise
     */
    bool add(const Matrix& other);

    /**
     * Subtracts another matrix from this matrix
     * return true if subtraction is successful, false otherwise
     */
    bool subtract(const Matrix& other);

    /**
     * Gets the number of rows in the matrix
     * return number of rows
     */
    unsigned int num_rows() const { return rows; }

    /**
     * Gets the number of columns in the matrix
     * return Number of columns
     */
    unsigned int num_cols() const { return cols; }

    /**
     * Gets the value at a specified position in the matrix
     * return True if the position is valid, false otherwise
     */
    bool get(unsigned int row, unsigned int col, double& value) const;

    /**
     * Sets the value at a specified position in the matrix
     * return True if the position is valid, false otherwise
     */
    bool set(unsigned int row, unsigned int col, double value);

    /**
     * Multiplies all elements of the matrix by a coefficient
     * param coefficient The coefficient to multiply by
     */
    void multiply_by_coefficient(double coefficient);

    /**
     * Swaps two rows in the matrix
     * return True if the rows are valid and swap is successful, false otherwise
     */
    bool swap_row(unsigned int row1, unsigned int row2);

    /**
     * Transposes the matrix (rows become columns and vice versa)
     */
    void transpose();

    /**
     * Gets a pointer to the specified row in the matrix
     * return Pointer to the row data
     */
    double* get_row(unsigned int row) const;

    /**
     * Gets a pointer to the specified column in the matrix
     * return Pointer to the column data
     */
    double* get_col(unsigned int col) const;

    /**
     * Divides the matrix into four quarters
     * return Pointer to an array of four matrices representing the quarters
     */
    Matrix* quarter() const;
};

std::ostream& operator<<(std::ostream& out, const Matrix& m);

#endif
