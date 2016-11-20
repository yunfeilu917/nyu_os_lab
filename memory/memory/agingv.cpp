//
//  agingv.cpp
//  memory
//
//  Created by Yunfei Lu on 11/18/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

//
//  agingf.cpp
//  memory
//
//  Created by Yunfei Lu on 11/18/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"

AgingVPager::AgingVPager() {
    ageTable.resize(pageSize);
}

void AgingVPager::setFrameNum(unsigned int num) {
    frameNum = num;
    frameTable.resize(num);
    for (int i = 0; i < num; i++) { // set all frames point to 64, which is not a valid address.
        frameTable[i] = pageSize;
    }
}

unsigned int AgingVPager::getFrame() {
    unsigned minAge = 0xffffffff;
    unsigned int page = pageSize;
    
    for (int i = 0; i < pageSize; i++) {
        if (pageTable[i]->getPresentBit() == 1) {
            ageTable[i] = (ageTable[i] >> 1) | (pageTable[i]->getReferencedBit() << 31);
            if (ageTable[i] < minAge) {
                page = i;
                minAge = ageTable[i];
            }
            pageTable[i]->resetReferencedBit();
        }
    }
    ageTable[page] = 0;
    return pageTable[page]->getFrameNum();
}

void AgingVPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
}

