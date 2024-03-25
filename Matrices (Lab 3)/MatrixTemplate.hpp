// MatrixTemplate.cpp

// MatrixTemplate.h
#ifndef MATRIX_TEMPLATE_H
#define MATRIX_TEMPLATE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <sstream>
using namespace std;

template<typename T> 


// Pre increment and decrement currently do not work.
class Matrix
{

    private:
        vector<vector<T>> data; // Matrix data 2D vector
        int dimension; // Dimension of the square matrix

    public:

        /**
         * @brief Constructs a square matrix of a given dimension, initialized to zero.
         * 
         * @param d The dimension of the matrix.
         */
        Matrix(int d) : dimension(d), data(d, vector<T>(d, 0)) {} // Construct matrix of dimension d
        ~Matrix() = default; // Vectors utilize automatic memory management
        


        // Friend functions

        /**
         * @brief Pre-increment operator. Increments each element of the matrix by one.
         * 
         * @return Matrix& A reference to the incremented matrix.
         */
        Matrix& operator++() {
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    ++data[i][j]; // Preincrement each cell
                }
            }
            return *this;
        }
        
        /**
         * @brief Pre-decrement operator. Decrements each element of the matrix by one.
         * 
         * @return Matrix& A reference to the decremented matrix.
         */
        Matrix& operator--() {
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    --data[i][j]; // Predecrement each cell
                }
            }
            return *this;
        }

        /**
         * @brief Post-increment operator. Increments each element of the matrix by one.
         * 
         * @param m The matrix to increment.
         * @return Matrix A copy of the original matrix before incrementation.
         */
        friend Matrix operator++(Matrix& m, int) {
            Matrix<T> temp = m; // Make a copy of the current state
            for (int i = 0; i < m.dimension; i++) {
                for (int j = 0; j < m.dimension; j++) {
                    ++temp.data[i][j]; // Increment the original
                }
            }
            return temp; // Return the unmodified copy
        }

        /**
         * @brief Post-decrement operator. Decrements each element of the matrix by one.
         * 
         * @param m The matrix to decrement.
         * @return Matrix A copy of the original matrix before decrementation.
         */
        friend Matrix operator--(Matrix& m, int) {
            Matrix<T> temp = m; // Make a copy of the current state
            for (int i = 0; i < m.dimension; i++) {
                for (int j = 0; j < m.dimension; j++) {
                    --temp.data[i][j]; // Decrement the original
                }
            }
            return temp; // Return the unmodified copy
        }
        
        
        // Matrix overloaded operators implimentations

        /**
         * @brief Adds another matrix to this matrix.
         * 
         * @param rhsMatrix The right-hand side matrix to add.
         * @return Matrix A new matrix representing the sum.
         */
        Matrix operator+(const Matrix& rhsMatrix) const {
            Matrix lhsMatrix(dimension); // Copy the lhs Matrix so as to not manipulate original matrix

            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    // Add each cell of the lhs(the given data) to the rhs
                    lhsMatrix.data[i][j] = data[i][j] + rhsMatrix.data[i][j]; 
                }
            }

            return lhsMatrix;
        }

        /**
         * @brief Subtracts another matrix from this matrix.
         * 
         * @param rhsMatrix The right-hand side matrix to subtract.
         * @return Matrix A new matrix representing the difference.
         */
        Matrix operator-(const Matrix& rhsMatrix) const{
            // Same as addition.
            Matrix lhsMatrix(dimension);
            
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    lhsMatrix.data[i][j] = data[i][j] - rhsMatrix.data[i][j];;
                }
            }

            return lhsMatrix;
        }

        /**
         * @brief Multiplies another matrix with this matrix.
         * 
         * @param rhsMatrix The right-hand side matrix to multiply.
         * @return Matrix A new matrix representing the product.
         */
        Matrix operator*(const Matrix& rhsMatrix) const{
            Matrix returnMatrix(dimension); // Create empty matrix

            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    for (int k = 0; k < dimension; k++) {
                        // Use summation formula for dot product of matrices
                        returnMatrix.data[i][j] += data[i][k] * rhsMatrix.data[k][j];
                    }
                    
                }
            }

            return returnMatrix;
        }

        /**
         * @brief Calculates the transpose of the matrix.
         * 
         * @return Matrix<T> A new matrix representing the transpose.
         */
        Matrix<T> transpose() const {
            Matrix<T> result(dimension); // New empty matrix
            for (int i = 0; i < dimension; ++i) {
                for (int j = 0; j < dimension; ++j) {
                    result.data[i][j] = data[j][i]; // Flip the columns and rows of orginal matrix
                }
            }

            return result;
        }

        /**
         * @brief Raises the matrix to the specified power.
         * 
         * @param n The power to which the matrix is to be raised.
         * @return Matrix<T> A new matrix representing the result.
         */
        Matrix<T> power(unsigned int n) const {
        if (n == 0) {
            Matrix<T> identity(dimension); // New empty matrix
            for (int i = 0; i < dimension; i++) {
                identity.data[i][i] = 1;
            }
            return identity;
        } else if (n == 1) {
            // Return the matrix itself for power 1
            return *this;
        } else {
            Matrix<T> result = *this; // Start with the matrix itself
            Matrix<T> temp = *this;   // Temporary matrix for multiplication
            for (unsigned int i = 1; i < n; i++) {
                // Multiply the result by the matrix for each power
                result = result * temp;
            }
            return result;
        }
    }

        template<typename U>
        friend ostream& operator<<(ostream& os, const Matrix<U>& m);
        // Increment and decrement as friend functions if necessary

    
    /**
     * @brief Sets the data of the matrix.
     * 
     * @param dataInput The 2D vector of data to set in the matrix.
     */
    void setData(vector<vector<int>> dataInput) {
        this->data = dataInput;
    }
    

};

template<typename T>

    /**
     * @brief Stream insertion operator to output the contents of the matrix.
     * 
     * @param os The output stream.
     * @param m The matrix to be output.
     * @return ostream& The output stream.
     */
ostream& operator<<(ostream& os, const Matrix<T>& m){\
            for(int i = 0; i < m.dimension; i++) {
                for(int j = 0; j < m.dimension; j++) {
                    os << m.data[i][j] << " ";
                }
                os << endl;
            }
            return os;
        }




#endif // MATRIX_TEMPLATE_H