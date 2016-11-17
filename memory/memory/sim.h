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
    int pageIn;
    int pageOut;
//    int zero;
    int instructionNum;
    int pageNum;
    int m;
    int u;
    
    
public:
    Sim();
    unsigned int getFrame();
    void simulate();
    void init(int,const char*[]);
    void unmap(unsigned int);
    void zero(unsigned int);
    void map(unsigned int, unsigned int);
    
    
};


#endif /* sim_h */
