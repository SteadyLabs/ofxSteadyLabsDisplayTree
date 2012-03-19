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
#include "BitmapSequence.h"

string BitmapSequence::ON_PLAY_COMPLETE = "onPlayComplete";
BitmapSequence::BitmapSequence(){
    init();
}

BitmapSequence::BitmapSequence( string inDir ){
    init();
    loadDir( inDir );
}

void BitmapSequence::init(){
    BaseMovie::BaseMovie();//super?
    usingFrames = true;//default this to true
    fps = 30;
    curFrame = totalFrames = 0;
    playing = false;
    hasAlpha = true;
    repeating = false;
    yoyo = false;
    forward = true;
    totalFrames = 0;
    //cout<< "BitmapSequence::init::usingFrames:"<< usingFrames<< "repeating:" << repeating <<"\n";
}
void BitmapSequence::loadDir(string inDir){
    dir.listDir( inDir );
    dir.sort();
    if( !dir.size() ){
		cout << "BitmapSequence::loadDir::no files in:" << inDir << "\n";
	}
    else{
        int numFiles = dir.size();
        for (int i = 0 ; i < numFiles; i++ ){
            string curFile = dir.getPath( i );
            ofImage* curImage = new ofImage();
            bool loaded = false;
            try {
                 loaded = curImage->loadImage( curFile );
            } catch ( std::exception& e ) {
                cout << "BitmapSequence::loadDir::Error trying to load image from:" << inDir<< "\n";
                printf("BitmapSequence::loadDir::Error trying to load image \n");
            }

            if ( loaded ){
                images.push_back(curImage);
            }
            else{
                delete curImage;//since we called new, we have to explicitly destroy
            }
        }
        totalFrames = images.size();
        //cout <<"BitmapSequence::loadDir::filesLoaded:" << totalFrames << "\n";
        printf("BitmapSequence::loadDir::filesLoaded: %i \n", totalFrames);
    }
    setDimensions();
}

void BitmapSequence::play(){
    playing = true;
}

void BitmapSequence::stop(){
    
    playing = false;
}

void BitmapSequence::useFrames(){
    usingFrames = true;
}

void BitmapSequence::useTime(){
    usingFrames = false;
}


void BitmapSequence::setDimensions(){

    width = images[ curFrame ]->width;
    height = images[ curFrame ]->height;
    //cout << "BitmapSequence::setDimensions::width:"<<width<<"\n";
    
}

void BitmapSequence::gotoAndPlay(int frame){
    printf("BitmapSequence::gotoAndPlay \n");
    //make sure they're asking for a frame in bounds    
    if ( frame >= 0 && frame < totalFrames ){
        curFrame = frame;
    }
    play();
}

void BitmapSequence::gotoAndStop(int frame){
    
    //make sure they're asking for a frame in bounds
    if ( frame >= 0 && frame < totalFrames ){
        curFrame = frame;
    }
    stop();
}
void BitmapSequence::update(){
    //cout<< "BitmapSequence::update::usingFrames:"<< usingFrames<< "repeating:" << repeating << name <<"\n";
    if ( ! (totalFrames  >= 1 ) ){
        cout<< "BitmapSequence::update::no frames exist:\n";
        return;//if we don't have more than one frames
    }
    if( totalFrames == 1 ){
        curFrame = 0;
        return;
    }
    if ( usingFrames && playing ){
        if ( repeating ){
            if( yoyo ){
                //it's going forward
                if (forward ){
                    curFrame++;
                    if (curFrame >= totalFrames ){
                        forward = false;
                        curFrame = totalFrames-2;//go back
                    }
                }
                else{
                    //it's going back
                    curFrame--;
                    if (curFrame <0 ){
                        forward = true;
                        curFrame = 1; //go forward instead
                    }
                }
            }
            else{
                curFrame = (curFrame + 1 )%totalFrames;
            }
        }
        else{
            curFrame++;
            if ( curFrame >= totalFrames ){
                curFrame = totalFrames -1;
                stop();
                dispatchEvent( BitmapSequence::ON_PLAY_COMPLETE , name );
            }
        }
        //cout<< "BitmapSequence::update::1::curFrame:"<< curFrame<< "\n";
    }
    else{
        //umm i dunno, use time?
    }
    
    setDimensions();
}

void BitmapSequence::render(){

    if( hasAlpha ){
        ofEnableAlphaBlending();
    }
    
    images[ curFrame ]-> draw( 0, 0 );

}

void BitmapSequence::onRelease(int x, int y, int button)
{
    this->dispatchEvent("onRelease", name);
}

BitmapSequence::~BitmapSequence(){
    for ( int i = 0; i < totalFrames; i++ ){
        delete images[ i ];
    }
}

