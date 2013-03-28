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
#include "TimelineSprite.h"
#include "ofMain.h"

using namespace std;

void TimelineSprite::init()
{
    BaseSprite::BaseSprite();
    
    
    setupTimeline();
    
    //image = new ofImage();
    //hasAlpha = true;
    //hitOnAlpha = true;
    //alphaHitThreshold = 20;//it has to be almost totally transparent to not hit
}

TimelineSprite::TimelineSprite(){
	init();
}

/*
TimelineSprite::TimelineSprite( string inFile ){
	init();
    //loadFile( inFile );
}

bool TimelineSprite::hitTest( int tx, int ty ){
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

void TimelineSprite::loadFile(string inFile){
    image->loadImage( inFile.c_str() );
    //image->setImageType( OF_IMAGE_GRAYSCALE );
    width = image->width;
    height = image->height;
}
*/

void TimelineSprite::render(){
    
    // cout << "BitmapSprite::render" << this->name << endl;
    
    //cout<<"wtf\n"<<width <<"," <<height;
    //image->draw( 0,0 );// x, y );
    
    ofBackground(.15*255);
    
    
    glEnable(GL_DEPTH_TEST);
	ofPushMatrix();
	
	ofPushStyle();
    //set the color to whatever the last color we encountered was
	ofSetColor(timeline.getColor("Colors"));
	
    //translate to the center of the screen
	ofTranslate(ofGetWidth()*.5, ofGetHeight()*.66, 40);
    
    //Read the values out of the timeline and use them to change the viewport rotation
	ofRotate(timeline.getValue("Rotate X"), 1, 0, 0);
	ofRotate(timeline.getValue("Rotate Y"), 0, 1, 0);
	
	ofBox(0,0,0, 200);
	
	ofPopMatrix();
    
	ofPopStyle();
	
	timeline.draw();
    glDisable(GL_DEPTH_TEST);
    
    
}

//--------------------------------------------------------------
void TimelineSprite::setupTimeline(){
    
	glEnable(GL_DEPTH_TEST);
	ofEnableLighting();
	
	light.setPosition(ofGetWidth()*.5, ofGetHeight()*.25, 0);
	light.enable();
    
    //Timeline setup and playback details
    ofxTimeline::removeCocoaMenusFromGlut("interfaceDemo");
    
	timeline.setup();
    timeline.setFrameRate(30);
	timeline.setDurationInFrames(90);
	timeline.setLoopType(OF_LOOP_NORMAL);
    
	//each call to "add keyframes" add's another track to the timeline
	timeline.addCurves("Rotate X", ofRange(0, 360));
	timeline.addCurves("Rotate Y", ofRange(0, 360));
    
	//Flags are little markers that you can attach text to
    //They are only useful when listening to bangFired() events
    //so that you know when one has passed
	timeline.addColors("Colors");
    
    //setting framebased to true results in the timeline never skipping frames
    //and also speeding up with the
    //try setting this to true and see the difference
    glDisable(GL_DEPTH_TEST);
    
}