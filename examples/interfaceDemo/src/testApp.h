#pragma once

#include "ofMain.h"
#include "BaseSprite.h"
#include "SimpleToggle.h"
#include "TimelineSprite.h"

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
    
    
    void onToggle(ofMessage &e);
    void onToggle2(ofMessage &e);
    
    BaseSprite *root;
    //BaseSprite *timelineSprite;
    SimpleToggle *toggle1;
    SimpleToggle *toggle2;

    TimelineSprite *timeline;
    
    
};
