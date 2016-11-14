//
//  32bit.h
//  memory
//
//  Created by Yunfei Lu on 11/13/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef _2bit_h
#define _2bit_h

class pte  {
    unsigned int present:1;
    unsigned int modified:1;
    unsigned int referenced:1;
    unsigned int pagedout:1;
    unsigned int frame:6;
public:
    unsigned int getFrameNum();
    unsigned int getPresentBit();
    void setPresentBit();
    void resetPresentBit();
    unsigned int getModifiedBit();
    void setModifiedBit();
    void resetModifiedBit();
    unsigned int getPagedOutBit();
    void setPagedOutBit();
    void resetPagedOutBit();
    
};


#endif /* _2bit_h */
