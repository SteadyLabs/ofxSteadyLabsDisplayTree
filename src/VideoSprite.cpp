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

}

VideoSprite::VideoSprite( string inFile ){
    
    loadFile(inFile);
}

VideoSprite::VideoSprite( string inFile, bool inIsLooped ){
    
    loadFile(inFile, inIsLooped);
    
}

void VideoSprite::update(){

    video->update();
    BaseSprite::update();//aka super.update();
}



void  VideoSprite::loadFile( string inFile, bool inIsLooped ){
	_isLooped = inIsLooped;

    video = new ofVideoPlayer();
    video->load( inFile.c_str() );
    if( !_isLooped ) video->setLoopState(OF_LOOP_NONE);

}

void VideoSprite::setPosition(float per)
{

    video->setPosition(per);
}

void VideoSprite::setFrame(int frame)
{
    
    video->setFrame(frame);
     
}

int VideoSprite::getCurrentVideoFrame() 
{
    return video->getCurrentFrame();
}

int VideoSprite::getTotalVideoFrames() 
{
    return video->getTotalNumFrames();
}

void  VideoSprite::render(){
   
    video->draw( 0, 0 );


}


void VideoSprite::close() {
    

    video->closeMovie();

	
}

float VideoSprite::getWidth()
{
    return video->getWidth();

}

float VideoSprite::getHeight()
{

    return video->getHeight();
}

bool VideoSprite::isLoaded()
{
    return video->isLoaded();
}


void  VideoSprite::play(){
    video->play();

}

VideoSprite::~ VideoSprite(){
    delete video;
}
