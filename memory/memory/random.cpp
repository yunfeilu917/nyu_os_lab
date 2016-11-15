//
//  random.cpp
//  memory
//
//  Created by Yunfei Lu on 11/15/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#include "random.h"

Random::Random() {
    done = false;
    randNum = 0;
}

Random::Random(const std::string fileName) {
    rfile.open(fileName);
    done = false;
    rfile >> randNum;
}

int Random::getRandNum() {
    int res;
    if (rfile >> res)
        return res;
    else {
        rfile.clear();
        rfile.seekg(0, std::ios::beg);
        rfile >> res;
        rfile >> res;
        return res;
    }
}
