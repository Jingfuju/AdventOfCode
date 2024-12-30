//
//  20.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 20   Part 1
 #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>


int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC20.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    std::vector<std::vector<char>> matrix;
    std::string line;
    while (getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        matrix.push_back(row);
    }
    inputFile.close();
    
    int sr = 0;
    int sc = 0;
    int er = 0;
    int ec = 0;
    
    int m = int(matrix.size());
    int n = int(matrix[0].size());
    
//    for (auto row: matrix) {
//        for (auto c: row) {
//            std::cout << c;
//        }
//        std::cout << std::endl;
//    }
    
    std::vector<std::vector<int>> shortestStepsMatrix(m, std::vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'E') {
                er = i;
                ec = j;
            }
            if (matrix[i][j] == 'S') {
                sr = i;
                sc = j;
                shortestStepsMatrix[i][j] = 0;
            }
            if (matrix[i][j] == '#') {
                shortestStepsMatrix[i][j] = -1;
            }
        }
    }

    std::vector<std::pair<int, int>> directions = {
        {-1, 0},  // Up (decrease row index)
        {0, 1},    // Right (increase column index)
        {1, 0},   // Down (increase row index)
        {0, -1},  // Left (decrease column index)
    };

    std::queue<std::vector<int>> queue;
    std::set<std::vector<int>> seen;
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    int best = 0;
    queue.push({er,ec});
    seen.insert({er,ec});
    
    
    int counter = 0;
    while (!queue.empty()){
        int size = queue.size();
        counter += 1;
        for (int i = 0; i < size; i++) {
            auto curr = queue.front();
            queue.pop();
            int r = curr[0];
            int c = curr[1];
            for (auto dir: directions) {
                int rr = r + dir.first;
                int cc = c + dir.second;
                
                if (isValid(rr, cc) && !seen.contains({rr,cc}) && matrix[rr][cc] != '#') {
                    seen.insert({r,c});
                    queue.push({rr, cc});
                    if (rr == sr && cc == sc) {
                        best = counter;
                    }
                    shortestStepsMatrix[rr][cc] = counter;
                }
            }
        }
    }
    
    std::cout << "best is: " << best << std::endl;
    seen.clear();
    queue = std::queue<std::vector<int>>();
    std::set<std::vector<int>> cheatSet;
    
    queue.push({0, sr,sc});
    for (int head = 0; head < 4; head++) {
        seen.insert({sr,sc, head});
    }
    
    
    
    int result = 0;
    std::unordered_map<int, int> map;
    while (!queue.empty()){
        int size = queue.size();
        
        for (int i = 0; i < size; i++) {
            auto curr = queue.front();
            queue.pop();
            int step = curr[0];
            int r = curr[1];
            int c = curr[2];

            for (int head = 0; head < 4; head++) {
                auto dir = directions[head];
                int rr = r + dir.first;
                int cc = c + dir.second;
                
                if (!isValid(rr, cc)) { continue ;}
                if (seen.contains({rr,cc,head})) { continue; }
                seen.insert({rr,cc, head});
                
                if (matrix[rr][cc] == '#') {

                    int rrr = rr + dir.first;
                    int ccc = cc + dir.second;
                    
                    if (
                        !isValid(rrr, ccc)
                        || shortestStepsMatrix[rrr][ccc] == -1
                        || cheatSet.contains({r, c, rrr, ccc})
                    ) { continue; }
                    
                    cheatSet.insert({r, c, rrr, ccc});
                    int currentBestStep = 2 + step + shortestStepsMatrix[rrr][ccc];
                    if (best > currentBestStep) {
                        map[best-currentBestStep] += 1;
                    }
                } else {
                    queue.push({step+1, rr, cc});
                }
            }
        }
    }
    
    for (auto pair: map) {
        std::cout << "There are " << pair.second << " cheats that save " << pair.first << " picoseconds." << std::endl;
        if (pair.first >= 100) {
            result += pair.second;
        }
    }
    
//
    std::cout << std::endl;
    for (auto row: shortestStepsMatrix) {
        for (auto c: row) {
            std::cout << c << "     ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "result is: " << result << std::endl;
    return 0;
}
   part 2: 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>


int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC20.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    std::vector<std::vector<char>> matrix;
    std::string line;
    while (getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end());
        matrix.push_back(row);
    }
    inputFile.close();
    
    int sr = 0;
    int sc = 0;
    int er = 0;
    int ec = 0;
    
    int m = int(matrix.size());
    int n = int(matrix[0].size());
    
