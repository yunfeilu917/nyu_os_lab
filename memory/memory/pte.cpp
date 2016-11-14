//
//  32bit.cpp
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pte.h"


unsigned int pte::getFrameNum() {
    return frame;
}

unsigned int pte::getPresentBit() {
    return present;
}

void pte::setPresentBit() {
    present = 0;
}

void pte::resetPresentBit() {
    present = 1;
}

unsigned int pte::getModifiedBit() {
    return modified;
}

void pte::setModifiedBit() {
    modified = 1;
}

void pte::resetModifiedBit() {
    modified = 0;
}

unsigned int pte::getPagedOutBit() {
    return pagedout;
}

void pte::resetPagedOutBit() {
    pagedout = 0;
}

void pte::setPagedOutBit() {
    pagedout = 1;
}
