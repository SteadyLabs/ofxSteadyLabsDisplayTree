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

VideoSprite::VideoSprite( string inFile, bool inHasAlpha ){
    
    loadFile(inFile, inHasAlpha);
}

VideoSprite::VideoSprite( string inFile, bool inHasAlpha, bool inIsLooped ){
    
    loadFile(inFile, inHasAlpha, inIsLooped);
    
}

void VideoSprite::update(){
    //video.idleMovie();
    if (hasAlpha ){
        alphaVideo->update();
    }
    else{
        video->update();
    }
    BaseSprite::update();//aka super.update();
}



void  VideoSprite::loadFile( string inFile, bool inHasAlpha, bool inIsLooped ){
	_isLooped = inIsLooped;
    if ( inHasAlpha ){
        hasAlpha = true;
        int mode = OFXQTVIDEOPLAYER_MODE_TEXTURE_ONLY;
        alphaVideo = new ofxQTKitVideoPlayer();
        alphaVideo->loadMovie( inFile.c_str(), mode );   
		if( !_isLooped ) alphaVideo->setLoopState(OF_LOOP_NONE);
    }
    else{
        hasAlpha = false;
        video = new ofVideoPlayer();
        video->loadMovie( inFile.c_str() );
		if( !_isLooped ) video->setLoopState(OF_LOOP_NONE);
    }
}

void VideoSprite::setPosition(float per)
{
    if (hasAlpha ){
        alphaVideo->setPosition(per);
    }
    else{
        video->setPosition(per);
    } 
}

void VideoSprite::setFrame(int frame)
{
    if (hasAlpha ){
        alphaVideo->setFrame(frame);
    }
    else{
        video->setFrame(frame);
    } 
}

int VideoSprite::getCurrentVideoFrame() 
{
    if (hasAlpha ){
        return alphaVideo->getCurrentFrame();
    }
    else{
        return video->getCurrentFrame();
    }  
}

int VideoSprite::getTotalVideoFrames() 
{
    if (hasAlpha ){
        return alphaVideo->getTotalNumFrames();
    }
    else{
        return video->getTotalNumFrames();
    }
}

void  VideoSprite::render(){
   
    if (hasAlpha ){
        alphaVideo->draw( 0, 0);
    }
    else{
        video->draw( 0, 0 );
    }    

}

//// Added because was having problems unloading movies from overlay controller -seb
//void VideoSprite::stop() {
//	
//    if (hasAlpha ){
//        alphaVideo->pause();
//    }
//    else{
//        video->stop();
//    }    
//	
//}

void VideoSprite::close() {
    
	if (hasAlpha ){
        alphaVideo->closeMovie();
    }
    else{
        video->closeMovie();
    }	
	
}

float VideoSprite::getWidth()
{
	if (hasAlpha ){
        alphaVideo->getWidth();
    }
    else{
        video->getWidth();
    }	
}

float VideoSprite::getHeight()
{
	if (hasAlpha ){
        alphaVideo->getHeight();
    }
    else{
        video->getHeight();
    }	
}

bool VideoSprite::isLoaded()
{
	if(hasAlpha)
	{
		if(alphaVideo->isLoaded())
		{
			return alphaVideo->isLoaded();
		}
	} else
	{
		if( video->isLoaded() )
		{
			return video->isLoaded();
		}
	}
	
	return false;
}


void  VideoSprite::play(){
    if (hasAlpha ){
        alphaVideo->play();
    }
    else{
        video->play();
    }
}

VideoSprite::~ VideoSprite(){
    //todo: write a destructor, deallocate mem
}