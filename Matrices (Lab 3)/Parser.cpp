#include "MatrixTemplate.cpp"

/**
 * @brief Creates a matrix from the given dimension and data.
 * 
 * @param dimension The size of the square matrix.
 * @param data The data to be stored in the matrix.
 * @return Matrix<int> The created matrix.
 */

Matrix<int> createMatrix(int d, vector<vector<int>> data);

/**
 * @brief This function sets up a square matrix of size d by calling the parseMatrix function.
 * 
 * @param d The size of the square matrix.
 * @return Matrix<int> The created and initialized matrix.
 */
Matrix<int> setUpMatrix(int d);
/**
 * @brief Splits a string into a vector of substrings (data values), separated by a specified delimiter.
 * 
 * @param str The string to be split.
 * @param delimiter The character used to separate the substrings in the original string.
 * @return vector<string> A vector of substrings that were separated by the specified delimiter.
 */
vector<string> split(const string& str, char delimiter);

/**
 * @brief Splits a string into a vector of substrings (data values), separated by a specified delimiter.
 * 
 * @param str The string to be split.
 * @param delimiter The character used to separate the substrings in the original string.
 * @return vector<string> A vector of substrings that were separated by the specified delimiter.
 */
vector<vector<int>> parseMatrix(const string& matrixStr);


vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


vector<vector<int>> parseMatrix(const string& matrixStr) {
    string trimmedStr = matrixStr.substr(1, matrixStr.size() - 2); // Trim the brackets
    vector<string> rows = split(trimmedStr, ';');
    vector<vector<int>> matrixData;

    for (const auto& rowStr : rows) {
        vector<string> elementStrs = split(rowStr, ',');
        vector<int> row;
        for (const auto& elemStr : elementStrs) {
            row.push_back(stoi(elemStr)); // Convert string to int and add to row
        }
        matrixData.push_back(row); // Add row to matrix
    }

    return matrixData;
}

Matrix<int> setUpMatrix(int d) {
    string input;
    cin >> input;
    vector<vector<int>> inputVector = parseMatrix(input);

    return createMatrix(d, inputVector);
}

Matrix<int> createMatrix(int d, vector<vector<int>> data) {

    Matrix<int>* matrix = new Matrix<int>(d);
    matrix->setData(data);
    return *matrix;
}
