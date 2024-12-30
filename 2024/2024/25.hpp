//
//  25.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 25



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Function to read the file and process the grids
vector<vector<vector<char>>> readGridsFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    vector<vector<vector<char>>> grids;  // To store multiple grids
    vector<vector<char>> currentGrid;    // Temporary grid to store each grid's data

    while (getline(file, line)) {
        // If the line is empty, we know it's an empty line separating grids
        if (line.empty()) {
            // If the current grid has data, push it to grids and reset
            if (!currentGrid.empty()) {
                grids.push_back(currentGrid);
                currentGrid.clear();
            }
        } else {
            // Add the line to the current grid
            vector<char> row(line.begin(), line.end());
            currentGrid.push_back(row);
        }
    }

    // Add the last grid (if any) after finishing the file reading
    if (!currentGrid.empty()) {
        grids.push_back(currentGrid);
    }

    return grids;
}

// Function to print a grid for testing
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char ch : row) {
            cout << ch;
        }
        cout << endl;
    }
}

int main() {
    string filename = "/Users/jingfuju/Desktop/Advent of Code/AoC25.txt";  // Replace with your file name

    // Read grids from file
    vector<vector<vector<char>>> grids = readGridsFromFile(filename);

    // Print all grids for testing
    for (size_t i = 0; i < grids.size(); ++i) {
        cout << "Grid " << i + 1 << ":" << endl;
        printGrid(grids[i]);
        cout << endl;
    }
    
    vector<vector<int>> locks;
    vector<vector<int>> keys;
    
    for (auto grid: grids) {
        
        if(grid[0][0] == '#') {
            vector<int> lock;
            for (int j = 0; j < grid[0].size(); j++) {
                for (int i = 0; i < grid.size(); i++) {
                    if (grid[i][j] == '.') {
                        lock.push_back((i-1));
                        break;
                    }
                }
            }
            locks.push_back(lock);
        }
        
        if(grid[0][0] == '.') {
            vector<int> key;
            for (int j = 0; j < grid[0].size(); j++) {
                for (int i = grid.size()-1; i >= 0; i--) {
                    if (grid[i][j] == '.') {
                        key.push_back(grid.size()-i-2);
                        break;
                    }
                }
            }
            keys.push_back(key);
        }
    }
    
    for (auto lock: locks) {
        for(auto item: lock) {
            std::cout << item << ",";
        }
        std::cout << std::endl;
    }
    
    std::cout << "key is" << std::endl;
    for (auto key: keys) {
        for(auto item: key) {
            std::cout << item << ",";
        }
        std::cout << std::endl;
    }
    
    int result = 0;
    for (int i = 0; i < locks.size(); i++) {
        for (int j = 0; j < keys.size(); j++) {
            
            vector<int> lock = locks[i];
            vector<int> key = keys[j];
            
            int counter = 0;
            for (int k = 0; k < 5; k++) {
                if (lock[k] + key[k] <= 5) {
                    counter += 1;
                }
            }
            if (counter == 5) {
                result += 1;
            }
        }
    }
    
    std::cout << "part1 result is: " << result << std::endl;

    return 0;
}



