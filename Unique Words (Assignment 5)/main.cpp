#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

// Function declarations
void check_unique(const string input, vector<char*> &unique_words);
vector<string> split(const string& input);

int main(){
    // Vector to store unique words
    vector<char*> unique_words;
    // Input string
    string input;

    // Main loop for input
    while(true){
        // Prompt user for input
        cout << endl << "Enter word or -1 to end" << endl;
        // Read a line of input
        getline(cin, input);
        // Check if input is "-1" to end the loop
        if (input == "-1"){break;}
        
        // Check for unique words in the input and update unique_words vector
        check_unique(input, unique_words);
        
        // Print unique words
        cout << "Unique words: " << endl;
        for (int i = 0; i < unique_words.size(); i++){
            cout << unique_words[i] << ", ";
        }
    }
    return 0; 
}

// Function to split input string into words
vector<string> split(const string& input) {
    // Vector to store words
    vector<string> words;
    // String stream for input
    istringstream iss(input);
    string word;
    // Loop to extract words from input stream
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

// Function to check for unique words and update unique_words vector
void check_unique(const string input, vector<char*> &unique_words){
    // Split input string into words
    vector<string> words = split(input);

    // Loop through each word in the input
    for (string w : words) {
        // Flag to track if word is found in unique_words
        bool find = false;

        // Check if the word is already in unique_words
        for (char *word : unique_words) {
            // Compare each word with existing words in unique_words
            if (word == w){
                find =  true;
                break;
            }
        }

        // If word is not found in unique_words, add it
        if (!find){
            char* mem = new char[w.length() + 1];
            strcpy(mem, w.c_str());
            unique_words.push_back(mem);
        }
    }
}
