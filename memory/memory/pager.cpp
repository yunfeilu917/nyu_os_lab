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

Pte* SecondChancePager::getFrame() {
    while (true) {
        Pte* temp = pageFrameUsed.front();
        if (temp->getReferencedBit() == 0) {
            pageFrameUsed.erase(pageFrameUsed.begin());
            pageFrameUsed.push_back(temp);
            return temp;
        }
        else {
            temp->resetReferencedBit();
            pageFrameUsed.erase(pageFrameUsed.begin());
            pageFrameUsed.push_back(temp);
            continue;
        }
    }
}

void SecondChancePager::update() {
    
}

Pte* NRUPager::getFrame() {
    
}

void NRUPager::update() {
    
}
