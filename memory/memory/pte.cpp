//
//  pte.cpp
//  memory
//
//  Created by Yunfei Lu on 11/14/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pte.h"


unsigned int Pte::getFrameNum() {
    return frame;
}

unsigned int Pte::getPresentBit() {
    return present;
}

void Pte::setPresentBit() {
    present = 0;
}

void Pte::resetPresentBit() {
    present = 1;
}

unsigned int Pte::getModifiedBit() {
    return modified;
}

void Pte::setModifiedBit() {
    modified = 1;
}

void Pte::resetModifiedBit() {
    modified = 0;
}

unsigned int Pte::getPagedOutBit() {
    return pagedout;
}

void Pte::resetPagedOutBit() {
    pagedout = 0;
}

void Pte::setPagedOutBit() {
    pagedout = 1;
}