//    for (auto row: matrix) {
//        for (auto c: row) {
//            std::cout << c;
//        }
//        std::cout << std::endl;
//    }
    
    std::vector<std::vector<int>> shortestStepsMatrix(m, std::vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'E') {
                er = i;
                ec = j;
            }
            if (matrix[i][j] == 'S') {
                sr = i;
                sc = j;
                shortestStepsMatrix[i][j] = 0;
            }
            if (matrix[i][j] == '#') {
                shortestStepsMatrix[i][j] = -1;
            }
        }
    }

    std::vector<std::pair<int, int>> directions = {
        {-1, 0},  // Up (decrease row index)
        {0, 1},    // Right (increase column index)
        {1, 0},   // Down (increase row index)
        {0, -1},  // Left (decrease column index)
    };

    std::queue<std::vector<int>> queue;
    std::set<std::vector<int>> seen;
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };
    int best = 0;
    queue.push({er,ec});
    seen.insert({er,ec});
    
    
    int counter = 0;
    while (!queue.empty()){
        int size = queue.size();
        counter += 1;
        for (int i = 0; i < size; i++) {
            auto curr = queue.front();
            queue.pop();
            int r = curr[0];
            int c = curr[1];
            for (auto dir: directions) {
                int rr = r + dir.first;
                int cc = c + dir.second;
                
                if (isValid(rr, cc) && !seen.contains({rr,cc}) && matrix[rr][cc] != '#') {
                    seen.insert({r,c});
                    queue.push({rr, cc});
                    if (rr == sr && cc == sc) {
                        best = counter;
                    }
                    shortestStepsMatrix[rr][cc] = counter;
                }
            }
        }
    }
    
    std::cout << "best is: " << best << std::endl;
    
    
    
    
    seen.clear();
    queue = std::queue<std::vector<int>>();
    std::set<std::vector<int>> cheatSet;
    
    queue.push({0, sr,sc});
    for (int head = 0; head < 4; head++) {
        seen.insert({sr,sc, head});
    }
    
    int result = 0;
    std::unordered_map<int, int> map;
    while (!queue.empty()){
        int size = queue.size();
        
        for (int i = 0; i < size; i++) {
            auto curr = queue.front();
            queue.pop();
            int step = curr[0];
            int r = curr[1];
            int c = curr[2];

            for (int head = 0; head < 4; head++) {
                auto dir = directions[head];
                int rr = r + dir.first;
                int cc = c + dir.second;
                
                if (!isValid(rr, cc)) { continue ;}
                if (seen.contains({rr,cc,head})) { continue; }
                seen.insert({rr,cc, head});
                
                if (matrix[rr][cc] == '#') {

                    int rrr = rr;
                    int ccc = cc;
                    
                    int pi = 20;
                    
                    for (int pass = 1; pass <= pi; pass++) {
                        for (int x = 0; x <= pass; x++) {
                            
                            std::vector<std::vector<int>> next = {
                                {x, pass - x},
                                {-x, pass - x},
                                {x, -(pass-x)},
                                {-x, -(pass-x)}
                            };
                            
                            for (auto item: next) {
                                rrr = r + item[0];
                                ccc = c + item[1];
                                if (
                                    !isValid(rrr, ccc)
                                    || shortestStepsMatrix[rrr][ccc] == -1
                                    || cheatSet.contains({r, c, rrr, ccc})
                                ) { continue; }
                                
                                cheatSet.insert({r, c, rrr, ccc});
                                int currentBestStep = pass + step + shortestStepsMatrix[rrr][ccc];
                                if (best > currentBestStep) {
                                    map[best-currentBestStep] += 1;
                                }
                            }
                        }
                    }
                } else {
                    queue.push({step+1, rr, cc});
                }
            }
        }
    }
    
    for (auto pair: map) {
        std::cout << "There are " << pair.second << " cheats that save " << pair.first << " picoseconds." << std::endl;
        if (pair.first >= 100) {
            result += pair.second;
        }
    }
    std::cout << "result is: " << result << std::endl;
    return 0;
}
