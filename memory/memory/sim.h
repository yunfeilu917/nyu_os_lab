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
    std::vector<Pte* > freeFrame;
    std::vector<Pte* > frameTable; // has value of virtual page
    Pte* allocateFrameFromFreeList();
    bool getNextInstruction(unsigned int&, unsigned int&);
    Pager *pager;
    std::ifstream inFile;
    int frameNumber;
    
    
    
public:
    Pte* getFrame();
    void simulate();
    void init(int,const char*[]);
    
};


#endif /* sim_h */
