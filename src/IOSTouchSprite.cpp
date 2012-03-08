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
#include <iostream>
#include "IOSTouchSprite.h"
#include "ofEvents.h"

string IOSTouchSprite::ON_TOUCHDOWN = "onTouchDown";
string IOSTouchSprite::ON_TOUCHMOVED = "onTouchMoved";
string IOSTouchSprite::ON_TOUCHUP = "onTouchUp";
string IOSTouchSprite::ON_TOUCHDOUBLETAP = "onTouchDoubleTap";
string IOSTouchSprite::ON_TOUCHCANCELED = "onTouchCanceled";

IOSTouchSprite::IOSTouchSprite(){
    hasAlpha = true;
    init();
}

IOSTouchSprite::IOSTouchSprite( string inDir ){
    init();
    loadFile( inDir );
}

void IOSTouchSprite::loadFile(string inDir){
    
    string default_dir = inDir + "/default";
    string rollout_dir = inDir + "/rollout";
    string rollover_dir = inDir + "/rollover";
    string press_dir = inDir + "/press";
    
    loadAnimSequence(DEFAULT_TOUCH, default_dir);
    loadAnimSequence(ROLLOUT_TOUCH, rollout_dir);
    loadAnimSequence(ROLLOVER_TOUCH, rollover_dir);
    loadAnimSequence(PRESS_TOUCH, press_dir);
}

void IOSTouchSprite::init(){
    BaseSprite::BaseSprite();//super? //Is this nessecary?
    
    //verbose = true;
    //enableMouseEvents();
    //enablePQEvents();
    touchState = DEFAULT_TOUCH;
    
    rollover_anim = NULL;
    rollout_anim = NULL;
    press_anim = NULL;
    
    default_state = NULL;
    
    fingerIndex = NULL;
    //ofRegisterTouchEvents(this);
    // cout<< "ButtonSprite::constructor::rollover_anim:"<< rollover_anim<< "rollout_anim:" << rollout_anim <<"\n";
}

// function to load sequences
void IOSTouchSprite::loadAnimSequence(TouchState thisState, string inDir)
{
    switch (thisState) {
        case DEFAULT_TOUCH:
            default_state = new BitmapSequence(inDir);
            default_state->name = "default";
            if (default_state->parentSprite == NULL){
                //cout << " default addChild " << name << endl;
                BaseSprite::addChild(default_state);
            }
            BaseSprite::width = default_state->width;
            BaseSprite::height = default_state->height;
            break;
            
        case ROLLOUT_TOUCH:
            
            rollout_anim = new BitmapSequence(inDir);
            rollout_anim->name = "rollout";
            break;
            
        case ROLLOVER_TOUCH:
            rollover_anim = new BitmapSequence(inDir);
            rollover_anim->name = "rollover";
            break;
            
        case PRESS_TOUCH:
            press_anim = new BitmapSequence(inDir);
            press_anim->name = "press";
            break;
            
        default:
            break;
    }
}

void IOSTouchSprite::onTouchDown( ofTouchEventArgs &touch )
{
    if (!BaseSprite::visible || !BaseSprite::worldMouseEnabled ) return;
   
    if (press_anim->parentSprite == NULL){
        BaseSprite::addChild(press_anim);
    }
    
    //remove all other states
    if (default_state->parentSprite != NULL)
        BaseSprite::removeChild(default_state);
    if (rollover_anim->parentSprite != NULL)
        BaseSprite::removeChild(rollover_anim);
    if (rollout_anim->parentSprite != NULL)
        BaseSprite::removeChild(rollout_anim);
    
    //cout<< "ButtonSprite::onPress::\n" <<  name << endl;
    touchState = PRESS_TOUCH;
    press_anim->gotoAndPlay(1);
    
    //ofNotifyEvent(customTouchDown, touch, this);
    //this->dispatchEvent(ON_TOUCHDOWN, name);
}


void IOSTouchSprite::onTouchUp( ofTouchEventArgs &touch )
{    
    //printf("IOSTouchSprite::onTouchUp \n");
    
    if (default_state->parentSprite == NULL){
        addChild(default_state);
    }
    
    //remove all other states
    if (press_anim->parentSprite != NULL)
        removeChild(press_anim);
    if (rollover_anim->parentSprite != NULL)
        removeChild(rollover_anim);
    if (rollout_anim->parentSprite != NULL)
        removeChild(rollout_anim);
    
    
    if (!visible || !worldMouseEnabled ) return;
    
    touchState = DEFAULT_TOUCH;
    
    //touch.xspeed = velocity.x;
    //touch.yspeed = velocity.y;
    
    //ofNotifyEvent(customTouchUp, touch, this);
    //this->dispatchEvent(ON_TOUCHUP, name);
}


void IOSTouchSprite::onTouchCancelled( ofTouchEventArgs &touch )
{
    //ofNotifyEvent(customTouchCancelled, touch, this);
}

void IOSTouchSprite::onTouchMoved( ofTouchEventArgs &touch )
{
    if (press_anim->parentSprite == NULL){
        BaseSprite::addChild(press_anim);
    }
    
    //remove all other states
    if (default_state->parentSprite != NULL)
        BaseSprite::removeChild(default_state);
    if (rollover_anim->parentSprite != NULL)
        BaseSprite::removeChild(rollover_anim);
    if (rollout_anim->parentSprite != NULL)
        BaseSprite::removeChild(rollout_anim);

    touchState = PRESS_TOUCH;
    press_anim->gotoAndPlay(1);
    
    //touch.xspeed = velocity.x;
    //touch.yspeed = velocity.y;
    
    //ofNotifyEvent(customTouchMoved, touch, this);
}

void IOSTouchSprite::onTouchDoubleTap( ofTouchEventArgs &touch )
{
    //ofNotifyEvent(customTouchDoubleTap, touch, this);
}

// ofTouchEventArgs has speed and accel properties. Why do they always return zero?
/*
void IOSTouchSprite::update()
{
    if ( touchState == PRESS_TOUCH )
    {
        velocity = pos - posOld;
        posOld = pos;
    }
}
*/