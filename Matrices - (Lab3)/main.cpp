#include "MatrixTemplate.hpp"
#include "Parser.cpp"

int main() {
   string sentinel;
    int inputCount = 0;
    cout << "\nEnter the matrix variable name and its definition." << endl
        << "\nYou may perform operations afterward using basic algebra notation" << endl
        << "\nALL inputs must start with a variable [X = 1,2;3,4]; Separate rows with a';'\nType a variable with no definition to output its data\n" << endl;

    do{
        cout << "> ";
        getline(cin, sentinel);
        Matrix<int>* matrixPtr = consoleInput(sentinel);
        cout << *matrixPtr <<endl;
        
        //Matrix<int>& matrixRef = *matrices[inputCount];
        //cout << matrixRef << endl;
        inputCount++;


    } while (sentinel != "-1" );

    for (auto& pair : matrixMap) {
        delete pair.second; // pair.second is the pointer to the Matrix
    }
    matrixMap.clear();  


    /*int d;
    string matrixA, matrixB, matrixC, matrixD;

    cout << "Dimension: ";
    cin >> d;
    cin >> matrixA;

    cout << "A = " << endl;
    Matrix<int> A(d);
    A.setData(matrixA);
    A.getDataString();

    cout << "B = " << endl;
    cin >> matrixB;
    Matrix<int> B(d);
    B.setData(matrixB);
    B.getDataString();


    cout << "Matrix C =  " << A + B <<  endl; */
   
    
    return 0;
    
    
}