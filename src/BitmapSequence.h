/***********************************************************************
 
 Copyright (c) 2011,2012, Mike Manh
 ***STEADY LTD http://steadyltd.com ***
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without 
 modification, are permitted provided that the following conditions are met:
 
 *Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 *Redistributions in binary form must reproduce the above copyright notice, 
 this list of conditions and the following disclaimer in the 
 documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************/
#ifndef BitmapSequence_h
#define BitmapSequence_h

#include <string>
#include "ofMain.h"
#include "BaseMovie.h"
#include "ofImage.h"

class BitmapSequence : public BaseMovie{
    
public:
    
    static string ON_PLAY_COMPLETE;
    BitmapSequence();
    BitmapSequence( string inDir );
    void loadDir( string inDir );
    
    virtual void play();
    void stop();
    void gotoAndPlay( int frame );
    void gotoAndStop( int frame );    
    
    void useTime();
    void useFrames();
    void update();
    void render();
    bool hasAlpha;
    bool repeating;
    bool yoyo;
    bool forward;
    
    ~BitmapSequence();
protected:
    vector< ofImage* > images;
    void init();
    void setDimensions();
    void onRelease(int x, int y, int button);
    
    
    bool usingFrames; //vs trying to use time
    bool playing;
    float fps;
    ofDirectory dir;
    float curTime; //in case we ever use time
    int curFrame;
    int totalFrames;
    
private:
    

};

#endif
