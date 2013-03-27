#pragma once

#include "ofMain.h"
#include "BaseSprite.h"
#include "BitmapSprite.h"
#include "ButtonSprite.h"
#include "BitmapSequence.h"

#include "JSONParser.h"


class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // ASSETS
    BaseSprite* root;
    BaseSprite* containerA;
    
    BitmapSprite* stageImg;
    BitmapSprite *redAsset;
    BitmapSprite *blueAsset;
    BitmapSprite *greenAsset;
    BitmapSprite *yellowAsset;
    
    // SETTINGS
    bool isDebug;
    
    // JSON
    JSONParser jsonParser;
		
};
