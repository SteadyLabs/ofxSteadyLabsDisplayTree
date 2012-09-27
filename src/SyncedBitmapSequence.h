//
//  SyncedBitmapSequence.h
//  emptyExample
//
//  Created by Mike Manh on 9/26/12.
//
//

#ifndef __emptyExample__SyncedBitmapSequence__
#define __emptyExample__SyncedBitmapSequence__

#include <iostream>

#include "BitmapSequence.h"
class mpeClientTCP;

class SyncedBitmapSequence : public BitmapSequence {
public:
    
    void update();
    static void setClient( mpeClientTCP *inClient );
    
protected:
    int syncStartFrame; //aka the offset frame;
    
private:
    static mpeClientTCP *globalClient;
    
};

#endif /* defined(__emptyExample__SyncedBitmapSequence__) */
