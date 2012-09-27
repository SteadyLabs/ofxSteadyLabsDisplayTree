//
//  SyncedBitmapSequence.cpp
//  emptyExample
//
//  Created by Mike Manh on 9/26/12.
//
//

#include "SyncedBitmapSequence.h"
#include "mpeClientTCP.h"

mpeClientTCP* SyncedBitmapSequence::globalClient;

void SyncedBitmapSequence::setClient(mpeClientTCP *inClient){
    globalClient = inClient;
}

void SyncedBitmapSequence::update(){
    BitmapSequence::update();
    int frameCount = globalClient->getFrameCount();
    int calcedFrame = frameCount - syncStartFrame;
    
        //cout<< "BitmapSequence::update::usingFrames:"<< usingFrames<< "repeating:" << repeating << name <<"\n";
    if ( ! (totalFrames  >= 1 ) ){
        cout<< "BitmapSequence::update::no frames exist:\n";
        return;//if we don't have more than one frames
    }

    if( totalFrames == 1 ){
        curFrame = 0;
        return;
    }
    if ( usingFrames && playing ){
        if ( repeating ){
            if( yoyo ){
                //it's going forward
                if (forward ){
                    curFrame++;
                    if (curFrame >= totalFrames ){
                        forward = false;
                        curFrame = totalFrames-2;//go back
                    }
                }
                else{
                    //it's going back
                    curFrame--;
                    if (curFrame <0 ){
                        forward = true;
                        curFrame = 1; //go forward instead
                    }
                }
            }
            else{
                curFrame = (curFrame + 1 )%totalFrames;
            }
        }
        else{
            curFrame++;
            if ( curFrame >= totalFrames ){
                curFrame = totalFrames -1;
                stop();
                dispatchEvent( BitmapSequence::ON_PLAY_COMPLETE , name );
            }
        }
        //cout<< "BitmapSequence::update::1::curFrame:"<< curFrame<< "\n";
    }
    else{
        //umm i dunno, use time?
    }
    
    setDimensions();
}

