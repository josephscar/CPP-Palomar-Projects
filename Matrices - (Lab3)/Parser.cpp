#include "MatrixTemplate.hpp"
Matrix<int>* filterDigits(const string& input);
string removeSpaces(const std::string& input);
Matrix<int>* consoleInput(const string& input);
Matrix<int>* createMatrix(int dimension, char name, string data);
Matrix<int>* algebra(const string& input);
 // global, only used for each time we run the program.
#include <map>

map<char, Matrix<int>*> matrixMap;


string removeSpaces(const string& input) {
    string output;
    for (char c : input) {
        if (c != ' ' && c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}') {
            output += c;
        }
    }
    return output;
}
Matrix<int>* consoleInput(const string& input) {
    string output = removeSpaces(input);
    // ouput now looks like: X=matrix or X=A+B or any other algebraic format; no spaces

    if (!isalpha(output[0]) ) {
        throw invalid_argument("Input did not start with a single alphabetical variable name");
    } else if (isalpha(output[1])){
        throw invalid_argument("Variable name is not a single letter");
    }

    // TEST. NEEDS WORK

    if (output.length() == 1){

        auto check = matrixMap.find(output[0]);
        if (check!= matrixMap.end()) {
            return check->second;
        } else {
            throw invalid_argument("Variable name is not found.");
        }
    } else {


    bool algebraic = false;
    for (int i = 2; i < output.length(); i++) {
        if (isalpha(output[i])) {
            algebraic = true;
            cout << "Algebra found!" <<endl;
            break;
            // Do algebra, use many pointers
        }
    }
    if (algebraic){
        cout << "Attempting algebra..." << endl;
        return algebra(output);
    } else {
        return filterDigits(output);
    }
    
    }
}
Matrix<int>* algebra(const string& input){
    string output = removeSpaces(input);
    cout <<"Algebraic expression: " << output << endl;

    char leftMatrixKey = output[0];
    char rightMatrixKey = output[2];

    // Find the matrices in the map;
    Matrix<int>* leftMatrix = matrixMap.find(leftMatrixKey)->second;
    Matrix<int>* rightMatrix = matrixMap.find(rightMatrixKey)->second;
    Matrix<int>* resultMatrix = nullptr;
    
    // Use the overloaded operator+ to add the matrices
    // Note: This creates a new matrix that is the sum of leftMatrix and rightMatrix
    for (char ch : input) {
            switch (ch) {
                case '+':
                    cout << "Addition operation found." << std::endl;
                    resultMatrix = new Matrix<int>(*leftMatrix + *rightMatrix);// Handle addition here
                    break;
                case '*':
                    cout << "Dot product operation found." << std::endl;
                    resultMatrix = new Matrix<int>(*leftMatrix * *rightMatrix);// Handle addition here
                    break;
                case '-':
                    cout << "Subtraction operation found." << std::endl;
                    resultMatrix = new Matrix<int>(*leftMatrix - *rightMatrix);// Handle addition here
                    break;
            }  
        if (resultMatrix != nullptr) {
            break; // Exit loop if an operation was performed
        }
    }
    return createMatrix(resultMatrix->getDimension(), resultMatrix->getName(), resultMatrix->getDataString());
}

Matrix<int>* filterDigits(const string& input) {

    int presetDimension = 1;
    string dataOutput;
    char name = input[0];

    //single digit only
    for (char c : input) {
        if (isdigit(c)) {
            dataOutput.push_back(c);
        } 
        else if (c == ';') {
            presetDimension++;
        }
    } 

    
    if (dataOutput.length() != (presetDimension*presetDimension)) {  
        throw invalid_argument("Dimension mismatch, possible invalid input or nonsquare matrix detected.");
    }

    Matrix<int>* matrix = createMatrix(presetDimension,name, dataOutput);
    return matrix;
    // TODO: MUST be able to handle different Matrix data types. Here we just assume it is an int.
}

// TODO: again, only works for int type.
Matrix<int>* createMatrix(int dimension, char name, string data) {
    Matrix<int>* matrix = new Matrix<int>(dimension);

    matrixMap[name] = matrix;
     // Push to matrix vector for memory
    matrix->setData(data);

    return matrix;
}