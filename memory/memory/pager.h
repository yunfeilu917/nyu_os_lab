//
//  pager.h
//  memory
//
//  Created by Yunfei Lu on 11/14/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef pager_h
#define pager_h

#include "pte.h"
#include "random.h"
#include <vector>
#include <list>

class  Pager {
public:
    Random randGenerator;
    unsigned int frameNum;
    std::vector<Pte*> pageTable;
    std::vector<unsigned int>frameTable;
    virtual unsigned int getFrame() = 0;
    virtual void update(unsigned int, unsigned int) = 0;
    
};


class FIFOPager: public Pager {
    std::list<unsigned int > pageInMemory;
public:
    unsigned int getFrame();
    void update(unsigned int, unsigned int);
    FIFOPager();
};

class SecondChancePager: public Pager {
    std::vector<Pte *> pageFrameUsed;
public:
    unsigned int getFrame();
    void update(unsigned int, unsigned int);
};

class NRUPager: public Pager {
    std::vector<Pte *> pageFrameUsed;
    int clock; //reset the R bit every 10th page
public:
    unsigned int getFrame();
    void update(unsigned int, unsigned int);
};

class ClockPager: public Pager {
    
};
#endif /* pager_h */
