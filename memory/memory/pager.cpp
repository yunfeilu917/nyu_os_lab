//
//  pager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/14/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"
#include <iostream>
Pte* FIFOPager::getFrame() {
    Pte* temp = pageFrameUsed.front();
    pageFrameUsed.erase(pageFrameUsed.begin());
    pageFrameUsed.push_back(temp);
    return temp;
    
}

void FIFOPager::update() {
}
