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
#include "BitmapSprite.h"
#include "ofMain.h"

using namespace std;

void BitmapSprite::init()
{
    BaseSprite::BaseSprite();
    image = new ofImage();
    hasAlpha = true;
    hitOnAlpha = true;
    alphaHitThreshold = 20;//it has to be almost totally transparent to not hit
}

BitmapSprite::BitmapSprite(){
	init();
}

BitmapSprite::BitmapSprite( string inFile ){
	init();
    loadFile( inFile );
}

bool BitmapSprite::hitTest( int tx, int ty ){
    //cout<<"BitmapSprite::hitTest::1" << endl;
    if ( DisplayObject::hitTest(tx, ty) ){
        
        if( !hitOnAlpha){
            return true;
        }
        
        ofPoint myPoint = unprojectPoint(tx, ty);
        ofPixels myPixels;
        //myPixels.setFromExternalPixels( image->getPixels(), image->getWidth(), image->getHeight(), image->;
        
        ofColor myColor = image->getColor(myPoint.x, myPoint.y);
        //cout << "BitmapSprite::color " << (unsigned int)myColor.a;
        int alpha = (unsigned int)myColor.a;
        return (alpha >= alphaHitThreshold);
    }
    return false;
}

void BitmapSprite::loadFile(string inFile){
    image->loadImage( inFile.c_str() );
    //image->setImageType( OF_IMAGE_GRAYSCALE );
    if (width==0)
        width = image->width;
    if (height==0)
        height = image->height;
}

void BitmapSprite::render(){
    
    // cout << "BitmapSprite::render" << this->name << endl;
    
    //cout<<"wtf\n"<<width <<"," <<height;
    image->draw( 0,0 );// x, y );
}