#include "MatrixTemplate.hpp"

int main() {

    int d;
    string matrixA, matrixB, matrixC, matrixD;

    cout << "Dimension: ";
    cin >> d;
    cin >> matrixA;

    cout << "A = " << endl;
    Matrix<int> A(d);
    A.setData(matrixA);
    A.getData();

    cout << "B = " << endl;
    cin >> matrixB;
    Matrix<int> B(d);
    B.setData(matrixB);
    B.getData();

    Matrix<int> C(d);
    C = A * B;
    C.getData();

    
    
}