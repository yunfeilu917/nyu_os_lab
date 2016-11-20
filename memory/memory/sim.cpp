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
    statsUnmaps = statsMaps = statsIn = statsOut = statsZero = totalCost = 0;
    frameNumber = 32;
    pageNum = 64;
    pager = new FIFOPager();
    freeFrame.resize(frameNumber);
    for (int i = 0; i < frameNumber; i++) {
        freeFrame[i] = i;
    }
    instructionNum = 0;
    O = P = F = S = p = f = a = false;
}

void Sim::init(int argc , char* argv[]) {
    if (argc < 3) {
        std::cerr << "Wrong parameter number, should be at least three\n";
        exit(1);
    }
    else {
        int c;
        size_t optLen;
        while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
            switch (c) {
                    // set algorithm
                case 'a':
                    switch (optarg[0]) {
                        case 'r':
                            pager = new RandomPager();
                            break;
                        case 'f':
                            pager = new FIFOPager();
                            break;
                        case 's':
                            pager = new SecondChancePager();
                            break;
                        case 'c':
                            pager = new ClockFPager();
                            break;
                        case 'a':
                            pager = new AgingFPager();
                            break;
                        case 'N':
                            pager = new NRUPager();
                            break;
                        case 'X':
                            pager = new ClockVPager();
                            break;
                        case 'Y':
                            pager = new AgingVPager();
                            break;
                        default:
                            break;
                    }
                    break;
                    // set output options
                case 'o':
                    optLen = strlen(optarg);
                    for (int i = 0; i < optLen; i++) {
                        switch (optarg[i]) {
                            case 'O':
                                O = true;
                                break;
                            case 'P':
                                P = true;
                                break;
                            case 'F':
                                F = true;
                                break;
                            case 'S':
                                S = true;
                                break;
                            case 'p':
                                p = true;
                                break;
                            case 'f':
                                f = true;
                                break;
                            case 'a':
                                a = true;
                                break;
                        }
                    }
                    break;
                    // set number of frame
                case 'f':
                    sscanf(optarg, "%d", &frameNumber);
                    if (frameNumber > 64) {
                        fprintf(stderr, "Too many frames, not supported.\n");
                        exit(2);
                    }
                    pager->setFrameNum(frameNumber);
                    freeFrame.resize(frameNumber);
                    for (int i = 0; i < frameNumber; i++) {
                        freeFrame[i] = i;
                    }
                    break;
            }
        }
        inFile.open(argv[argc - 2]);
        if (!inFile) {
            fprintf(stderr, "Instruction file cannot found.\n");
            exit(3);
        }
    }
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
    statsUnmaps++;
    pager->pageTable[page]->resetPresentBit(); //simply tell it's not available, then check if we need to do the pageout
    if (O) {
        printf("%d: UNMAP%4d%4d\n", instructionNum, pager->frameTable[frame], frame);
    }
    if (pager->pageTable[page]->getModifiedBit() == 1) {
        pager->pageTable[page]->setPagedOutBit();
        pager->pageTable[page]->resetModifiedBit();
        pager->pageTable[page]->resetReferencedBit();
        if (O) {
            printf("%d: OUT  %4d%4d\n", instructionNum, page, frame);
        }
        statsOut++;
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
        if (O) {
            printf("==> inst: %d %d\n", protectBit, pageTableKey);
        }
        if (pager->pageTable[pageTableKey]->getPresentBit() == 0) {
            unsigned int frame = getFrame();
            unmap(frame);
            if (pager->pageTable[pageTableKey] -> getPagedOutBit()) {
                if (O) {
                    printf("%d: IN   %4d%4d\n", instructionNum, pageTableKey, frame);
                }
                statsIn++;
                //pager->pageTable[pageTableKey]->resetPagedOutBit();
            }
            else {
                zero(frame);
                if (O) {
                    printf("%d: ZERO     %4d\n", instructionNum, frame);
                }
                
                statsZero++;
            }
            map(frame, pageTableKey);
            statsMaps++;
            if (O) {
                printf("%d: MAP  %4d%4d\n", instructionNum, pageTableKey, frame);
            }
        }
        pager -> update_pte(protectBit, pageTableKey);
        instructionNum++;
    }

    if (P) {
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
        std::cout << std::endl;
    }
    if (F) {
        for (int i = 0; i < pager->frameTable.size();i++) {
            if (pager->frameTable[i] == pageNum) {
                std::cout <<"* ";
            }
            else std::cout << pager->frameTable[i] <<" ";
        }
        std::cout << std::endl;
    }

    if (S) {
        totalCost = instructionNum + 400 * (statsMaps + statsUnmaps)
        + 3000 * (statsIn + statsOut) + 150 * statsZero;
        
        printf("SUM %d U=%d M=%d I=%d O=%d Z=%d ===> %llu\n",
               instructionNum, statsUnmaps, statsMaps, statsIn, statsOut, statsZero, totalCost);
    }
}


unsigned int Sim::allocateFrameFromFreeList() {
    if (freeFrame.size() == 0) {     //if freeFrame is empty, then just return a max frame num to show there is no open slot in page frame table
        return frameNumber;
    }
    else {
        int frame = freeFrame.front();
        freeFrame.erase(freeFrame.begin());
        return frame;
    }
}

