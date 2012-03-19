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

    loadAnimSequence(DEFAULT_TOUCH, inDir + "/default");
    loadAnimSequence(DOWN_TOUCH, inDir + "/down");
    //loadAnimSequence(MOVED_TOUCH, inDir + "/moved");
    loadAnimSequence(UP_TOUCH, inDir + "/up");
    loadAnimSequence(DOUBLETAP_TOUCH, inDir + "/doubletap");
}

void IOSTouchSprite::init(){
    BaseSprite::BaseSprite();//super? //Is this nessecary?
    
    touchState = DEFAULT_TOUCH;
    
    fingerIndex = NULL;
    //ofRegisterTouchEvents(this);
    // cout<< "ButtonSprite::constructor::rollover_anim:"<< rollover_anim<< "rollout_anim:" << rollout_anim <<"\n";
}

// function to load sequences
void IOSTouchSprite::loadAnimSequence(TouchState thisState, string inDir)
{
    BitmapSequence* tmp;
    switch (thisState) {
        case DEFAULT_TOUCH:
            tmp = new BitmapSequence(inDir);
            touchAnimationStates.push_back( tmp );
            tmp->name = "default";
            
            if (tmp->parentSprite == NULL){
                BaseSprite::addChild(tmp);
            }
            BaseSprite::width = tmp->width;
            BaseSprite::height = tmp->height;
            break;
            
        case DOWN_TOUCH:
            tmp = new BitmapSequence(inDir);
            touchAnimationStates.push_back( tmp );
            tmp->name = "down";
            break;
            
        case MOVED_TOUCH:
            //tmp = new BitmapSequence(inDir);
            //touchAnimationStates.push_back( tmp );
            //tmp->name = "move";
            break;
            
        case UP_TOUCH:
            tmp = new BitmapSequence(inDir);
            touchAnimationStates.push_back( tmp );
            tmp->name = "up";
            break;
        
        case DOUBLETAP_TOUCH:
            tmp = new BitmapSequence(inDir);
            touchAnimationStates.push_back( tmp );
            tmp->name = "doubletap";
            break;
            
        default:
            break;
    }
}

BitmapSequence* IOSTouchSprite::handleAnimationStates( string inShowState )
{
    BitmapSequence* tmp;
    for ( int i = 0; i < touchAnimationStates.size(); i++ ){
        if ( touchAnimationStates[i]->name == inShowState ){
            tmp = touchAnimationStates[i];
            if ( touchAnimationStates[i]->parentSprite == NULL ) {
                BaseSprite::addChild(touchAnimationStates[i]);
            }
        }
        
        if (touchAnimationStates[i]->name != inShowState ) {
            if ( touchAnimationStates[i]->parentSprite != NULL ) {
                BaseSprite::removeChild(touchAnimationStates[i]);
            }
        }
    }
    
    return tmp;
}

void IOSTouchSprite::onTouchDown( ofTouchEventArgs &touch )
{
    if (!BaseSprite::visible || !BaseSprite::worldMouseEnabled ) return;
    
    BitmapSequence* tmp = handleAnimationStates( "down" );
    
    touchState = DOWN_TOUCH;
    tmp->gotoAndPlay(1);
    printf("IOSTouchSprite::onTouchDown : play me some animation \n");
    //ofNotifyEvent(customTouchDown, touch, this);
    //this->dispatchEvent(ON_TOUCHDOWN, name);
}


void IOSTouchSprite::onTouchUp( ofTouchEventArgs &touch )
{    
    BitmapSequence* tmp = handleAnimationStates( "up" );
    
    if (!visible || !worldMouseEnabled ) return;
    
    touchState = UP_TOUCH;
    tmp->gotoAndPlay(1);
    //ofNotifyEvent(customTouchUp, touch, this);
    //this->dispatchEvent(ON_TOUCHUP, name);
}


void IOSTouchSprite::onTouchCancelled( ofTouchEventArgs &touch )
{
    //ofNotifyEvent(customTouchCancelled, touch, this);
}

void IOSTouchSprite::onTouchMoved( ofTouchEventArgs &touch )
{
    //BitmapSequence* tmp = handleAnimationStates( "moved" );

    //touchState = MOVED_TOUCH;
    //tmp->gotoAndStop(1);
    
    //ofNotifyEvent(customTouchMoved, touch, this);
}

void IOSTouchSprite::onTouchDoubleTap( ofTouchEventArgs &touch )
{
    BitmapSequence* tmp = handleAnimationStates( "doubletap" );
    
    touchState = DOUBLETAP_TOUCH;
    tmp->gotoAndPlay(1);
    
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