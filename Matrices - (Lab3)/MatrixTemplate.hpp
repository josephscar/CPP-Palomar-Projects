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

template<typename T> // Allows Matrix of any number type (float, double, int)

class Matrix
{

    private:
        vector<vector<T>> data; // Matrix data 2D vector
        int dimension;
        char variable = '\0'; //

    public:
        Matrix(int d, char n ='\0') : dimension(d), variable(n), data(d, vector<T>(d, 0)) {} // Construct matrix of dimension d
        ~Matrix() = default; // Vectors utilize automatic memory management
        
        // Matrix overloaded operators implimentations
        template<typename U>
        friend ostream& operator<<(ostream& os, const Matrix<U>& m);

        Matrix operator+(const Matrix& rhsMatrix) const {
            // Copy the lhs Matrix
            Matrix lhsMatrix(dimension);

            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    lhsMatrix.data[i][j] = data[i][j] + rhsMatrix.data[i][j];;
                }
            }

            return lhsMatrix;
        }

        Matrix operator-(const Matrix& rhsMatrix) const{
            // Copy the lhs Matrix
            Matrix lhsMatrix(dimension);
            
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    lhsMatrix.data[i][j] = data[i][j] - rhsMatrix.data[i][j];;
                }
            }

            return lhsMatrix;
        }

        Matrix operator*(const Matrix& rhsMatrix) const{
            // Create empty matrix
            Matrix returnMatrix(dimension);

            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    for (int k = 0; k < dimension; k++) {
                        returnMatrix.data[i][j] += data[i][k] * rhsMatrix.data[k][j];
                    }
                    
                }
            }

            return returnMatrix;
        }


        // Increment and decrement as friend functions if necessary
        /*friend Matrix operator++(Matrix& m, int){}; // Post-increment
        friend Matrix& operator++(Matrix& m){}; // Pre-increment

        friend Matrix operator--(Matrix& m, int){}; // Post-decrement
        friend Matrix& operator--(Matrix& m){}; // Pre-decrement */

        void setData(string input) {
            int d = this->dimension;
            // filteredDigits looks like "000000000"
            int dataIndex = 0;
            for (int i = 0; i < d; i++) {
                for (int j = 0; j < d; j++) {
                    this->data[i][j] = (input[dataIndex] - '0');
                    dataIndex++;
                }
            }
        }

    int getDimension() {
        return this->dimension;
    }
    vector<vector<T>> getData(){
        return data;
    }

    string getDataString() {
        ostringstream oss;
        for (const auto& row : data) {
            for (const auto& elem : row) {
                oss << elem;
            }
        }
        return oss.str();
    }


    char getName(){
        return this->variable;
    }
    

};

template<typename T>
ostream& operator<<(ostream& os, const Matrix<T>& m){\
            os << m.variable << " =" << endl;
            for(int i = 0; i < m.dimension; i++) {
                os << "   ";
                for(int j = 0; j < m.dimension; j++) {
                    os << m.data[i][j] << " ";
                }
                os << endl;
            }
            return os;
        }





#endif // MATRIX_TEMPLATE_H

