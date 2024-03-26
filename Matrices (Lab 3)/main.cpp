/**
 * @file main.cpp
 * @brief Interface to carry out matrix operations
 * 
 * Program to allow the user to perform a set of simple matrix operations based on various inputs
 * 
 * @author Joseph Scarnecchia
 * @date 2024-03-24
 * @version 1.0
 * 
 */
#include "Parser.cpp"

int main() {

    while (true){
        
    int operation,d;
    string op;
    Matrix<int> A(d), B(d);

    // Ask for dimension and to set up matrix.
    cout << "\nDimension [-1 to quit program]: ";
    cin >> d;
    if (d == -1){
        break;
    }

    // Input matrix data
    cout << "Enter matrix as [a,b;c,d]" << endl;
    cout << "Input Matrix A: ";
    A = setUpMatrix(d);
    cout<< "\nA =\n" << A << endl;

    cout << "Operation [op<num>] or type [list] for operations: ";
    cin >> op;
    while(op == "list"){
        cout << "\n<op1> Add" << endl;
        cout << "<op2> Subtract" << endl;
        cout << "<op3> Multiply (Dot Product)" << endl;
        cout << "<op4> Post / Preincrement" << endl;
        cout << "<op5> Post / Predecrement" << endl;
        cout << "<op6> Transpose" << endl;
        cout << "<op7> Exponential\n" << endl;
        cin >> op;
    }


    operation = op[2] - '0'; 

    cout << "Input Matrix B if necessary." <<endl;
    switch (operation) {
        case 1:
        // Addition
        B = setUpMatrix(d);
        cout<< "B =  " << endl << B << endl;
        cout << A + B << endl;
        break;

        case 2:
        // Subtraction
        B = setUpMatrix(d);
        cout<< "B =  " << endl << B << endl;
        cout << "<output>\n" << A - B << endl;
        break;

        case 3:
        // Multiplication
        B = setUpMatrix(d);
        cout<< "B =  " << endl << B << endl;
        cout <<"<output>\n" << A * B << endl;
        break;
        

        case 4:
        // Post and pre Increment
        char choice;
        cout << "[a] for postincrement, [b] for preincrement: ";
        cin >> choice;

        if (choice = 'a'){
            // Post
            B = A++;
            cout << "<output>\n" << B << endl;
            cout << "<Output post increment>\n" << A << endl;
        } else if (choice = 'b') {
            // Pre
            B = ++A;
            cout << "<output>\n" << B << endl;
        }
        
        break;
        

        case 5:
        // Post and pre Decrement
        char _choice;
        cout << "[a] for postdecrement, [b] for preincrement: ";
        cout << "<Output post decrement>\n" << A << endl;
        cin >> choice;

        if (_choice = 'a'){
            B = A--;
            cout << "<output>\n" << B << endl;
        } else if (_choice = 'b') {
            cout << "<output>\n" << --A << endl;
        }

        break;
        

        case 6:
        // Transpose
        cout << "<output>\n" << A.transpose() << endl;
        break;
        

        case 7:
        // Exponential
        int exp;
        cout << "Exponentiate by: ";
        cin >> exp;
        cout << "<output>\n" <<A.power(exp) << endl;
        break;
        

        default:
        cout << "Invalid operation" << endl;
        break;
    
    }  
    }
    
    cout << "Ending program..." << endl;
    return 0;
    
    
}