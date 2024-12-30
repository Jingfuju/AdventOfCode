//
//  16.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 16

- [x]  普通的Queue不可以，这题目要一直保持最小的哦， 不然大case会有bug， 答案会too high
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>




int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC16.txt");
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
    
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 'E') {
                er = i;
                ec = j;
            }
            if (matrix[i][j] == 'S') {
                sr = i;
                sc = j;
            }
        }
    }

    int m = int(matrix.size());
    int n = int(matrix[0].size());
    
    
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> queue;
    std::set<std::vector<int>> seen;
    int score = 0;
    int head = 1;
    int result = 0;

    std::vector<std::pair<int, int>> directions = {
        {-1, 0},  // Up (decrease row index)
        {0, 1},    // Right (increase column index)
        {1, 0},   // Down (increase row index)
        {0, -1},  // Left (decrease column index)
        
    };
    
    queue.push({score, sr, sc, head});
    
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };


    while (!queue.empty()){
        auto curr = queue.top();
        queue.pop();
        int score = curr[0];
        int r = curr[1];
        int c = curr[2];
        int head = curr[3];
        
        if (r == er && c == ec) {
            if (result == 0) {
                result = score;
                break;
            }
        }
        
        if (seen.contains({r,c,head})) {
            continue;
        }
        seen.insert({r,c,head});
        
        int rr = r + directions[head].first;
        int cc = c + directions[head].second;
        
        if (isValid(rr, cc) && matrix[rr][cc] != '#') {
            queue.push({score+1, rr, cc, head});
        }
        
        int head1 = ((head+1)%4);
        int head2 = ((head+3)%4);
        queue.push({score+1000, r, c, head1});
        queue.push({score+1000, r, c, head2});
        if (!seen.contains({r,c,head1})) {
            
        }
        if (!seen.contains({r,c,head2})) {
            
        }
    }
    std::cout << "result is: " << result << std::endl;
    return 0;
}

Part 2:  #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <queue>

struct vector_hash {
    template <typename T>
    std::size_t operator () (const std::vector<T>& v) const {
        std::size_t hash = 0;
        for (const T& element : v) {
            // Combine the current hash with the hash of the element
            hash ^= std::hash<T>{}(element) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};


int main() {
    std::ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC16.txt");
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
    
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 'E') {
                er = i;
                ec = j;
            }
            if (matrix[i][j] == 'S') {
                sr = i;
                sc = j;
            }
        }
    }

    int m = int(matrix.size());
    int n = int(matrix[0].size());
    
    
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> queue;
    std::set<std::vector<int>> seen;
    int score = 0;
    int head = 1;
    int result = 0;

    std::vector<std::pair<int, int>> directions = {
        {-1, 0},  // Up (decrease row index)
        {0, 1},    // Right (increase column index)
        {1, 0},   // Down (increase row index)
        {0, -1},  // Left (decrease column index)
        
    };
    
    queue.push({score, sr, sc, head});
    
    auto isValid = [&m, &n](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };

    std::unordered_map<std::vector<int>, int, vector_hash> map1;
    while (!queue.empty()){
        auto curr = queue.top();
        queue.pop();
        int score = curr[0];
        int r = curr[1];
        int c = curr[2];
        int head = curr[3];
        
        if (!map1.contains({r, c, head})) {
            map1[{r, c, head}] = score;
        }
        
        if (r == er && c == ec) {
            if (result == 0) {
                result = score;
            }
        }
        if (seen.contains({r,c,head})) {
            continue;
        }
        seen.insert({r,c,head});
        
        int rr = r + directions[head].first;
        int cc = c + directions[head].second;
        
        if (isValid(rr, cc) && matrix[rr][cc] != '#') {
            queue.push({score+1, rr, cc, head});
        }
        
        int head1 = ((head+1)%4);
        int head2 = ((head+3)%4);
        queue.push({score+1000, r, c, head1});
        queue.push({score+1000, r, c, head2});
    }
    std::cout << "result is: " << result << std::endl;
    
    
    
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> queue2;
    std::set<std::vector<int>> seen2;
    std::unordered_map<std::vector<int>, int, vector_hash> map2;
    
    for (int head = 0; head < 4; head++) {
        queue2.push({0, er, ec, head});
    }
    
    
    while (!queue2.empty()){
        auto curr = queue2.top();
        queue2.pop();
        int score = curr[0];
        int r = curr[1];
        int c = curr[2];
        int head = curr[3];
        
        if (!map2.contains({r, c, head})) {
            map2[{r, c, head}] = score;
        }
        
        if (seen2.contains({r,c,head})) {
            continue;
        }
        seen2.insert({r,c,head});
        
        int rr = r + directions[(head+2)%4].first;
        int cc = c + directions[(head+2)%4].second;
        
        if (isValid(rr, cc) && matrix[rr][cc] != '#') {
            queue2.push({score+1, rr, cc, head});
        }
        
        int head1 = ((head+1)%4);
        int head2 = ((head+3)%4);
        queue2.push({score+1000, r, c, head1});
        queue2.push({score+1000, r, c, head2});
    }
    
    std::set<std::vector<int>> OK;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 4; k++) {
                if(map1.contains({i, j, k}) && map2.contains({i, j, k}) && map1[{i, j, k}] + map2[{i, j, k}] == result) {
                    OK.insert({i, j});
                }
            }
        }
    }
    std::cout << "result 2 is: " << OK.size() << std::endl;
    return 0;
}



