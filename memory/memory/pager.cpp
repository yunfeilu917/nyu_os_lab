//
//  pager.cpp
//  memory
//
//  Created by Yunfei Lu on 11/19/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pager.h"


Pager::Pager() {
    frameNum = 32;
    pageSize = 64;
    pageTable.resize(64);
    for (int i = 0; i < pageSize; i++) {
        pageTable[i] = new Pte();
    }
    frameTable.resize(frameNum);
    for (int i = 0; i < frameNum; i++) { // set all frames point to 64, which is not a valid address.
        frameTable[i] = pageSize;
    }
}
