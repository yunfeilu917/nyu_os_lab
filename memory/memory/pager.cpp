//
//  pager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/14/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"
#include <iostream>


FIFOPager::FIFOPager() {
    pageTable.resize(64);
    for (int i = 0; i < 64; i++) {
        pageTable[i] = new Pte();
    }
    frameTable.resize(16);
    for (int i = 0; i < 16; i++) {
        frameTable[i] = 64;
    }
    
}


unsigned int FIFOPager::getFrame() {
    unsigned int temp = pageInMemory.front();
    pageInMemory.erase(pageInMemory.begin());
    pageInMemory.push_back(temp);
    return temp;
    
}

void FIFOPager::update(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
    if (pageInMemory.size() != 16 && std::find(pageInMemory.begin(), pageInMemory.end(), pageTable[pageTableKey]->getFrameNum()) == pageInMemory.end()) {
        pageInMemory.push_back(pageTable[pageTableKey]->getFrameNum());
    }
}

unsigned int SecondChancePager::getFrame() {
    return 0;
}

void SecondChancePager::update(unsigned int protectBit, unsigned int pageTableKey) {
    
}

unsigned int NRUPager::getFrame() {
    return 0;
}

void NRUPager::update(unsigned int protectBit, unsigned int pageTableKey) {
    
}
