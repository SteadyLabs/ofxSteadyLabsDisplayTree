//
//  ToggleButton.cpp
//
//


#include <iostream>
#include "SimpleToggle.h"
#include "BitmapSprite.h"

SimpleToggle::SimpleToggle(){
    
    init();
    
}


SimpleToggle::SimpleToggle(string inPath){
    
    init();
    loadDir(inPath);
    
}

void SimpleToggle::init() {
    
    // font
    avenir.loadFont("fonts/avenir.ttf", 10);
    avenir.setLineHeight(10);
    
    image_off = NULL;
    image_on = NULL;
    isOn = false;
    toggleState = OFF_STATE; // default to off
    buttonTxt = "default";
    
    SimpleButton::SimpleButton(); // get that simple button
    
}

void SimpleToggle::renderFont() {
    
    ofSetColor(0, 0, 0);
    avenir.drawString("toggle1", BaseSprite::x + BaseSprite::width + 8, BaseSprite::y + 12);
    
}

void SimpleToggle::loadDir(string inDir) {

    loadImage(DEFAULT, "toggle/default/default.png");
    loadImage(ON_STATE, "toggle/on/onstate.png");
    loadImage(OFF_STATE, "toggle/off/offstate.png");
    
    /* bk: fix this to load the images in the directory recursively
     
    dir.listDir( inDir );
    dir.sort();

    if( !dir.size() ){
		cout << "BitmapSequence::loadDir::no files in:" << inDir << "\n";
        
	} else {
        
        
        int numFiles = dir.size();
        for (int i = 0 ; i < numFiles; i++ ){
            
            string curPath = dir.getPath(i);
            cout << "curFolder: " << curPath << endl;
            
            //subDir.listDir(curPath);
            //cout << subDir.size() << endl;
            
            //now loop through sub directories
            //ofDirectory subDir;
            //subDir.listDir(curPath);
            
            //cout << "subDir: " << subDir.size() << endl;
            
            //string subDirName = inDir + "/" + curFolder;
            
            int numImages = subDir.size();
            for (int i = 0; i < numImages; i ++) {
                
                string curImage = subDir.getName(i);
                cout << "curImage: " << curImage << endl;

                
                string curImage = subDir.getName(i);
                cout << "curImage: " << curImage << endl;
                
                if (curImage == "default.png") {
                    loadImage(DEFAULT, subDirName + "/" + curImage);

                } else if (curImage == "onstate.png") {
                    loadImage(ON_STATE, subDirName + "/" + curImage);
                    
                }  else if (curImage == "offstate.png") {
                    loadImage(ON_STATE, subDirName + "/" + curImage);
                    
                }
            }
            
        }
        
        
     } */
    
}

void SimpleToggle::loadImage(ToggleState thisState, string inDir) {
    
    switch (thisState) {
        case DEFAULT:
            image_off = new BitmapSprite(inDir);
            image_off->name = "default";
            
            if (image_off->parentSprite == NULL) {
                BaseSprite::addChild(image_off);
            }
            
            BaseSprite::width = image_off->width;
            BaseSprite::height = image_off->height;
            
            
            break;
            
        case ON_STATE:
            image_on = new BitmapSprite(inDir);
            image_on->name = "onimage";
            
            break;
            
        case OFF_STATE:
            image_off = new BitmapSprite(inDir);
            image_off->name = "offimage";
            
            break;
    }
    
}

void SimpleToggle::flipToggle() {
    
    isOn = !isOn; // bang!
    
    cout << "SimpleToggle::flipToggle current state: " << isOn << "\n";
    
    if (isOn) {
        
        if (image_on->parentSprite == NULL){
            addChild(image_on);
            removeChild(image_off);
        }
        
        toggleState = ON_STATE;
        
    } else if (!isOn) {
        
        if (image_off->parentSprite == NULL){
            addChild(image_off);
            removeChild(image_on);
        }
        
        toggleState = OFF_STATE;
    }
    
    
    
}

void SimpleToggle::onPress(int x, int y, int button){
    cout << "SimpleToggle::onPress\n";
    if (isInRenderTree())
        this->dispatchEvent(ON_PRESS, name);
}

void SimpleToggle::onRelease(int x, int y, int button){
    
    cout << "SimpleToggle::onRelease\n";
    if (isInRenderTree()) {
        
        
        flipToggle(); // flip it!
        
        this->dispatchEvent(ON_RELEASE, name);
        
    }
    
}

void SimpleToggle::onReleaseOutside(int x, int y, int button){
    cout << "SimpleToggle::onReleaseOutside\n";
    if (isInRenderTree())
        this->dispatchEvent(ON_RELEASE_OUTSIDE, name);
}