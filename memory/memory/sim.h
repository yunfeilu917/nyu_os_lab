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
    int frameNumber;
    void map(unsigned int, unsigned int);
    void zero(unsigned int);
    
    
public:
    Sim();
    unsigned int getFrame();
    void simulate();
    void init(int,const char*[]);
    
};


#endif /* sim_h */
