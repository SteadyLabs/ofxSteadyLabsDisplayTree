/***********************************************************************
 
 Copyright (c) 2011,2012, Carrie Kengle, Mike Manh
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

string ButtonSprite::ON_PRESS = "onPress";
string ButtonSprite::ON_RELEASE = "onRelease";
string ButtonSprite::ON_RELEASE_OUTSIDE = "onReleaseOutside";
string ButtonSprite::ON_ROLLOVER = "onRollover";
string ButtonSprite::ON_ROLLOUT = "onRollout";

ButtonSprite::ButtonSprite(){
    // image = new ofImage();
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
    
    states.push_back(default_state);
    states.push_back(rollout_anim);
    states.push_back(rollover_anim);
    states.push_back(press_anim);
    setState(DEFAULT);
    setAlphaHitThreshold(20);
    setUseAlpha(true);
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
    curState = NULL;
    
}

// function to load sequences
void ButtonSprite::loadAnimSequence(ButtonState thisState, string inDir)
{
    switch (thisState) {
        case DEFAULT:
            default_state = new BitmapSequence(inDir);
            default_state->name = "default_state";
            if (default_state->parentSprite == NULL){
                addChild(default_state);
            }
            BaseSprite::width = default_state->width;
            BaseSprite::height = default_state->height;
            break;
            
        case ROLLOUT:
            
            rollout_anim = new BitmapSequence(inDir);
            rollout_anim->name = "rollout_anim";
            break;
            
        case ROLLOVER:
            rollover_anim = new BitmapSequence(inDir);
            rollover_anim->name = "rollover_anim";
            break;
            
        case PRESS:
            press_anim = new BitmapSequence(inDir);
            press_anim->name = "press_anim";      
            press_anim->x = 20;
            break;
            
        default:
            break;
    }
}

void ButtonSprite::onPress(int x, int y, int button)
{
    cout << "ButtonSprite::onPress\n";
    if (!BaseSprite::visible || !BaseSprite::worldMouseEnabled ) return;
    
    //cout<< "ButtonSprite::onPress::\n" <<  name << endl;
    //buttonState = PRESS;
    setState( PRESS );
    curState->gotoAndPlay(1);
    this->dispatchEvent(ON_PRESS, name);
}


void ButtonSprite::onRelease(int x, int y, int button)
{
    
    if (!visible || !worldMouseEnabled ) return;
    
    setState( ROLLOVER );
    curState->gotoAndPlay(1);
    this->dispatchEvent(ON_RELEASE, name);
}

bool ButtonSprite::getUseAlpha(){
    return useAlpha;
}

void ButtonSprite::setUseAlpha( bool inUseAlpha ){
    useAlpha = inUseAlpha;    
    for( int i = 0; i < states.size(); i++ ){
        states[i]->hitOnAlpha = inUseAlpha;
    }
}

void ButtonSprite::setState( ButtonState inState ){
    switch (inState) {
        case DEFAULT:
            curState = default_state;
            break;
        case ROLLOUT:
            curState = rollout_anim;
            break;
        case ROLLOVER:
            curState = rollover_anim;
            break;
        case PRESS:
            curState = press_anim;            
            break;            
        default:
            break;
    }
    buttonState = inState;
    
    if (curState->parentSprite == NULL){
        // cout << " press addChild " << name << endl;
        addChild(curState);
    }
    
    //remove all other states
    for( int i = 0; i < states.size(); i++ ){
        if ( states[ i ] != curState && states[i]->parentSprite == this){
            removeChild(states[i]);
        }
    }
}

bool ButtonSprite::hitTest( int tx, int ty ){
    //ofLog( OF_LOG_VERBOSE, "ButtonSprite::hitTest" );
    //cout<< "ButtonSprite::hitTest\n";a
    //todo actually do a hit test based off the curstate
    if ( curState != NULL ){
        cout <<"ButtonSprite::hitTest::curState:" << name << "::" << curState->name <<endl;
        return curState->hitTest(tx, ty);
    }
    else{
        cout <<"ButtonSprite::hitTest::curState == NULL\n";
        return false;
    }
}


void ButtonSprite::setAlphaHitThreshold( int inThreshold ){
    alphaHitThreshold = inThreshold;
    for( int i = 0; i < states.size(); i++ ){
        states[i]->alphaHitThreshold = inThreshold;
    }
}

int ButtonSprite::getAlphaHitThreshold(){
    return( alphaHitThreshold );
}


void ButtonSprite::onReleaseOutside(int x, int y, int button)
{
    if (!visible ) return;
    //buttonState = DEFAULT;
    setState(DEFAULT);
    this->dispatchEvent(ON_RELEASE_OUTSIDE, name);
}

//TODO: CK, implement rollover and rollout states
void ButtonSprite::onRollOut()
{
    //cout<< "ButtonSprite::onRollOut::\n";
    if (!visible || !worldMouseEnabled ) return;
    
    setState(ROLLOUT);
    curState->gotoAndPlay(1);
    this->dispatchEvent(ON_ROLLOUT, name);
}

void ButtonSprite::onRollOver(int x, int y)
{
    //cout<< "ButtonSprite::onRollOver::\n";
    if (!visible || !worldMouseEnabled ) return;
    
    setState( ROLLOVER );
    curState->gotoAndPlay(1);
    //traceTransformChain();
    this->dispatchEvent(ON_ROLLOVER, name);
}

void ButtonSprite::render(){
    cout <<"ButtonSprite::render::"<< name <<endl;
    DisplayObject::render();
}

