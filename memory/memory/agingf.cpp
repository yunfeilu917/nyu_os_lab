//
//  agingf.cpp
//  memory
//
//  Created by Yunfei Lu on 11/18/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

AgingFPager::AgingFPager() {
    ageTable.resize(frameNum);
}

void AgingFPager::setFrameNum(unsigned int num) {
    frameNum = num;
    frameTable.resize(num);
    for (int i = 0; i < num; i++) { // set all frames point to 64, which is not a valid address.
        frameTable[i] = pageSize;
    }
    ageTable.resize(frameNum);
}


unsigned int AgingFPager::getFrame() {
    unsigned minAge = 0xffffffff;
    unsigned int frame = frameNum;
    
    for (int i = 0; i < frameNum; i++) {
        ageTable[i] = (ageTable[i] >> 1) | (pageTable[frameTable[i]]->getReferencedBit() << 31);
        if (ageTable[i] < minAge) {
            frame = i;
            minAge = ageTable[i];
        }
        pageTable[frameTable[i]]->resetReferencedBit();
    }
    ageTable[frame] = 0;
    return frame;
}

void AgingFPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
}

