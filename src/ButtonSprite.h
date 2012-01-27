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
#ifndef ButtonSprite_h
#define ButtonSprite_h

#pragma once
#include "BaseSprite.h"
#include "BitmapSequence.h"
#include "BitmapSprite.h"
//#include "TouchSprite.h"

typedef enum{
    ROLLOVER,
    ROLLOUT,
    PRESS,
    DEFAULT
}ButtonState;


class ButtonSprite : public BaseSprite{
    
public:
    static string ON_PRESS;
    static string ON_RELEASE;
    static string ON_RELEASE_OUTSIDE;
    static string ON_ROLLOVER;
    static string ON_ROLLOUT;
    
    ButtonSprite();
    ButtonSprite( string inDir);
    void loadFile( string inFile );
    // void render();
    
    BitmapSequence* rollover_anim;
    BitmapSequence* rollout_anim;
    
    ButtonState buttonState;
    
    
    
private:
    bool hasAlpha;
    
    
    BitmapSequence* press_anim;
    BitmapSequence* default_state;
    
    
    void init();
    void loadAnimSequence(ButtonState buttonState, string inDir);
    
    
protected:
    void onPress(int x, int y, int button);
    void onRelease(int x, int y, int button);
    void onRollOver(int x, int y);
    void onReleaseOutside(int x, int y, int button);
	void onRollOut();
    
    // void update();

    
    
    
};

#endif


