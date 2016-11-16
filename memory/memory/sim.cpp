//
//  sim.cpp
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "sim.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>


Sim::Sim() {
    pager = new FIFOPager();
    freeFrame.resize(16);
    for (int i = 0; i < 16; i++) {
        freeFrame[i] = i;
    }
    
    inFile.open("/Users/yunfeilu/Downloads/lab3_assign/in1K4");
}


unsigned int Sim::getFrame() {
    unsigned frame = allocateFrameFromFreeList();
    if (frame > 15) {
        frame = pager->getFrame();
    }
    return frame;
}

bool Sim::getNextInstruction(unsigned int& m, unsigned int& p) { // m stands for modified, p stands for page number
    std::string line;
    getline(inFile, line);
    while (line.find('#') != std::string::npos) {
        getline(inFile, line);
    }
    if (line == "") {
        return false;
    }
    else {
        std::istringstream iss( line );
        iss >> m >> p;
        return true;
    }
}

void Sim::map(unsigned int frame, unsigned int pageTableKey) {
    pager->pageTable[pageTableKey]->setFrameNum(frame);
    pager->frameTable[frame] = pageTableKey;
}


void Sim::zero(unsigned int frame) {
    if (pager->frameTable[frame] == 64) {
        return;
    }
    pager->pageTable[pager->frameTable[frame]]->resetModifiedBit();
    pager->pageTable[pager->frameTable[frame]]->resetPresentBit();
    pager->pageTable[pager->frameTable[frame]]->resetPagedOutBit();
    pager->pageTable[pager->frameTable[frame]]->resetReferencedBit();
    pager->pageTable[pager->frameTable[frame]]->resetFrameNum();
}

void Sim::simulate() {
    unsigned int protectBit = 0;
    unsigned int pageTableKey = 0;
    while (getNextInstruction(protectBit, pageTableKey)) {
        std::cout << protectBit << "\t" <<pageTableKey << ": ";
        if (pager->pageTable[pageTableKey]->getPresentBit() == 0) {
            unsigned int frame = getFrame();
            if (pager->pageTable[pageTableKey] -> getPagedOutBit()) {
                std::cout << "Page In" << std::endl;
            }
            else {
                zero(frame);
            }
            map(frame, pageTableKey);
            std::cout << pageTableKey << "->" << frame;
        }
        std::cout << std::endl;
        pager -> update(protectBit, pageTableKey);
    }
}


unsigned int Sim::allocateFrameFromFreeList() {
    if (freeFrame.size() == 0) {
        return 16;
    }
    else {
        int frame = freeFrame.front();
        freeFrame.erase(freeFrame.begin());
        return frame;
    }
}

