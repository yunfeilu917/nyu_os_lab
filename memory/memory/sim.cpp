//
//  sim.cpp
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "sim.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

//void Sim::init(int argc, const char * argv[]) {
//    if (argc < 3) {
//        std::cerr << "Wrong number of arguments." << std::endl;
//        exit(0);
//    }
//    int c;
//    int optLen;
//    while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
//        switch (c) {
//            case 'a':
//                switch (optarg[0]) {
//                    case 'l':
//                        <#statements#>
//                        break;
//                    case 'r':
//                        break;
//                    case 'f':
//                        break;
//                    case 's':
//                        break;
//                    case 'c':
//                        break;
//                    case 'a':
//                        break;
//                    case 'N':
//                        break;
//                    case 'X':
//                        break;
//                    case 'Y':
//                        break;
//                        
//                    default:
//                        break;
//                }
//                break;
//                // lack of option
//                
//            case 'f':
//                sscanf(optarg, "%d", &frameNumber);
//                
//            default:
//                break;
//        }
//    }
//    
//}

Pte* Sim::getFrame() {
    Pte* frame = allocateFrameFromFreeList();
    if (frame == nullptr) {
        frame = pager->getFrame();
    }
    return frame;
}

bool Sim::getNextInstruction(unsigned int&, unsigned int&) {
    return false;
}

void Sim::simulate() {
    unsigned int protectBit = 0;
    unsigned int pageTableKey = 0;
    while (getNextInstruction(protectBit, pageTableKey)) {
        if (pager->pageTable[pageTableKey]->getPresentBit()) {
            Pte* frame = getFrame();
            if (pager->pageTable[pageTableKey] -> getPagedOutBit()) {
                // pagein
            }
            else {
                //pageout
            }
            //map
        }
        //update ()
    }
}

Pte* Sim::allocateFrameFromFreeList() {
    if (freeFrame.size() == 0) {
        return nullptr;
    }
    else {
        Pte* frame = freeFrame.front();
        freeFrame.erase(freeFrame.begin());
        return frame;
    }
}

