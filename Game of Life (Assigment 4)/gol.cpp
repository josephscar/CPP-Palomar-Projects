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



int main() {

    int generations;
    cout << "How many generations? : ";
    cin >> generations;

    vector<vector<string>> grid;
    initialize(grid);


    for (int xi = 0; xi < generations; xi++) {
        system("cls");
        updateGrid(grid);
        cout << "Generation " << xi + 1 << ":\n";
        printGrid(grid);
        Sleep(100);
    }

    return 0;
}



void initialize(vector<vector<string>> &grid) {

    grid.resize(rows, vector<string>(columns, "-"));
    printGrid(grid);

    char choice;
    bool rstate = false;
    string r = "";

    cout << "[r] for random grid, [other key] for self input: ";
    cin >> r;
    srand(static_cast<unsigned int>(time(0)));

    if (r == "r" || r == "R") {

        cout << "Randomizing the first generation..." << endl;
        Sleep(500);
        for (int row = 0; row < rows; row++) {

            for (int column = 0; column < columns; column++) {

                grid[row][column] = (rand() % 2 == 0? 'o' : '-');
            }
        }

    } else {

        for (int row = 0; row < rows; row++) {
        
            string config = "";
            cout << "Enter intial cells for row " << row + 1 << " [-]dead, [o]alive, [r]randomize row: "; 
            cin >> config;
            cout << endl;

            for (int column = 0; column < config.length(); column++) {

                if ((config[column] != 'o' && config[column] != '-') || config.length() > rows){
                    cout << (config[column] == 'r' ? "Randomizing the row" : "Invalid inputs generate a random row.") << endl;
                    Sleep(500);
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
    cout << "Initializing simulation..." << endl;
    Sleep(750);

}

void printGrid(vector<vector<string>> &grid) {
    for (int xi = 0; xi < rows; xi++) {
        for (int yj = 0; yj < columns; yj++) {
            cout << grid[xi][yj] << " ";
        }
        cout << endl;
    }
}

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

void updateGrid(vector<vector<string>> &grid) {
    vector<vector<string>> buffer = grid; // Copy the current grid to the buffer

    for (int xi = 0; xi < rows; xi++) {
        for (int yj = 0; yj < columns; yj++) {
            int liveNeighbors = countNeighbors(grid, xi, yj);

            if (grid[xi][yj] == "o") {
                // Kill cell if there are less than 2 or more than 3 neighbors
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    buffer[xi][yj] = "-";
                }
                // Cells simply stay alive if they have 2 neighbors exactly, do nothing
            } else {
                // Produce new cell at empty cell if there are exactly 3 neighbors 
                if (liveNeighbors == 3) {
                    buffer[xi][yj] = "o";
                }
            }

        }
    }

    grid = buffer; // Update the grid
}


