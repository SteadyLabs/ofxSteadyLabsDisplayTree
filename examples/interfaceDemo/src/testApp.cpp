#include "testApp.h"
#include "MouseEventController.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();

    
    setupTimeline();

    MouseEventController::init();

    root = new BaseSprite();
    root->isRoot = true;
    root->name = "root";
    
    
    string buttonPath = "toggle";
    toggle1 = new SimpleToggle(buttonPath);
    toggle1->x = 25;
    toggle1->y = 500;
    toggle1->addListener(SimpleToggle::ON_PRESS, this, &testApp::onToggle);

    
    toggle2 = new SimpleToggle(buttonPath);
    toggle2->x = 25;
    toggle2->y = 530;
    toggle2->addListener(SimpleToggle::ON_PRESS, this, &testApp::onToggle2);
    
    
    root->addChild(toggle1);
    root->addChild(toggle2);
    
    //timelineSprite = new BaseSprite();
    //root->addChild(timelineSpr)
    
}

//--------------------------------------------------------------
void testApp::update(){
    root->update();
    MouseEventController::processEvents();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    
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

    
    
    root->draw();
    
    
    toggle1->renderFont();
    toggle2->renderFont();

}

//--------------------------------------------------------------
void testApp::setupTimeline(){

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

//--------------------------------------------------------------
void testApp::onToggle(ofMessage &e){

    cout << " show panel " << endl;
}

void testApp::onToggle2(ofMessage &e){
    
    cout << " show panel " << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}