//
//  sim.h
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef sim_h
#define sim_h
#include "pager.h"
#include "pte.h"
#include <vector>
#include <fstream>

class Sim {
    std::vector<unsigned int> freeFrame;
    unsigned int allocateFrameFromFreeList();
    bool getNextInstruction(unsigned int&, unsigned int&);
    Pager *pager;
    std::ifstream inFile;
    unsigned int frameNumber;
    int instructionNum;
    int pageNum; // in this lab, is always 64
    int statsUnmaps;
    int statsMaps;
    int statsIn;
    int statsOut;
    int statsZero;
    unsigned long long totalCost;

    bool O,P,F,S,p,f,a;
    
    
public:
    Sim();
    unsigned int getFrame();
    void simulate();
    void init(int,char*[]);
    void unmap(unsigned int);
    void zero(unsigned int);
    void map(unsigned int, unsigned int);
    
    
};


#endif /* sim_h */
