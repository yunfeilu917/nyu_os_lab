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
#include <vector>
#include <unordered_map>

class  Pager {
public:
    
    std::unordered_map<unsigned int, Pte*> pageTable;
    virtual Pte* getFrame() = 0;
    virtual void update() = 0;
    
};


class FIFOPager: public Pager {
    std::vector<Pte * > pageFrameUsed;
public:
    Pte* getFrame();
    void update();
};


#endif /* pager_h */
