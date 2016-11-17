//
//  secondchancepager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/17/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

//
//  fifopager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/16/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//


SecondChancePager::SecondChancePager(unsigned int frameTableSize) {
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
    
}



unsigned int SecondChancePager::getFrame() {
    unsigned int frame;
    while (true) {
        frame = frameUsed.front();
        frameUsed.erase(frameUsed.begin());
        frameUsed.push_back(frame);
        if (pageTable[frameTable[frame]]->getReferencedBit() == 1 ) {
            pageTable[frameTable[frame]]->resetReferencedBit();
            continue;
        }
        else
            return frame;
    }
    
}



void SecondChancePager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
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
