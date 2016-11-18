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
    unsigned int pageSize;
    std::vector<Pte*> pageTable;
    std::vector<unsigned int>frameTable;
    virtual unsigned int getFrame() = 0;
    virtual void update_pte(unsigned int, unsigned int) = 0;
};

class FIFOPager: public Pager {
    std::list<unsigned int > frameUsed; // store which
public:
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    FIFOPager(unsigned int);

};

class SecondChancePager: public Pager {
    std::list<unsigned int > frameUsed; // store which
public:
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    SecondChancePager(unsigned int);
};

class NRUPager: public Pager {
    int clock;
    Random *randGenerator;
public:
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    NRUPager(unsigned int);
};

class RandomPager: public Pager {
    Random *randGenerator;
public:
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    RandomPager(unsigned int);
};

class ClockFPager: public Pager { // clock algorithm based on the frame
    unsigned int clock;
public:
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    ClockFPager(unsigned int);

};
#endif /* pager_h */
