//
//  randompager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/17/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

RandomPager::RandomPager(unsigned int frameTableSize) {
    pageSize = 64;
    frameNum = frameTableSize;
    pageTable.resize(pageSize);
    for (int i = 0; i < pageSize; i++) {
        pageTable[i] = new Pte();
    }
    frameTable.resize(frameTableSize);
    for (int i = 0; i < frameTableSize; i++) { // set all frames point to 64, which is not a valid address.
        frameTable[i] = pageSize;
    }
    randGenerator = new Random("/Users/yunfeilu/Downloads/lab3_assign/rfile");
}

unsigned int RandomPager::getFrame() {
    unsigned int frame = randGenerator->getRandNum() % frameNum;
    return frame;
}

void RandomPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
    
}

