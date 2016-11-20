//
//  nrupager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/17/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"


NRUPager::NRUPager() {
    clock = 0;
    randGenerator = new Random("/Users/yunfeilu/Downloads/lab3_assign/rfile");
}

void NRUPager::setFrameNum(unsigned int num) {
    frameNum = num;
    frameTable.resize(num);
    for (int i = 0; i < num; i++) { // set all frames point to 64, which is not a valid address.
        frameTable[i] = pageSize;
    }
}

unsigned int NRUPager::getFrame() {
    unsigned int frame = 0;
    std::vector<std::vector<unsigned int>> multiLevel;
    multiLevel.resize(4);
    for (int i = 0; i < pageSize; i++) {
        if (pageTable[i]->getPresentBit() == 1) {
            unsigned int r = pageTable[i]->getReferencedBit();
            unsigned int m = pageTable[i]->getModifiedBit();
            if (r == 0 && m == 0) {
                multiLevel[0].push_back(pageTable[i]->getFrameNum());
            } else if (r == 0 && m == 1) {
                multiLevel[1].push_back(pageTable[i]->getFrameNum());
            } else if (r == 1 && m == 0) {
                multiLevel[2].push_back(pageTable[i]->getFrameNum());
            } else {
                multiLevel[3].push_back(pageTable[i]->getFrameNum());
            }
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (multiLevel[i].size() > 0) {
            int rand = randGenerator->getRandNum();
            frame = multiLevel[i][rand % multiLevel[i].size()];
            //frame = multiLevel[i][randGenerator.getRandNum() % multiLevel[i].size()];
            break;
        }
    }
    
    clock ++;
    if (clock == 10) {
        clock = 0;
        for (int i = 0; i < pageSize; i++) {
            pageTable[i]->resetReferencedBit();
        }
    }
    
    return frame;
}

void NRUPager::update_pte(unsigned int protectBit, unsigned int pageTableKey) {
    pageTable[pageTableKey]->setPresentBit();
    if (protectBit == 0) {
        pageTable[pageTableKey]->setReferencedBit();
    }
    else {
        pageTable[pageTableKey]->setReferencedBit();
        pageTable[pageTableKey]->setModifiedBit();
    }
    
}
