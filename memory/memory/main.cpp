//
//  main.cpp
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include <iostream>
#include <vector>
#include "pte.h"
using namespace std;



class Frame {
    
};

class Pager {
public:
    Frame * allocate_frame();
};

class Sim {
    vector<Frame* > freeFream;
    Frame* allocate_frame_from_free_list() {
        if (freeFream.size() == 0)
            return nullptr;
        else {
            Frame* res = freeFream.front();
            freeFream.erase(freeFream.begin());
            return res;
        }
    }
    int get_next_instruction();
    Pager pager;
    
public:
    Frame* get_frame() {
        Frame* frame = allocate_frame_from_free_list();
        if (frame == nullptr) {
            frame = pager.allocate_frame();
        }
        return frame;
    }
    
    void simulate() {
        while (get_next_instruction()) {
            if (<#condition#>) {
                <#statements#>
            }
        }
    }
};


int main(int argc, const char * argv[]) {
    pte a;
    cout << a.getFrameNum();
    cout << a.getModifiedBit();
    cout << a.getPagedOutBit();
    return 0;
}
