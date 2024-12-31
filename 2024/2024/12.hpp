//
//  12.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//


- [x] Day 12

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC12.txt");  // Open the file (change the filename as needed)
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::vector<std::vector<char>> data;  // 2D vector to hold the characters
    
    std::string line;
    while (std::getline(file, line)) {  // Read each line from the file
        std::vector<char> row(line.begin(), line.end());  // Convert the line to a vector of characters
        data.push_back(row);  // Add the row to the 2D vector
    }
    
    // Close the file
    file.close();
    
    // Print the 2D vector (just to verify)
    for (const auto& row : data) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    
    int m = data.size();
    int n = data[0].size();
        
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
    
    
    std::vector<std::pair<int, int>> directions = {
       {-1, 0},  // Up
       {1, 0},   // Down
       {0, -1},  // Left
       {0, 1}    // Right
   };

    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, int> areaMap;
    std::unordered_map<int, int> periMap;
    
    
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >=0 && y < n;
    };
    
    int curr = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (matrix[i][j] == -1) {
                
                queue.push({i, j});
                matrix[i][j] = curr;
                int areaCounter = 0;
                while (queue.size() > 0) {
                    auto node = queue.front();
                    queue.pop();
                    areaCounter += 1;
                    
                    for (auto direct: directions) {
                        int x = node.first + direct.first;
                        int y = node.second + direct.second;
                        
                        if (isValid(x, y) && data[x][y] == data[i][j] && matrix[x][y] != curr) {
                            queue.push({x, y});
                            matrix[x][y] = curr;
                        }
                    }
                }
                areaMap[curr] = areaCounter;
                curr += 1;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            periMap[matrix[i][j]] += 4;
            if (isValid(i, j+1) && matrix[i][j+1] == matrix[i][j]) {
                periMap[matrix[i][j]] -= 2;
            }
            
            if (isValid(i+1, j) && matrix[i+1][j] == matrix[i][j]) {
                periMap[matrix[i][j]] -= 2;
            }
        }
    }
    
    // Print the 2D vector (just to verify)
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "matrix is as following:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
    
    
    int result = 0;
    for (const auto& pair: areaMap) {
        int prei = periMap[pair.first];
        result += prei * pair.second;
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "area is as following:" << std::endl;
    for (const auto& pair : areaMap) {
        std::cout << "key is: " << pair.first << " area size is: " << pair.second << std::endl;
    }
    
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "peri is as following:" << std::endl;
    for (const auto& pair : periMap) {
        std::cout << "key is: " << pair.first << " peri value is: " << pair.second << std::endl;
    }
    
    std::cout << "result is: " << result << std::endl;
    return 0;
}

Part 2:

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <functional>

int main() {
    std::ifstream file("/Users/jingfuju/Desktop/Advent of Code/AoC12.txt");  // Open the file (change the filename as needed)
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    std::vector<std::vector<char>> data;  // 2D vector to hold the characters
    std::string line;
    while (std::getline(file, line)) {  // Read each line from the file
        std::vector<char> row(line.begin(), line.end());  // Convert the line to a vector of characters
        data.push_back(row);  // Add the row to the 2D vector
    }
    file.close();
    
    
    
    // Print the 2D vector (just to verify)
    for (const auto& row : data) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
    
    
    
    int m = int(data.size());
    int n = int(data[0].size());
    
    
    std::vector<std::pair<int, int>> directions = {
       {-1, 0},  // Up
       {1, 0},   // Down
       {0, -1},  // Left
       {0, 1}    // Right
   };
    
    int result = 0;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, int> areaMap;

    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >=0 && y < n;
    };
    
    
    int curr = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (matrix[i][j] == -1) {
                queue.push({i, j});
                matrix[i][j] = curr;
                int areaCounter = 0;
                while (queue.size() > 0) {
                    auto node = queue.front();
                    queue.pop();
                    areaCounter += 1;
                    
                    for (auto direct: directions) {
                        int x = node.first + direct.first;
                        int y = node.second + direct.second;
                        
                        if (isValid(x, y) && data[x][y] == data[i][j] && matrix[x][y] != curr) {
                            queue.push({x, y});
                            matrix[x][y] = curr;
                        }
                    }
                }
                areaMap[curr] = areaCounter;
                curr += 1;
            }
        }
    }
    
    
    std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "area is as following:" << std::endl;
   for (const auto& pair : areaMap) {
       std::cout << "key is: " << pair.first << " area size is: " << pair.second << std::endl;
   }
    
    std::cout << std::endl;
    std::cout << std::endl;
    // Print the 2D vector (just to verify)
    for (const auto& row : matrix) {
        for (const auto& ch : row) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }

    
    std::set<int> seen;
    
    std::unordered_map<int, std::set<std::vector<int>>> outsidePeriMap;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            
            if (seen.contains(matrix[i][j])) { continue; }
            std::set<std::vector<int>> visited;
            
            outsidePeriMap.clear();
            seen.insert(matrix[i][j]);
            
            std::queue<std::pair<int, int>> queue1;
            queue1.push({i, j});
            visited.insert({i, j});
            
            while (queue1.size() > 0) {
                auto node = queue1.front();
                queue1.pop();
            
                for (int k = 0; k < 4; k++) {
                    int x = node.first + directions[k].first;
                    int y = node.second + directions[k].second;
                    
                    if (isValid(x, y)) {
                        if (matrix[x][y] != matrix[i][j]) {
                            if (matrix[i][j] == 4) {
                                std::cout << std::endl;
                            }
                            outsidePeriMap[k].insert({x, y});
                        }
                        
                        if (matrix[x][y] == matrix[i][j] && !visited.contains({x, y})) {
                            queue1.push({x, y});
                            visited.insert({x, y});
                        }
                    } else {
                        if (matrix[i][j] == 4) {
                            std::cout << std::endl;
                        }
                        outsidePeriMap[k].insert({x, y});
                    }
                }
            }
            
            std::cout << " Node is " << matrix[i][j] << std::endl;
            for (auto pair: outsidePeriMap) {
                std::cout << " Direction is " << pair.first << std::endl;
                for (auto item: pair.second) {
                    std::cout << " ( " << item[0] << "," << item[1] << ")";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            
            int peri = 0;
            for (int i = 0; i < 4; i++) {
//                std::set<std::pair<int, int>> nodes;
                std::set<std::vector<int>> nodes = outsidePeriMap[i];
                std::set<std::vector<int>> isVisited;
                std::queue<std::vector<int>> queue;
                for (auto& node: nodes) {
                    if (!isVisited.contains(node)) {
                        queue.push(node);
                        visited.insert(node);
                        peri += 1;
                        while (queue.size() > 0) {
                            std::vector<int> curr = queue.front();
                            queue.pop();
                            
                            for (int k = 0; k < 4; k++) {
                                int x = curr[0] + directions[k].first;
                                int y = curr[1] + directions[k].second;
                                
                                if (nodes.contains({x, y}) && !isVisited.contains({x, y})) {
                                    queue.push({x, y});
                                    isVisited.insert({x, y});
                                }
                            }
                        }
                    }
                }
            }
            std::cout << "area key " << matrix[i][j] << "'s perimeter is " << peri << std::endl;
            result += areaMap[matrix[i][j]] * peri;
        }
    }
    
    std::cout << "result is: " << result << std::endl;
    return 0;
}
