//
//  clockvpager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/18/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

ClockVPager::ClockVPager(unsigned int frameTableSize) {
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
    clock = 0;
}

unsigned int ClockVPager::getFrame() {
    unsigned int page;
    while (true) {
        if(pageTable[clock]->getPresentBit() == 1) {
            if (pageTable[clock]->getReferencedBit() == 0) {
                page = clock;
                clock++;
                if (clock == pageSize) {
                    clock = 0;
                }
                break;
            }
            else {
                pageTable[clock]->resetReferencedBit();
                clock++;
                if (clock == pageSize) {
                    clock = 0;
                }
                continue;
            }
        }
        
        else {
            clock++;
            if (clock == pageSize) {
                clock = 0;
            }
            continue;
        }
    }
    return pageTable[page]->getFrameNum();
}

void ClockVPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
}

