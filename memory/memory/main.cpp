//
//  main.cpp
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include <iostream>
#include <vector>
#include "sim.h"

int main(int argc, char * argv[]) {
    Sim vmm;
    vmm.init(argc, argv);
    vmm.simulate();
    return 0;
}
