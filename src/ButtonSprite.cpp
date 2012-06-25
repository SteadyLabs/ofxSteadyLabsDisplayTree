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
#include "ButtonSprite.h"

ButtonSprite::ButtonSprite(){
    // image = new ofImage();
    
    hasAlpha = true;
    init();

}


ButtonSprite::ButtonSprite( string inDir ){
    init();
    loadFile( inDir );
}

void ButtonSprite::loadFile(string inDir){
    
    string default_dir = inDir + "/default";
    string rollout_dir = inDir + "/rollout";
    string rollover_dir = inDir + "/rollover";
    string press_dir = inDir + "/press";
    
    loadAnimSequence(DEFAULT, default_dir);
    loadAnimSequence(ROLLOUT, rollout_dir);
    loadAnimSequence(ROLLOVER, rollover_dir);
    loadAnimSequence(PRESS, press_dir);
}

void ButtonSprite::init(){
    BaseSprite::BaseSprite();//super?
    //verbose = true;
    enableMouseEvents();
    //enablePQEvents();
    buttonState = DEFAULT;

    rollover_anim = NULL;
    rollout_anim = NULL;
    press_anim = NULL;
    
    default_state = NULL;
    
    
    // cout<< "ButtonSprite::constructor::rollover_anim:"<< rollover_anim<< "rollout_anim:" << rollout_anim <<"\n";
}

// function to load sequences
void ButtonSprite::loadAnimSequence(ButtonState thisState, string inDir)
{
    switch (thisState) {
        case DEFAULT:
            default_state = new BitmapSequence(inDir);
            default_state->name = "default";
            if (default_state->parentSprite == NULL){
                //cout << " default addChild " << name << endl;
                BaseSprite::addChild(default_state);
            }
            BaseSprite::width = default_state->width;
            BaseSprite::height = default_state->height;
            break;
            
        case ROLLOUT:
            
            rollout_anim = new BitmapSequence(inDir);
            rollout_anim->name = "rollout";
            break;
            
        case ROLLOVER:
            rollover_anim = new BitmapSequence(inDir);
            rollover_anim->name = "rollover";
            break;
            
        case PRESS:
            press_anim = new BitmapSequence(inDir);
            press_anim->name = "press";
            break;
            
        default:
            break;
    }
}

void ButtonSprite::onPress(int x, int y, int button)
{
    if (!BaseSprite::visible || !BaseSprite::worldMouseEnabled ) return;
    
    if (press_anim->parentSprite == NULL){
        // cout << " press addChild " << name << endl;
        BaseSprite::addChild(press_anim);
    }
    
    //remove all other states
    if (default_state->parentSprite != NULL)
        BaseSprite::removeChild(default_state);
    if (rollover_anim->parentSprite != NULL)
        BaseSprite::removeChild(rollover_anim);
    if (rollout_anim->parentSprite != NULL)
        BaseSprite::removeChild(rollout_anim);
    
    // cout<< "ButtonSprite::onPress::\n" <<  name << endl;
    buttonState = PRESS;
    press_anim->gotoAndPlay(1);
    this->dispatchEvent(ON_PRESS, name);
}


void ButtonSprite::onRelease(int x, int y, int button)
{
    //cout<< "ButtonSprite::onRelease::\n";
    
    if (default_state->parentSprite == NULL){
        // cout << " default addChild " << name << endl;
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
    
    buttonState = DEFAULT;
    this->dispatchEvent(ON_RELEASE, name);
}

void ButtonSprite::onReleaseOutside(int x, int y, int button)
{
    if (default_state->parentSprite == NULL){
        // cout << " default addChild " << name << endl;
        addChild(default_state);
    }
    
    //remove all other states
    if (press_anim->parentSprite != NULL)
        removeChild(press_anim);
    if (rollover_anim->parentSprite != NULL)
        removeChild(rollover_anim);
    if (rollout_anim->parentSprite != NULL)
        removeChild(rollout_anim);
    
    //cout<< "ButtonSprite::onRelease::\n";
    if (!visible ) return;
    buttonState = DEFAULT;
    this->dispatchEvent(ON_RELEASE_OUTSIDE, name);
}

//TODO: CK, implement rollover and rollout states
void ButtonSprite::onRollOut()
{
    //cout<< "ButtonSprite::onRollOut::\n";
    if (!visible || !worldMouseEnabled ) return;
    
    if (rollout_anim->parentSprite == NULL){
        // cout << " rollout addChild " << name << endl;
        addChild(rollout_anim);
    }
    
    //remove all other states
    if (default_state->parentSprite != NULL)
        removeChild(default_state);
    if (press_anim->parentSprite != NULL)
        removeChild(press_anim);
    if (rollover_anim->parentSprite != NULL)
        removeChild(rollover_anim);
    
    buttonState = ROLLOUT;
    rollout_anim->gotoAndPlay(1);
    this->dispatchEvent(ON_ROLLOUT, name);
}

void ButtonSprite::onRollOver(int x, int y)
{
    // cout<< "ButtonSprite::onRollOver::\n";
    if (!visible || !worldMouseEnabled ) return;
    
    if (rollover_anim->parentSprite == NULL){
        // cout << "rollover addChild" << name << endl;
        addChild(rollover_anim);
    }
    
    //remove all other states
    if (default_state->parentSprite != NULL)
        removeChild(default_state);
    if (press_anim->parentSprite != NULL)
        removeChild(press_anim);
    if (rollout_anim->parentSprite != NULL)
        removeChild(rollout_anim);
    
    buttonState = ROLLOVER;
    rollover_anim->gotoAndPlay(1);
    //traceTransformChain();
    this->dispatchEvent(ON_ROLLOVER, name);
}

