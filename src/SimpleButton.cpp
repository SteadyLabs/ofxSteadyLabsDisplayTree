//
//  SimpleButton.cpp
//  NikePro
//
//  Created by Michael Manh on 10/25/12.
//  Copyright (c) 2012 Uberlabs. All rights reserved.
//

#include <iostream>
#include "SimpleButton.h"
#include "BitmapSprite.h"

string SimpleButton::ON_PRESS = "onPress";
string SimpleButton::ON_RELEASE = "onRelease";
string SimpleButton::ON_RELEASE_OUTSIDE = "onReleaseOutside";


SimpleButton::SimpleButton():BaseSprite(){

    cout<< "SimpleButton::constructor\n";
    
    
    cout<< "SimpleButton::constructor::2\n";
    //mouseEnabler = NULL;
    image = NULL;

    enableMouseEvents();
    
}


SimpleButton::SimpleButton(string inPath):BaseSprite(){
    
    
    
    cout<< "SimpleButton::constructor::2\n";
    //mouseEnabler = NULL;
    image = NULL;
    
    enableMouseEvents();
    loadFile( inPath );
}

void SimpleButton::loadFile(string inPath){
    if ( image != NULL ){
        removeChild(image);
        delete image;       
    }
    
    
    image = new BitmapSprite( inPath );
    width = image->width;
    height = image->height;
    addChild( image );
}

void SimpleButton::onPress(int x, int y, int button){
    cout << "SimpleButton::onPress\n";
    if (isInRenderTree())
        this->dispatchEvent(ON_PRESS, name);
}

void SimpleButton::onRelease(int x, int y, int button){
    cout << "SimpleButton::onRelease\n";
    if (isInRenderTree())
        this->dispatchEvent(ON_RELEASE, name);
}

void SimpleButton::onReleaseOutside(int x, int y, int button){
    cout << "SimpleButton::onReleaseOutside\n";
    if (isInRenderTree())
    this->dispatchEvent(ON_RELEASE_OUTSIDE, name);
}