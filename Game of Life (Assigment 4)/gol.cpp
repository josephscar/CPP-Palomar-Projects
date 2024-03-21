#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;


int rows = 10;
int columns = 10;

void initialize(vector<vector<string>> &grid);
void printGrid(vector<vector<string>> &grid);
int countNeighbors(vector<vector<string>> &grid, int x, int y);
void updateGrid(vector<vector<string>> &grid);

// Initialize the grid with a random setup
void initialize(vector<vector<string>> &grid) {

    grid.resize(rows, vector<string>(columns, "-"));
    printGrid(grid);

    char choice;
    bool rstate = false;
    string r = "";

    cout << "[r] for random grid, [other key] for self input: ";
    cin >> r;

    if (r == "r") {
        cout << "Randomizing the first generation..." << endl;
        Sleep(500);
        for (int row = 0; row < rows; row++) {

            for (int column = 0; column < columns; column++) {

                grid[row][column] = (rand() % 10 == 0? 'o' : '-');
            }
        }

    } else {

        for (int row = 0; row < rows; row++) {
        
            string config = "";
            cout << "Enter intial cells for row " << row + 1 << " [-]dead [o]alive [r]randomize row: "; 
            cin >> config;
            cout << endl;

            srand(static_cast<unsigned int>(time(0)));

            for (int column = 0; column < config.length(); column++) {

                if ((config[column] != 'o' && config[column] != '-') || config.length() > 10){
                    cout << (config[column] == 'r' ? "Randomizing the row" : "Invalid inputs generate a random row.") << endl;
                    Sleep(1000);
                    config = "----------";

                    for (int cell = 0; cell < config.length(); cell++) {
                        config[cell] = (rand() % 2 == 0 ? 'o' : '-');
                    }
                } 

            }

            for (int column = 0; column < config.length(); column++) {
                grid[row][column] = config[column];
            }

            grid.resize(rows, vector<string>(columns, config));
            system("cls");
            printGrid(grid);
        }
    }
    cout << "Initializing simulation." << endl;
    Sleep(1000);

}

// Print the grid
void printGrid(vector<vector<string>> &grid) {
    for (int xi = 0; xi < rows; xi++) {
        for (int yj = 0; yj < columns; yj++) {
            cout << grid[xi][yj] << " ";
        }
        cout << endl;
    }
}

// Count living neighbors
int countNeighbors(vector<vector<string>> &grid, int x, int y) {
    int count = 0;
    
    // Iterate through neighbors by creating combinations of all possible neighbors
    // Use -1 to 1 in order to offset the coordinate location, then check cell state
    for (int xi = -1; xi <= 1; xi++) {
        for (int yj = -1; yj <= 1; yj++) {
            if (xi == 0 && yj == 0) continue; // 0,0 offset means we are at the cell itself, skip this iteration
            int nx = x + xi; 
            int ny = y + yj;

            // Check if the current offset is in bounds of the screen and count if neighbor is alive
            if (nx >= 0 && nx < rows && ny >= 0 && ny < columns && grid[nx][ny] == "o") {
                count++;
            }
        }
    }
    return count;
}

// Update the grid based on the rules
void updateGrid(vector<vector<string>> &grid) {
    vector<vector<string>> buffer = grid; // Copy the current grid

    for (int xi = 0; xi < rows; xi++) {
        for (int yj = 0; yj < columns; yj++) {
            int liveNeighbors = countNeighbors(grid, xi, yj);

            if (grid[xi][yj] == "o") {
                // Rule 1 or 3
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    buffer[xi][yj] = "-";
                }
            } else {
                // Rule 4
                if (liveNeighbors == 3) {
                    buffer[xi][yj] = "o";
                }
            }
        }
    }

    grid = buffer; // Update the grid
}

int main() {
    vector<vector<string>> grid;
    initialize(grid);

    // Simulate for a certain number of steps
    int generations = 10;
    for (int xi = 0; xi < generations; xi++) {
        system("cls");
        updateGrid(grid);
        cout << "Generation " << xi + 1 << ":\n";
        printGrid(grid);
        Sleep(1000);
    }

    return 0;
}


