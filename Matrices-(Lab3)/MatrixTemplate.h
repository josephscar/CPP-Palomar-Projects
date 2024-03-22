// MatrixTemplate.h
#ifndef MATRIX_TEMPLATE_H
#define MATRIX_TEMPLATE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T> // Allows Matrix of any number type (float, double, int)

class Matrix
{
    private:
        vector<vector<T>> data; // Matrix data 2D vector
        int dimension;

    public:
        Matrix(int d) : dimension(d), data(d, vector<T>(d, 0)) {} // Construct matrix of dimension d
        ~Matrix() = default; // Vectors utilize automatic memory management
        
        // Matrix overloaded operators implimentations

        Matrix operator+(const Matrix& val) const {

        }
        Matrix operator-(const Matrix& val) const{

        }
        Matrix operator*(const Matrix& val) const{

        }

        //
        friend ostream& operator<<(ostream& os, const Matrix& m);

        // Increment and decrement as friend functions if necessary
        friend Matrix operator++(Matrix& m, int); // Post-increment
        friend Matrix& operator++(Matrix& m); // Pre-increment

        friend Matrix operator--(Matrix& m, int); // Post-decrement
        friend Matrix& operator--(Matrix& m); // Pre-decrement

};






#endif // MATRIX_TEMPLATE_H