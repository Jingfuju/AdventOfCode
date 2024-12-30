//
//  15.hpp
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

Day 15  https://elixirforum.com/t/advent-of-code-2024-day-15/68106/6

 #include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
    ifstream inputFile("/Users/jingfuju/Desktop/Advent of Code/AoC15.txt"); // Open the file (make sure to change the file name/path)
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    vector<vector<char>> grid; // 2D grid (vector of strings)
    vector<int> movementInstructions;
    string line;
    
    // Read the grid part (until an empty line or special delimiter)
    while (getline(inputFile, line) && !line.empty()) {
        std::vector<char> charArray(line.begin(), line.end());
        grid.push_back(charArray);
    }
    unordered_map<char, int> charToInt = {
        {'^', 0},
        {'v', 1},
        {'<', 2},
        {'>', 3}
    };

    // Skip any empty lines or non-grid parts and process the movement instructions
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            // Iterate over each character in the line and map it to an integer
            for (char c : line) {
                movementInstructions.push_back(charToInt[c]);
            }
        }
    }
    inputFile.close(); // Close the file
    
  
    vector<pair<int, int>> directions = {
        { -1, 0 }, // ^ (up)
        { 1, 0 },  // v (down)
        { 0, -1 }, // < (left)
        { 0, 1 }   // > (right)
    };
    
    
    int m = int(grid.size());
    int n = int(grid[0].size());
    
    
    vector<vector<char>> extenddGrid;
    for (int i = 0; i < m; i++) {
        vector<char> row;
        for (int j = 0; j < n; j++) {
            
            if (grid[i][j] == '@') {
                row.push_back('@');
                row.push_back('.');
            }
            if (grid[i][j] == '.') {
                row.push_back('.');
                row.push_back('.');
            }
            if (grid[i][j] == 'O') {
                row.push_back('[');
                row.push_back(']');
            }
            if (grid[i][j] == '#') {
                row.push_back('#');
                row.push_back('#');
            }
        }
        extenddGrid.push_back(row);
    }
    
    
//    std::cout << "extended Grid is as following." << std::endl;
//    for (auto row: extenddGrid) {
//        for (auto item : row) {
//            std::cout << item << " ";
//        }
//        std::cout << std::endl;
//    }
    
    
    std::vector<int> start;
    for (int i = 0; i < extenddGrid.size(); i++) {
        for (int j = 0; j < extenddGrid[0].size(); j++) {
            
            if (extenddGrid[i][j] == '@') {
                start = {i, j};
                break;
            }
        }
    }
    
    int startX = start[0];
    int startY = start[1];
    
    for (auto instruction: movementInstructions) {
        
//        std::cout << std::endl;
//        for (auto row: extenddGrid) {
//            for (auto item : row) {
//                std::cout << item << " ";
//            }
//            std::cout << std::endl;
//        }
        
        startX += directions[instruction].first;
        startY += directions[instruction].second;
        
        if (extenddGrid[startX][startY] == '.') {
            extenddGrid[startX][startY] = '@';
            extenddGrid[startX - directions[instruction].first][startY - directions[instruction].second] = '.';
            continue;
        }
        
        int x1 = startX;
        int y1 = startY;
        
        if (instruction == 2 || instruction == 3) {

            while (extenddGrid[x1][y1] == '[' || extenddGrid[x1][y1] == ']') {
                y1 += directions[instruction].second;
            }
            
            if (extenddGrid[x1][y1] == '#') {
                startY -= directions[instruction].second;
                continue;
            }
            
            if (extenddGrid[x1][y1] == '.') {
                
                while (extenddGrid[x1][y1] != '@') {
                    extenddGrid[x1][y1] = extenddGrid[x1][y1-directions[instruction].second];
                    y1 -= directions[instruction].second;
                }
                extenddGrid[startX][startY] = '@';
                extenddGrid[startX][startY-directions[instruction].second] = '.';
            }
        }
        
        
        if (instruction == 1 || instruction == 0) {
            
            
            stack<std::vector<int>> stack;
            queue<std::vector<int>> queue;
            
            if (extenddGrid[x1][y1] == '#') {
                startX -= directions[instruction].first;
                continue;
            }
            
            bool stucked = false;

            if (extenddGrid[x1][y1] == '[') {
                queue.push({x1, y1});
                queue.push({x1, y1+1});
            }
            
            if (extenddGrid[x1][y1] == ']') {
                queue.push({x1, y1-1});
                queue.push({x1, y1});
            }
            
            while (queue.size() > 0) {
                auto a = queue.front();
                stack.push(a);
                queue.pop();
                auto b = queue.front();
                stack.push(b);
                queue.pop();
                
                if (extenddGrid[a[0]+directions[instruction].first][a[1]] == '#'
                    || extenddGrid[b[0]+directions[instruction].first][b[1]] == '#'
                    ) {
                    stucked = true;
                    break;
                }
                
                
                std::set<std::vector<int>> seen;
                if (extenddGrid[a[0]+directions[instruction].first][a[1]] == '[') {
                    
                    seen.insert({a[0]+directions[instruction].first, a[1]});
                    seen.insert({a[0]+directions[instruction].first, a[1]+1});
                }
                
                if (extenddGrid[a[0]+directions[instruction].first][a[1]] == ']') {
                    seen.insert({a[0]+directions[instruction].first, a[1]-1});
                    seen.insert({a[0]+directions[instruction].first, a[1]});
                }
                
                if (extenddGrid[b[0]+directions[instruction].first][b[1]] == '[') {
                    seen.insert({b[0]+directions[instruction].first, b[1]});
                    seen.insert({b[0]+directions[instruction].first, b[1]+1});
                }
                
                if (extenddGrid[b[0]+directions[instruction].first][b[1]] == ']') {
                    seen.insert({b[0]+directions[instruction].first, b[1]});
                    seen.insert({b[0]+directions[instruction].first, b[1]-1});
                }
                
                for (auto item: seen) {
                    queue.push(item);
                }
                
                
//                if (extenddGrid[a[0]+directions[instruction].first][a[1]] == '[') {
//                    queue.push({a[0]+directions[instruction].first, a[1]});
//                    queue.push({a[0]+directions[instruction].first, a[1]+1});
//                } else if (extenddGrid[a[0]+directions[instruction].first][a[1]] == ']') {
//                    queue.push({a[0]+directions[instruction].first, a[1]-1});
//                    queue.push({a[0]+directions[instruction].first, a[1]});
//                }
//
//                if (extenddGrid[b[0]+directions[instruction].first][b[1]] == '[') {
//                    queue.push({b[0]+directions[instruction].first, b[1]});
//                    queue.push({b[0]+directions[instruction].first, b[1]+1});
//                }
                

            }
            
            if (stucked) {
                startX -= directions[instruction].first;
                continue;
            }
            else {
                
                while (stack.size() > 0) {
//                    std::cout << "stack size: " << stack.size() << endl;
                    auto curr = stack.top();
                    stack.pop();

                    int nextX = curr[0] + directions[instruction].first;
                    extenddGrid[nextX][curr[1]] = extenddGrid[curr[0]][curr[1]];
                    extenddGrid[curr[0]][curr[1]] = '.';
                }
                extenddGrid[startX][startY] = '@';
                extenddGrid[startX-directions[instruction].first][startY] = '.';
            }
        }
    }
    

    long long result = 0;
    for (int i = 0; i < extenddGrid.size(); i++) {
        for (int j = 0; j < extenddGrid[0].size(); j++) {
            if (extenddGrid[i][j] == '[') {
                result += i * 100 + j;
            }
        }
    }
    std::cout << std::endl;
    for (auto row: extenddGrid) {
        for (auto item : row) {
            std::cout << item;
        }
        std::cout << std::endl;
    }
    
    std::cout << "result is : " << result << std::endl;
    

    return 0;
}
   Python   import sys
