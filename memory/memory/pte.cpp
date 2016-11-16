//
//  pte.cpp
//  memory
//
//  Created by Yunfei Lu on 11/14/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "pte.h"

void Pte::setFrameNum(unsigned int num ) {
    
    frame = num;
}

void Pte::resetFrameNum() {
    frame = 0;
}

unsigned int Pte::getFrameNum() {
    return frame;
}

unsigned int Pte::getPresentBit() {
    return present;
}

void Pte::setPresentBit() {
    present = 1;
}

void Pte::resetPresentBit() {
    present = 0;
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

unsigned int Pte::getReferencedBit() {
    return referenced;
}

void Pte::setReferencedBit() {
    referenced = 1;
}

void Pte::resetReferencedBit() {
    referenced = 0;
}
