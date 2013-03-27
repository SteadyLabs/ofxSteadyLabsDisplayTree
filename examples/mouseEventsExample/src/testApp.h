#pragma once

#include "ofMain.h"
#include "DisplayObject.h"
#include "ButtonSprite.h"

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
    
    //these are the event listener functions
    void onButton1Pressed( ofMessage &e );
    void onButton1RolledOver( ofMessage &e );
    
    void onButton2Pressed( ofMessage &e );
    void onButton2RolledOut( ofMessage &e );
    
    DisplayObject* root;
    ButtonSprite* button1;
    ButtonSprite* button2;
		
};
