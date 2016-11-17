//
//  fifopager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/16/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

FIFOPager::FIFOPager(unsigned int frameTableSize) {
    pageSize = 64;
    frameNum = 16;
    pageTable.resize(pageSize);
    for (int i = 0; i < pageSize; i++) {
        pageTable[i] = new Pte();
    }
    frameTable.resize(frameTableSize);
    for (int i = 0; i < frameTableSize; i++) {
        frameTable[i] = pageSize;
    }
    
}



unsigned int FIFOPager::getFrame() {
    unsigned int frame = frameUsed.front();
    frameUsed.erase(frameUsed.begin());
    frameUsed.push_back(frame);
    return frame;
    
}



void FIFOPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
    if (frameUsed.size() != frameNum && std::find(frameUsed.begin(), frameUsed.end(), pageTable[pageTableKey]->getFrameNum()) == frameUsed.end()) {
        frameUsed.push_back(pageTable[pageTableKey]->getFrameNum());
    }
}
