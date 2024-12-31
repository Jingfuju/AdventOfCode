//
//  11.hpp
//  2024
//
//  Created by Jingfu Ju on 12/31/24.
//


- [x]  Day 11


Part 1:

#include <iostream>
#include <sstream>
#include <vector>

int main() {
    // The string you want to split
    std::string str = "64599 31 674832 2659361 1 0 8867 321";

    // A vector to store the split elements
    std::vector<long long> vector;

    // Create a stringstream object with the input string
    std::stringstream ss(str);
    int number;

    // Split the string by spaces and insert into the vector
    while (ss >> number) {
        vector.push_back(number);
    }

    // Print the elements in the vector
    std::cout << "Split elements:" << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    
    
    
    for (int i = 0; i < 25; i++) {
        std::vector<long long> temp;
        for (int j = 0; j < vector.size(); j++) {
            if (vector[j] == 0) {
                temp.push_back(1);
                continue;;
            }
            
            long long number = vector[j];
            int numDigits = (int)log10(number) + 1;
            if (numDigits % 2 == 0) {
                int splitPoint = numDigits / 2;
                int divisor = pow(10, splitPoint);
                long long firstPart = number / divisor;
                long long secondPart = number % divisor;
                temp.push_back(firstPart);
                temp.push_back(secondPart);
                continue;;
            }
            temp.push_back(2024 * vector[j]);
        }
        vector = temp;
    }
    std::cout << "result is : " << vector.size() << std::endl;
    
    return 0;
}


Part 2:   构建了graph 用dictionary，并且每一层进行了压缩。 用不着二维数组，太稀疏了，存储会超；

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

//std::vector<std::vector<long long>> matrix(pow(2, 28), std::vector<long long>(76, 0));
//
//long funcOutOfBound(long long num, int time) {
//    std::vector<long long> vector = {num};
//    long long result = 0;
//    for (int i = 0; i < time; i++) {
//       std::vector<long long> temp;
//       for (int j = 0; j < vector.size(); j++) {
//           if (vector[j] < pow(2, 28) && matrix[vector[j]][i] != 0) {
//               result += matrix[vector[j]][i];
//               continue;
//           }
//
//           if (vector[j] == 0) {
//               temp.push_back(1);
//               continue;;
//           }
//
//           long long number = vector[j];
//           int numDigits = (int)log10(number) + 1;
//           if (numDigits % 2 == 0) {
//               int divisor = pow(10, numDigits / 2);
//               temp.push_back(number / divisor);
//               temp.push_back(number % divisor);
//               continue;;
//           }
//           temp.push_back(2024 * vector[j]);
//       }
//       vector = temp;
//   }
//    return result + vector.size();
//}
//
//
//long func(long long num, int time) {
//
//    if (time == 0) {
//        return 1;
//    }
//
//    if (num == 0) {
//        if (matrix[1][time-1] == 0) {
//            matrix[1][time-1] = func(1, time-1);
//        }
//        return matrix[1][time-1];
//    }
//
//    int digits = (int)log10(num) + 1;
//    if (digits % 2 == 0) {
//        int divisor = pow(10, digits/2);
//        if (matrix[num/divisor][time-1] == 0) {
//            matrix[num/divisor][time-1] = func(num/divisor, time-1);
//        }
//        if (matrix[num%divisor][time-1] == 0) {
//            matrix[num%divisor][time-1] = func(num%divisor, time-1);
//        }
//        return matrix[num/divisor][time-1] + matrix[num % divisor][time-1];
//    }
//
//    if (2024 * num >= pow(2, 28)) {
//        return funcOutOfBound(2024*num, time-1);
//    }
//
//    if (matrix[2024 * num][time-1] == 0) {
//        matrix[2024 * num][time-1] = func(2024 * num, time-1);
//    }
//    return matrix[2024 * num][time-1];
//}



std::vector<long long> func(long long num, std::unordered_map<long long, std::vector<long long>> lookup) {
    
    if (lookup.contains(num)) {
        return lookup[num];
    }
    
    if (num == 0) {
        lookup[0] = {1};
    } else if (std::to_string(num).size()%2 == 0) {
        
        std::string alpha = std::to_string(num);
        int l = int(alpha.size() / 2);
        long long left = std::atoi(alpha.substr(0,l).c_str());
        long long right = std::atoi(alpha.substr(l).c_str());
        lookup[num] = { left, right};
    } else {
        lookup[num] = { num * 2024 };
    }
    return lookup[num];
}



int main() {
    int number;
    
    std::string str = "64599 31 674832 2659361 1 0 8867 321";
    std::stringstream ss(str);
    
    std::vector<int> vector;
    
    while (ss >> number) {
        vector.push_back(number);
    }
    
    
    std::unordered_map<long long, long long> couterMap;
    
    for (long long num: vector) {
        couterMap[num] = 1;
    }
    std::unordered_map<long long, std::vector<long long>> lookup;
    
    for (int k = 0; k < 75; k++) {
        std::unordered_map<long long, long long> tempCouterMap;
        for(const auto&pair: couterMap) {
            std::vector<long long> children = func(pair.first, lookup);
            for (const auto& child: children) {
                tempCouterMap[child] += pair.second;
            }
        }
        couterMap = tempCouterMap;
    }
    
    long long result = 0;
    for (const auto&pair: couterMap) {
        result += pair.second;
    }
    std::cout << "result is : " << result << std::endl;
    return 0;
}
 
