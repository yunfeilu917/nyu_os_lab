//
//  randompager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/17/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

RandomPager::RandomPager() {
    randGenerator = new Random("/Users/yunfeilu/Downloads/lab3_assign/rfile");
}

void RandomPager::setFrameNum(unsigned int num) {
    frameNum = num;
    frameTable.resize(num);
    for (int i = 0; i < num; i++) {
        frameTable[i] = pageSize;
    }
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

