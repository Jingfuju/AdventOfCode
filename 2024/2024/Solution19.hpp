//
//  Solution19.h
//  2024
//
//  Created by Jingfu Ju on 12/30/24.
//

#ifndef Solution19_H
#define Solution19_H


// Define an abstract base class (ABC) in C++
class SolutionResolver {
public:
    virtual void generateSolution() = 0;
};



class Solution19: public SolutionResolver {
public:
    void generateSolution();
};



#endif