import z3
import re
import heapq
from collections import defaultdict, Counter, deque
from sympy.solvers.solveset import linsolve
import pyperclip as pc
def pr(s):
    print(s)
    pc.copy(s)
sys.setrecursionlimit(10**6)
DIRS = [(-1,0),(0,1),(1,0),(0,-1)] # up right down left
def ints(s):
    return [int(x) for x in re.findall('-?\d+', s)]

infile = sys.argv[1] if len(sys.argv)>=2 else '15.in'
D = open(infile).read().strip()

G, instrs = D.split('\n\n')
G = G.split('\n')

def solve(G,part2):
    R = len(G)
    C = len(G[0])
    G = [[G[r][c] for c in range(C)] for r in range(R)]
    if part2:
        BIG_G = []
        for r in range(R):
            row = []
            for c in range(C):
                if G[r][c]=='#':
                    row.append('#')
                    row.append('#')
                if G[r][c]=='O':
                    row.append('[')
                    row.append(']')
                if G[r][c]=='.':
                    row.append('.')
                    row.append('.')
                if G[r][c]=='@':
                    row.append('@')
                    row.append('.')
            BIG_G.append(row)
        G = BIG_G
        C *= 2

    for r in range(R):
        for c in range(C):
            if G[r][c] == '@':
                sr,sc = r,c
                G[r][c] = '.'

    r,c = sr,sc
    for inst in instrs:
        if inst == '\n':
            continue
        dr,dc = {'^': (-1,0), '>': (0,1), 'v': (1,0), '<': (0,-1)}[inst]
        #print(r,c,inst)
        rr,cc = r+dr,c+dc
        if G[rr][cc]=='#':
            continue
        elif G[rr][cc]=='.':
            r,c = rr,cc
        elif G[rr][cc] in ['[', ']', 'O']:
            Q = deque([(r,c)])
            SEEN = set()
            ok = True
            while Q:
                rr,cc = Q.popleft()
                if (rr,cc) in SEEN:
                    continue
                SEEN.add((rr,cc))
                rrr,ccc = rr+dr, cc+dc
                if G[rrr][ccc]=='#':
                    ok = False
                    break
                if G[rrr][ccc] == 'O':
                    Q.append((rrr,ccc))
                if G[rrr][ccc]=='[':
                    Q.append((rrr,ccc))
                    assert G[rrr][ccc+1]==']'
                    Q.append((rrr,ccc+1))
                if G[rrr][ccc]==']':
                    Q.append((rrr,ccc))
                    assert G[rrr][ccc-1]=='['
                    Q.append((rrr,ccc-1))
            if not ok:
                continue
            while len(SEEN) > 0:
                for rr,cc in sorted(SEEN):
                    rrr,ccc = rr+dr,cc+dc
                    if (rrr,ccc) not in SEEN:
                        assert G[rrr][ccc] == '.'
                        G[rrr][ccc] = G[rr][cc]
                        G[rr][cc] = '.'
                        SEEN.remove((rr,cc))
            r = r+dr
            c = c+dc

    for r in range(R):
        print(''.join(G[r]))
    ans = 0
    for r in range(R):
        for c in range(C):
            if G[r][c] in ['[', 'O']:
                ans += 100*r+c
    return ans
pr(solve(G, False))
pr(solve(G, True))
