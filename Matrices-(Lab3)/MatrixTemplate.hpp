// MatrixTemplate.cpp

// MatrixTemplate.h
#ifndef MATRIX_TEMPLATE_H
#define MATRIX_TEMPLATE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

template<typename T> // Allows Matrix of any number type (float, double, int)

class Matrix
{

    private:
        vector<vector<T>> data; // Matrix data 2D vector
        int dimension;


    string filterDigits(const string& input) {
        int d = this->dimension;
        string output;

        for (char c : input) {
            if (isdigit(c)) {
                output.push_back(c);
            }
        }

        if (output.length() != (d*d)) {  
            throw invalid_argument("Dimension mismatch");
        }

        return output;
        


}

    public:
        Matrix(int d) : dimension(d), data(d, vector<T>(d, 0)) {} // Construct matrix of dimension d
        ~Matrix() = default; // Vectors utilize automatic memory management
        
        // Matrix overloaded operators implimentations

        Matrix operator+(const Matrix& rhsMatrix) const {
            // Copy the lhs Matrix
            Matrix lhsMatrix(dimension);

            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    lhsMatrix.data[i][j] += rhsMatrix.data[i][j];;
                }
            }

            return lhsMatrix;
        }

        Matrix operator-(const Matrix& rhsMatrix) const{
            // Copy the lhs Matrix
            Matrix lhsMatrix(dimension);
            lhsMatrix.data = this->data;
            
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    lhsMatrix.data[i][j] -= rhsMatrix.data[i][j];;
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
                        returnMatrix.data[i][j] += this->data[i][k] * rhsMatrix.data[k][j];
                    }
                    
                }
            }

            return returnMatrix;
        }

        //
        /*friend ostream& operator<<(ostream& os, const Matrix& m){};


        // Increment and decrement as friend functions if necessary
        friend Matrix operator++(Matrix& m, int){}; // Post-increment
        friend Matrix& operator++(Matrix& m){}; // Pre-increment

        friend Matrix operator--(Matrix& m, int){}; // Post-decrement
        friend Matrix& operator--(Matrix& m){}; // Pre-decrement */

        void setData(string input) {
            int d = this->dimension;
            string filteredData = filterDigits(input);
            // filteredDigits looks like "000000000"

            int dataIndex = 0;
            for (int i = 0; i < d; i++) {
                for (int j = 0; j < d; j++) {
                    this->data[i][j] = (filteredData[dataIndex] - '0');
                    dataIndex++;
                }
            }
        }

        void getData() {
            cout << endl;
            for(int i = 0; i < dimension; i++) {
                for(int j = 0; j < dimension; j++) {
                    cout << data[i][j] << " ";
                }
                cout << endl;
            }
        }
        
    

};






#endif // MATRIX_TEMPLATE_H

