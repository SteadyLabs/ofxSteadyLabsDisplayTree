#pragma once

#include "ofMain.h"
#include "BaseSprite.h"
#include "SimpleToggle.h"
#include "ofxTimeline.h"
#include "ofxTLEmptyTrack.h"
#include "ofxTLEmptyKeyframes.h"


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
    void setupTimeline();
    
    BaseSprite *root;
    //BaseSprite *timelineSprite;
    SimpleToggle *toggle1;

    
    ofxTimeline timeline;
	ofxTLEmptyTrack* emptyTrack;
	ofxTLEmptyKeyframes* emptyKeyframes;
    
    
};
