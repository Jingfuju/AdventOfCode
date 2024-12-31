//
//  10.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//


- [x]  Day 10
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using std::vector;

int main() {
    // Open the input file
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC10.txt");
    
    // Check if file is opened successfully
    if (!inputFile) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    // A 2D vector to hold the integer values
    std::vector<std::vector<int>> matrix;

    std::string line;
    // Read each line from the file
    while (std::getline(inputFile, line)) {
        std::vector<int> row;
        
        // Process each character in the line
        for (char ch : line) {
            if (ch == '.') {
                row.push_back(-2); // Change '.' to -1
            } else if (std::isdigit(ch)) {
                row.push_back(ch - '0'); // Convert character to integer
            }
        }

        // Add the row to the matrix
        matrix.push_back(row);
    }

    inputFile.close(); // Close the file

    // Print the resulting 2D vector (matrix)
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    
    
    std::vector<std::pair<int, int>> starts;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
                starts.push_back({i, j});
            }
        }
    }
    
    int m = matrix.size();
    int n = matrix[0].size();
    
    std::vector<std::pair<int, int>> directions = {
       {-1, 0},  // Up
       {1, 0},   // Down
       {0, -1},  // Left
       {0, 1}    // Right
   };


        // Create an empty queue
    
    std::queue<std::pair<int, int>> queue;
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    
    
    int result = 0;
    for (const auto& pair: starts) {
        queue.push(pair);
        vector<vector<int>> visited = matrix;
        visited[pair.first][pair.second] = -3;
        
        int score = 0;
        while (queue.size() > 0) {
            
            for(int i = 0; i < queue.size(); i++) {
                
                std::pair<int, int> curr = queue.front();
                queue.pop();
                if (matrix[curr.first][curr.second] == 9) {
                    score += 1;
                }
                
                for (const auto&direct: directions) {
                    int x = curr.first + direct.first;
                    int y = curr.second + direct.second;
    
                    if (isValid(x, y) && matrix[x][y] == matrix[curr.first][curr.second] + 1) {
                        std::cout << "x " << x << " is add to queue.";
                        std::cout << "y " << y << " is add to queue"<< std::endl;
                        queue.push({x, y});
                        visited[x][y] = -3;
                    }
                }
            }
        }
        result += score;
        std::cout << std::endl;
        std::cout << "score is : " << score << std::endl;
        for (const auto& row : visited) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "result is : " << result << std::endl;
    return 0;
}


