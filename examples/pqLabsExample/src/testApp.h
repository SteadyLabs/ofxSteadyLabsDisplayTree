#pragma once

#include "ofMain.h"
#include "BaseSprite.h"
#include "ButtonSprite.h"
#include "TouchEnabler.h"

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
		
    BaseSprite* root;
    ButtonSprite *button1;
    ButtonSprite *button2;
    ButtonSprite *button3;
    
    TouchEnabler *t1;
    TouchEnabler *t2;
    TouchEnabler *t3;
    
};
