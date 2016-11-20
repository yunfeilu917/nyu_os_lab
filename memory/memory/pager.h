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
    virtual void setFrameNum(unsigned int) = 0;
    Random randGenerator;
    unsigned int frameNum;
    unsigned int pageSize;
    std::vector<Pte*> pageTable;
    std::vector<unsigned int>frameTable;
    virtual unsigned int getFrame() = 0;
    virtual void update_pte(unsigned int, unsigned int) = 0;
    Pager();
};

class FIFOPager: public Pager {
    std::list<unsigned int > frameUsed; // store which
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    FIFOPager();

};

class SecondChancePager: public Pager {
    std::list<unsigned int > frameUsed; // store which
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    SecondChancePager();
};

class NRUPager: public Pager {
    int clock;
    Random *randGenerator;
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    NRUPager();
};

class RandomPager: public Pager {
    Random *randGenerator;
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    RandomPager();
};

class ClockFPager: public Pager { // clock algorithm based on the frame
    unsigned int clock;
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    ClockFPager();

};

class ClockVPager: public Pager {
    unsigned int clock;
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    ClockVPager();
};

class AgingFPager: public Pager {
    std::vector<unsigned int> ageTable;
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    AgingFPager();
};

class AgingVPager: public Pager {
    std::vector<unsigned int> ageTable;
public:
    void setFrameNum(unsigned int);
    unsigned int getFrame();
    void update_pte(unsigned int, unsigned int);
    AgingVPager();
};


#endif /* pager_h */
