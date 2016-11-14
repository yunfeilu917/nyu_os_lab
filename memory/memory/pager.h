//
//  Header.h
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include "pte.h"
#include <vector>

class  Pager {
public:
    std::vector<pte> pageTable;
    int frameNumbers;
    virtual int getFrame();
    
};

class FIFOPager: public Pager {
    
};
#endif /* Header_h */
