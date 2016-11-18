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
    pageIn = 0;
    pageOut = 0;
    frameNumber = 16;
    pageNum = 64;
    m = 0;
    u = 0;
    pager = new ClockFPager(frameNumber);
    freeFrame.resize(frameNumber);
    for (int i = 0; i < frameNumber; i++) {
        freeFrame[i] = i;
    }
    instructionNum = 0;
    inFile.open("/Users/yunfeilu/Downloads/lab3_assign/in1K4");
}


unsigned int Sim::getFrame() {
    unsigned frame = allocateFrameFromFreeList();
    if (frame == frameNumber) { //means there is no open slot, we need to do the page replacement work
        frame = pager->getFrame(); // return me a frame, meanwhile, have to make sure unmap first.
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

void Sim::unmap(unsigned int frame) {
    unsigned int page = pager->frameTable[frame];
    if (page == pager->pageSize) {
        return;
    }
    u++;
    pager->pageTable[page]->resetPresentBit(); //simply tell it's not available, then check if we need to do the pageout
    std::cout << instructionNum<<": UNMAP  "<<pager->frameTable[frame]<<"   "<<frame<<std::endl;
    if (pager->pageTable[page]->getModifiedBit() == 1) {
        pager->pageTable[page]->setPagedOutBit();
        pager->pageTable[page]->resetModifiedBit();
        pager->pageTable[page]->resetReferencedBit();
        std::cout << instructionNum<<": OUT    "<<page<<"  "<<frame<<std::endl;
        pageOut++;
    }
}

void Sim::zero(unsigned int frame) {
    if (pager->frameTable[frame] == pager->pageSize) {  // at the beginning, all frames point to 64, since they are belong to no one
        return;
    }
    unsigned int page = pager->frameTable[frame];
    pager->pageTable[page]->resetModifiedBit();
    pager->pageTable[page]->resetPresentBit();
    pager->pageTable[page]->resetReferencedBit();
    pager->pageTable[page]->resetFrameNum();
}
void Sim::map(unsigned int frame, unsigned int pageTableKey){
    pager->pageTable[pageTableKey]->setFrameNum(frame);
    pager->frameTable[frame] = pageTableKey;
}


void Sim::simulate() {
    unsigned int protectBit = 0;
    unsigned int pageTableKey = 0;
    while (getNextInstruction(protectBit, pageTableKey)) {
        std::cout << "==> inst: "<<protectBit << " " <<pageTableKey << std::endl;
        if (pager->pageTable[pageTableKey]->getPresentBit() == 0) {
            unsigned int frame = getFrame();
            unmap(frame);
            if (pager->pageTable[pageTableKey] -> getPagedOutBit()) {
                std::cout << instructionNum<<": IN      "<<pageTableKey<<"  "<<frame << std::endl;
                pageIn++;
                //pager->pageTable[pageTableKey]->resetPagedOutBit();
            }
            else {
                zero(frame);
                std::cout << instructionNum<<": ZERO"<<"        "<<frame << std::endl;

                
                //zero++;
            }
            map(frame, pageTableKey);
            m++;
            std::cout <<instructionNum<<": MAP     "<<pageTableKey<<"   "<<frame<<std::endl;
        }
        pager -> update_pte(protectBit, pageTableKey);
        instructionNum++;
    }
    std::cout << u << " "<<m <<pageIn << "\t"<< pageOut<< std::endl;
    for (int i = 0; i < pager->pageTable.size(); i++) {
        std::string output;
        if(pager->pageTable[i]->getPresentBit() == 0) {
            if (pager->pageTable[i]->getPagedOutBit() == 0) {
                output = "*";
            }
            else
                output = "#";
        }
        else {
            output = std::to_string(i) + ':';
            if (pager->pageTable[i]->getReferencedBit() == 1) {
                output += 'R';
            }
            else
                output += '-';
            if (pager->pageTable[i]->getModifiedBit() == 1) {
                output += 'M';
            }
            else
                output += '-';
            if (pager->pageTable[i]->getPagedOutBit() == 1) {
                output += 'S';
            }
            else
                output += '-';
        }
        std::cout << output <<" ";
    }
    for (int i = 0; i < pager->frameTable.size();i++) {
        if (pager->frameTable[i] == pageNum) {
            std::cout <<"*" ;
        }
        else std::cout << pager->frameTable[i];
    }
}


unsigned int Sim::allocateFrameFromFreeList() {
    if (freeFrame.size() == 0) {     //if freeFrame is empty, then just return a max frame num to show there is no open slot in page frame table
        return 16;
    }
    else {
        int frame = freeFrame.front();
        freeFrame.erase(freeFrame.begin());
        return frame;
    }
}

