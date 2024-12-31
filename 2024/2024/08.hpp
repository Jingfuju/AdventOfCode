//
//  08.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//



- [x] Day 8
Part1:  #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>


int main() {
    // File path (replace with your actual file path)
    std::string filePath = "/Users/jingfuju/Desktop/Advent of Code/AoC8.txt";
    
    // Open the file for reading
    std::ifstream file(filePath);
    
    // Check if the file was successfully opened
    if (!file) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return 1;
    }
    
    // Grid to store the map (2D vector)
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(file, line)) {
        // Create a row (vector of characters) from the line and add it to the grid
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    file.close();
    
    
    
    // body
    
    int result = 0;
    std::unordered_map<char, std::vector<std::vector<int>>> map;
//     Example of processing the grid: Find all the 'A' positions;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); j++) {
            int c = grid[i][j];
            if (c !='.') {
                map[c].push_back({i, j});
            }
        }
    }
    
    int m = grid.size();
    int n = grid[0].size();
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    
    std::set<std::vector<int>> visited;
    for (const auto& pair: map) {
        
        std::vector<std::vector<int>> arr2D = pair.second;

        for (int i = 0; i < arr2D.size()-1; i++) {
            for (int j = i+1; j < arr2D.size(); j++) {
                
                int xDistance = arr2D[j][0] - arr2D[i][0];
                int yDistance = arr2D[j][1] - arr2D[i][1];
                
                
                int leftX = arr2D[i][0] - xDistance;
                int leftY = arr2D[i][1] - yDistance;
            
                
                int rightX = arr2D[j][0] + xDistance;
                int rightY = arr2D[j][1] + yDistance;
                
            
                if (!visited.contains({leftX, leftY}) && isValid(leftX, leftY)) {
                    result += 1;
                    visited.insert({leftX, leftY});
                }
                
              
                if (!visited.contains({rightX, rightY}) && isValid(rightX, rightY)) {
                    result += 1;
                    visited.insert({rightX, rightY});
                }
            }
        }
    }

    std::cout << std::endl;
    std::cout << "result is : " << result << std::endl;
    return 0;
}


Part 2:

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int result = 0;
std::set<std::vector<int>> totalVisited;

std::vector<std::vector<int>> buildBetween(std::vector<std::vector<int>>  vector1, std::vector<std::vector<int>> vector2, int m, int n) {
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    
    std::set<std::vector<int>> visited(vector1.begin(), vector1.end());
    std::vector<std::vector<int>> newVector = vector1;
    
    for (int i = 0; i < vector1.size(); i++) {
        for (int j = 0; j < vector2.size(); j++) {
            if (vector1[i] == vector2[j]) { continue; }
            int xDistance = vector2[j][0] - vector1[i][0];
            int yDistance = vector2[j][1] - vector1[i][1];
            
            
            int x = vector1[i][0] - xDistance;
            int y = vector1[i][1] - yDistance;
            
            while (isValid(x, y)) {
                if (!visited.contains({x, y})) {
                    visited.insert({x, y});
                    newVector.push_back({x, y});
                }
                x = x - xDistance;
                y = y - yDistance;
            }
            
            x = vector2[j][0] + xDistance;
            y = vector2[j][1] + yDistance;
            
            while (isValid(x, y)) {
                if (!visited.contains({x, y})) {
                    visited.insert({x, y});
                    newVector.push_back({x, y});
                }
                x = x + xDistance;
                y = y + yDistance;
            }
        }
    }
    return newVector;
}


int main() {
    // File path (replace with your actual file path)
    std::string filePath = "/Users/jingfuju/Desktop/Advent of Code/AoC8.txt";
    
    // Open the file for reading
    std::ifstream file(filePath);
    
    // Check if the file was successfully opened
    if (!file) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return 1;
    }
    
    // Grid to store the map (2D vector)
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(file, line)) {
        // Create a row (vector of characters) from the line and add it to the grid
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    file.close();
    
    
    
    // body
    std::unordered_map<char, std::vector<std::vector<int>>> map;
//     Example of processing the grid: Find all the 'A' positions;
    for (int i = 0; i < grid.size(); ++i) {
        std::cout << std::endl;
        for (int j = 0; j < grid[0].size(); j++) {
            
            std::cout << grid[i][j] << " ";
            int c = grid[i][j];
            if (c !='.') {
                map[c].push_back({i, j});
            }
        }
    }
    
    
    
    for (const auto& pair: map) {
        
        std::vector<std::vector<int>> arr2D = pair.second;
        std::vector<std::vector<int>> newVector = buildBetween(arr2D, arr2D, grid.size(), grid[0].size());
//        std::vector<std::vector<int>> vector = buildBetween2(arr2D, newVector, grid.size(), grid[0].size());
        
        
        totalVisited.insert(newVector.begin(), newVector.end());
        
        std::set<std::vector<int>> current;
        current.insert(newVector.begin(), newVector.end());
        for (std::vector<int> node: current) {
            std::cout << " " << "(" << node[0] << "," << node[1] << ")"<< std::endl;
            if (grid[node[0]][node[1]] == '.') {
                grid[node[0]][node[1]] = '#';
            }
        }
    }
    
    for (int i = 0; i < grid.size(); ++i) {
        std::cout << std::endl;
        for (int j = 0; j < grid[0].size(); j++) {
            std::cout << grid[i][j] << " ";
        }
    }
    
    result = totalVisited.size();
    std::cout << std::endl;
    std::cout << "result is : " << result << std::endl;
    return 0;
}
