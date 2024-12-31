//
//  06.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//


- [x] Day 6  Part 1:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main() {
    // Create a vector of vectors to store the grid
    std::vector<std::vector<char>> grid;

    // Open the file
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC6.txt");
    
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // Convert the line (string) into a vector of characters
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    // Close the file
    file.close();

    // Now `grid` contains the 2D array of characters
    // Print the grid to verify
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1} // Left
    };
    
    std::pair<int, int> start = {0, 0};
    
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '^') {
                start = {i, j};
            }
        }
    }
    
    int result = 0;
    
    int i = start.first;
    int j = start.second;
    int mark = 0;
    
    int m = grid.size();
    int n = grid[0].size();
    
    std::set<int> visited;
    visited.contains(i*n+j);
    auto isValid = [&m, &n](int i, int j) {
        return i >= 0 && j >= 0 && i < m && j < n;
    };
    
    int nextX = i + directions[mark].first;
    int nextY = j + directions[mark].second;
    while (true) {
    
        if (!isValid(nextX, nextY)) {
            std::cout << std::endl;
            for (const auto& row : grid) {
                for (char cell : row) {
                    std::cout << cell << " ";
                }
                std::cout << std::endl;
            }
            break;
        }
        
        // rotate
        if (isValid(nextX, nextY) && grid[nextX][nextY] == '#') {
            nextX -= directions[mark].first;
            nextY -= directions[mark].second;
            mark = (mark + 1) % 4;
            nextX += directions[mark].first;
            nextY += directions[mark].second;
        }
    
        while(isValid(nextX, nextY) && grid[nextX][nextY] != '#') {
            
            if (grid[nextX][nextY] != 'X') {
                result += 1;
            }
//            if (!visited.contains(nextX*n+nextY)) {
//                result += 1;
//            }
            grid[nextX][nextY] = 'X';
//            visited.insert(nextX*n+nextY);
            nextX += directions[mark].first;
            nextY += directions[mark].second;
        }
    }
    
    std::cout << "result is : " << result << std::endl;
    return 0;
}


Part 2:
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int main() {
    // Create a vector of vectors to store the grid
    std::vector<std::vector<char>> grid;

    // Open the file
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC6.txt");
    
    if (!file) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        // Convert the line (string) into a vector of characters
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    // Close the file
    file.close();

    // Now `grid` contains the 2D array of characters
    // Print the grid to verify
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1} // Left
    };
    
    std::pair<int, int> start = {0, 0};
    
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '^') {
                start = {i, j};
            }
        }
    }
    
    int result = 0;
    int m = grid.size();
    int n = grid[0].size();
    
    // inbound check
    auto isValid = [&m, &n](int i, int j) {
        return i >= 0 && j >= 0 && i < m && j < n;
    };

    
    for (int row = 0; row < n; row++) {
        
        for (int col = 0; col < m; col++) {
            if (grid[row][col] != '#') {
                grid[row][col] = '#';
                
                int mark = 0;
                std::unordered_map<int, std::set<int>> unordered_map;
                unordered_map[start.first*n+start.second].insert(mark);
                
                int nextX = start.first + directions[mark].first;
                int nextY = start.second + directions[mark].second;
                
                while (true) {
                    
                    if (!isValid(nextX, nextY)) {
                        
//                         Debug
//                        std::cout << std::endl;
//                        for (const auto& row : grid) {
//                            for (char cell : row) {
//                                std::cout << cell << " ";
//                            }
//                            std::cout << std::endl;
//                        }
//                         Debug end
                        break;
                    }
                    
                    
                    
                    // rotate
                    if (isValid(nextX, nextY) && grid[nextX][nextY] == '#') {
                        nextX -= directions[mark].first;
                        nextY -= directions[mark].second;
                        
                        int index = nextX*n+nextY;
                        unordered_map[index].insert(mark);
                        mark = (mark + 1) % 4;
                        unordered_map[index].insert(mark);
                        
                        nextX += directions[mark].first;
                        nextY += directions[mark].second;
                    }
                
                    while(isValid(nextX, nextY) && grid[nextX][nextY] != '#') {
                        int index = nextX*n+nextY;
                        if (unordered_map[index].contains(mark)) {
                            result += 1;
                            grid[row][col] = '.';
                            goto jump;
                        } else {
                            unordered_map[index].insert(mark);
                        }
                        nextX += directions[mark].first;
                        nextY += directions[mark].second;
                    }
                }
                
                // trace back
                jump:grid[row][col] = '.';
            }
        }
    }
    std::cout << "result is : " << result << std::endl;
    return 0;
}

