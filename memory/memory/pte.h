//
//  pte.h
//  memory
//
//  Created by Yunfei Lu on 11/14/16.
//  Copyright © 2016 Yunfei Lu. All rights reserved.
//

#ifndef pte_h
#define pte_h
class Pte  {
    unsigned int present:1;
    unsigned int modified:1;
    unsigned int referenced:1;
    unsigned int pagedout:1;
    unsigned int frame:6;
public:
    unsigned int getFrameNum();
    void setFrameNum(unsigned int);
    void resetFrameNum();
    unsigned int getPresentBit();
    void setPresentBit();
    void resetPresentBit();
    unsigned int getReferencedBit();
    void setReferencedBit();
    void resetReferencedBit();
    unsigned int getModifiedBit();
    void setModifiedBit();
    void resetModifiedBit();
    unsigned int getPagedOutBit();
    void setPagedOutBit();
    void resetPagedOutBit();
    
    
};


#endif /* pte_h */
