//
//  sim.h
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef sim_h
#define sim_h
#include "pager.h"
#include "pte.h"
#include <vector>
class simulation {
    Pager pager;
    vector<int> free_frame;
};

#endif /* sim_h */
