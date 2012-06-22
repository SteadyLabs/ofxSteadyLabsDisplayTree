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
#include "VideoSprite.h"

VideoSprite::VideoSprite(){
    cout << "VideoSprite::Constructor:\n";
    video = new ofVideoPlayer();
}

VideoSprite::VideoSprite( string inFile ){
    cout << "VideoSprite::ConstructorWithFile:\n";    
    loadFile(inFile);
}

VideoSprite::VideoSprite( string inFile, bool inIsLooped ){
    cout << "VideoSprite::Constructor::WithFileAndLoop\n";
    loadFile(inFile, inIsLooped);
    
}

void VideoSprite::update(){
    //cout << "VideoSprite::update:\n";
    video->update();
    //BaseSprite::update();//aka super.update();
}



void  VideoSprite::loadFile( string inFile, bool inIsLooped ){
    cout << "VideoSprite::loadFile:\n";
    video->loadMovie( inFile.c_str() );
    _isLooped = inIsLooped;
    //video->setUseTexture(false);
    if( !_isLooped ) video->setLoopState(OF_LOOP_NONE);
    
}

void VideoSprite::setPosition(float per)
{
    //cout << "VideoSprite::setPosition:\n";
    video->setPosition(per);
}

void VideoSprite::setFrame(int frame)
{
    //cout << "VideoSprite::setFrame:\n";
    video->setFrame(frame);
    
}

int VideoSprite::getCurrentVideoFrame() 
{
    //cout << "VideoSprite::getCurrentVideoFrame:\n";
    return video->getCurrentFrame();
}

int VideoSprite::getTotalVideoFrames() 
{
    //cout << "VideoSprite::getTotalVideoFrames:\n";
    return video->getTotalNumFrames();
}

void  VideoSprite::render(){
    //cout << "VideoSprite::render:\n";
    video->draw( 0, 0 );
    
    
}

void VideoSprite::stop()
{
    //cout << "VideoSprite::stop:\n";
    video->stop();
}

void VideoSprite::close() {
    //cout << "VideoSprite::close:\n";
    video->closeMovie();
    
	
}

float VideoSprite::getWidth()
{
    //cout << "VideoSprite::getWidth:\n";
    return video->getWidth();
    
}

float VideoSprite::getHeight()
{
    //cout << "VideoSprite::getHeight:\n";
    return video->getHeight();
}

bool VideoSprite::isLoaded()
{
    //cout << "VideoSprite::isLoaded:\n";
    return video->isLoaded();
}


void  VideoSprite::play(){
    cout << "VideoSprite::play:\n";
    video->play();
    
}

VideoSprite::~ VideoSprite(){
    //cout << "VideoSprite::Destructor:\n";
    delete video;
}