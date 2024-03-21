#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

vector<vector<string>> grid;
int height = 10;
int width = 10;

void initialize();
void printGrid();
int countNeighbors(int x, int y);

// Initialize the grid with a random setup
void initialize() {
    srand(static_cast<unsigned int>(time(0)));
    grid.resize(height, vector<string>(width, "-"));
    // Simple initial pattern
    for (auto& row : grid) {
        generate(row.begin(), row.end(), []() {return rand() % 10 == 0 ? 'o' : '-';});
    }
    printGrid();
}

// Print the grid
void printGrid() {
    for (int xi = 0; xi < height; xi++) {
        for (int yj = 0; yj < width; yj++) {
            cout << grid[xi][yj] << " ";
        }
        cout << endl;
    }
}

// Count living neighbors
int countNeighbors(int x, int y) {
    int count = 0;
    
    // Iterate through neighbors by creating combinations of all possible neighbors
    // Use -1 to 1 in order to offset the coordinate location, then check cell state
    for (int xi = -1; xi <= 1; xi++) {
        for (int yj = -1; yj <= 1; yj++) {
            if (xi == 0 && yj == 0) continue; // 0,0 offset means we are at the cell itself, skip this iteration
            int nx = x + xi; 
            int ny = y + yj;

            // Check if the current offset is in bounds of the screen and count if neighbor is alive
            if (nx >= 0 && nx < height && ny >= 0 && ny < width && grid[nx][ny] == "o") {
                count++;
            }
        }
    }
    return count;
}

// Update the grid based on the rules
void updateGrid() {
    vector<vector<string>> buffer = grid; // Copy the current grid

    for (int xi = 0; xi < height; xi++) {
        for (int yj = 0; yj < width; yj++) {
            int liveNeighbors = countNeighbors(xi, yj);

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
    initialize();

    // Simulate for a certain number of steps
    int generations = 10;
    for (int xi = 0; xi < generations; xi++) {
        system("cls");
        updateGrid();
        cout << "Generation " << xi + 1 << ":\n";
        printGrid();
        Sleep(1000);
    }

    return 0;
}


