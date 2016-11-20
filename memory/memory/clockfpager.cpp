//
//  clockfpager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/17/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

ClockFPager::ClockFPager() {
    clock = 0;
}

void ClockFPager::setFrameNum(unsigned int num) {
    frameNum = num;
    frameTable.resize(num);
    for (int i = 0; i < num; i++) {
        frameTable[i] = pageSize;
    }
}

unsigned int ClockFPager::getFrame() {
    unsigned int frame;
    while (true) {
        if(pageTable[frameTable[clock]]->getReferencedBit() == 0) {
            frame = clock;
            clock++;
            if (clock == frameNum) {
                clock = 0;
            }
            break;
        }
        else {
            pageTable[frameTable[clock]]->resetReferencedBit();
            clock++;
            if (clock == frameNum) {
                clock = 0;
            }
            continue;
        }
    }
    return frame;
}

void ClockFPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
}

