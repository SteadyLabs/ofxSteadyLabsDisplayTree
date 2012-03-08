/***********************************************************************
 
 Copyright (c) 2011,2012, Carrie Kengle
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

#ifndef IOSTouchSprite_h
#define IOSTouchSprite_h

#pragma once
//#include "ofxiPhone.h"
//#include "ofxiPhoneExtras.h"
#include "BaseSprite.h"
#include "BitmapSequence.h"
#include "BitmapSprite.h"
//#include "TouchSprite.h"

typedef enum{
    ROLLOVER_TOUCH,
    ROLLOUT_TOUCH,
    PRESS_TOUCH,
    DEFAULT_TOUCH
}TouchState;


class IOSTouchSprite : public BaseSprite{
    
public:
    static string ON_TOUCHDOWN;
    static string ON_TOUCHMOVED;
    static string ON_TOUCHUP;
    static string ON_TOUCHDOUBLETAP;
    static string ON_TOUCHCANCELED;
    
    IOSTouchSprite();
    IOSTouchSprite( string inDir);
    void loadFile( string inFile );
    //void update();
    //void render();
    
    BitmapSequence* rollover_anim;
    BitmapSequence* rollout_anim;
    
    TouchState touchState;
    
    /*
    ofEvent<ofTouchEventArgs> customTouchDown;
    ofEvent<ofTouchEventArgs> customTouchMoved;
    ofEvent<ofTouchEventArgs> customTouchUp;
    ofEvent<ofTouchEventArgs> customTouchDoubleTap;
    ofEvent<ofTouchEventArgs> customTouchCancelled;
    */
private:
    bool hasAlpha;
    //ofPoint posOld;
    //ofPoint pos;
    //ofPoint velocity;
    
    BitmapSequence* press_anim;
    BitmapSequence* default_state;
    
    void init();
    void loadAnimSequence(TouchState touchState, string inDir);
    
protected:
    
    void onTouchDown( ofTouchEventArgs &touch );
	void onTouchMoved( ofTouchEventArgs &touch );
	void onTouchUp( ofTouchEventArgs &touch );
	void onTouchDoubleTap( ofTouchEventArgs &touch );
	void onTouchCancelled( ofTouchEventArgs &touch );
};

#endif



