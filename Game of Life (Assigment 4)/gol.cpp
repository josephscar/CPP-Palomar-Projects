#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // Include for system calls like 'cls' and 'Sleep'

using namespace std;

// Global variables defining the grid size
int rows = 30;
int columns = 30;

// Function prototypes
void initialize(vector<vector<string>> &grid);
void printGrid(vector<vector<string>> &grid);
int countNeighbors(vector<vector<string>> &grid, int x, int y);
void updateGrid(vector<vector<string>> &grid);

/**
 * The main function. It runs a simulation of Conway's Game of Life, asking the user
 * for the number of generations to simulate, initializes the grid, and then iteratively
 * updates and prints the grid for each generation.
 */
int main() {
    int generations;
    cout << "How many generations? : ";
    cin >> generations;

    vector<vector<string>> grid;
    initialize(grid);

    for (int xi = 0; xi < generations; xi++) {
        system("cls"); // Clears the console screen
        updateGrid(grid);
        cout << "Generation " << xi + 1 << ":\n";
        printGrid(grid);
        Sleep(100); // Pauses execution for a short period
    }

    return 0;
}

/**
 * Initializes the simulation grid. The user can choose to randomly populate the grid or
 * enter a custom configuration. Additionally, it prints the initial grid to the console.
 * 
 * @param grid The simulation grid, passed by reference.
 */
void initialize(vector<vector<string>> &grid) {
    // Resize grid and fill with default dead cells ('-')
    grid.resize(rows, vector<string>(columns, "-"));
    printGrid(grid);

    cout << "[r] for random grid, [other key] for self input: ";
    string r;
    cin >> r;
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Randomize grid
    if (r == "r" || r == "R") {
        cout << "Randomizing the first generation..." << endl;
        Sleep(500);
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                // Randomly assign cells as alive ('o') or dead ('-')
                grid[row][column] = (rand() % 2 == 0 ? 'o' : '-');
            }
        }
    // Manually input the grid
    } else {
        // Allow the user to manually specify the state of each row in the grid
        for (int row = 0; row < rows; row++) {
            string config = "";
            cout << "Enter initial cells for row " << row + 1 << " [-]dead, [o]alive, [r]randomize row: "; 
            cin >> config;

            for (int column = 0; column < config.length(); column++) {
                // Validate input or randomize if invalid
                if ((config[column] != 'o' && config[column] != '-') || config.length() > rows) {

                    // Randomize the row
                    cout << (config == "r" ? "Randomizing the row" : "Invalid inputs generate a random row.") << endl;
                    Sleep(500);
                    config = "";
                    // Set config to a dead row with "rows" amount of cells; this is an nxn grid so cell per row = # of rows
                    for (int z = 0; z < rows; z++) {
                        config += "-";
                    }

                    // Randomize with 50% cell state
                    for (int cell = 0; cell < config.length(); cell++) {
                        config[cell] = (rand() % 2 == 0 ? 'o' : '-');
                    }
                }
            }

            // Configure the row based on user input or randomization
            for (int column = 0; column < config.length(); column++) {
                grid[row][column] = config[column];
            }

            // Update the grid
            system("cls");
            printGrid(grid);
        }
    }

    // Exit intialization process
    cout << "Initializing simulation..." << endl;
    Sleep(750);
}

/**
 * Prints the current state of the simulation grid to the console.
 * 
 * @param grid The simulation grid, passed by reference.
 */
void printGrid(vector<vector<string>> &grid) {

    // Iterates over the x,y coordinates and prints the grid with spaces in between
    for (int xi = 0; xi < rows; xi++) {
        for (int yj = 0; yj < columns; yj++) {
            cout << grid[xi][yj] << " ";
        }
        cout << endl;
    }
}

/**
 * Counts the alive neighbors around a given cell in the grid.
 * 
 * @param grid The simulation grid, passed by reference.
 * @param x The x-coordinate (row) of the cell.
 * @param y The y-coordinate (column) of the cell.
 * @return The count of alive neighbors.
 */
int countNeighbors(vector<vector<string>> &grid, int x, int y) {

    int count = 0;

    // All neighbors are a pair of coordinates with offsets ranging from -1 to 1.
    // Iterate through all possible offsets and count if there is an alive cell
    for (int xi = -1; xi <= 1; xi++) {
        for (int yj = -1; yj <= 1; yj++) {
            if (xi == 0 && yj == 0) continue; // Skip the cell itself
            int nx = x + xi;
            int ny = y + yj;
            // Check bounds and cell state
            if (nx >= 0 && nx < rows && ny >= 0 && ny < columns && grid[nx][ny] == "o") {
                count++;
            }
        }
    }
    return count;
}

/**
 * Updates the grid to the next generation based on Conway's Game of Life rules.
 * The state of each cell in the next generation depends on its current state and
 * the number of alive neighbors.
 * 
 * @param grid The simulation grid, passed by reference.
 */
void updateGrid(vector<vector<string>> &grid) {
    vector<vector<string>> buffer = grid; // Temporary grid for updates

    for (int xi = 0; xi < rows; xi++) {
        for (int yj = 0; yj < columns; yj++) {
            // Count the neighbors
            int liveNeighbors = countNeighbors(grid, xi, yj);

            if (grid[xi][yj] == "o") {
                // Kill the cell based on under or over population
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    buffer[xi][yj] = "-"; // Cell dies
                }
            } else {
                // Produce a cell if there are exactly 3 neighbors
                if (liveNeighbors == 3) {
                    buffer[xi][yj] = "o"; // Cell becomes alive
                }
            }
        }
    }

    grid = buffer; // Copy the updated state back to the original grid
}
