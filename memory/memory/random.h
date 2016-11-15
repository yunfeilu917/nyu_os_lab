//
//  random.h
//  memory
//
//  Created by Yunfei Lu on 11/15/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef random_h
#define random_h

#include <fstream>
#include <iostream>

class Random {
    std::ifstream rfile;
    int randNum;
    bool done;
public:
    Random(const std::string);
    Random();
    int getRandNum();
    
};

#endif /* random_h */
