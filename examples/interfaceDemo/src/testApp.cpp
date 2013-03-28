#include "testApp.h"
#include "MouseEventController.h"

//--------------------------------------------------------------
void testApp::setup(){
    MouseEventController::init();
    
    root = new BaseSprite();
    root->isRoot = true;
    root->name = "root";
    
    
    string buttonPath = "toggle";
    toggle1 = new SimpleToggle(buttonPath);
    toggle1->x = 300;
    toggle1->y = 300;
    toggle1->addListener(SimpleToggle::ON_PRESS, this, &testApp::onToggle);
    
    root->addChild(toggle1);
    
    
    //timelineSprite = new BaseSprite();
    //root->addChild(timelineSpr)
    setupTimeline();
    
}

//--------------------------------------------------------------
void testApp::update(){
    root->update();
    MouseEventController::processEvents();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(30, 30, 30);
    
    toggle1->renderFont();
    
    root->draw();
    
    // make a timeline sprite
    float curtime = timeline.getCurrentTime();
	timeline.draw();
}

//--------------------------------------------------------------
void testApp::setupTimeline(){

    //lets you use COMMAND+C and COMMAND+V actions on mac
    ofxTimeline::removeCocoaMenusFromGlut("Empty Templates");

    timeline.setup();
    timeline.setLoopType(OF_LOOP_NORMAL);
    timeline.setDurationInSeconds(30);

    //this is the simplest example and is really flexible
    emptyTrack = new ofxTLEmptyTrack();
    timeline.addTrack("My Custom Track", emptyTrack);

    //a very simple color keyframe
    emptyKeyframes = new ofxTLEmptyKeyframes();
    emptyKeyframes->setXMLFileName("MyEmptyKeyframes.xml");
    timeline.addTrack("My Custom Keyframes", emptyKeyframes);
}

//--------------------------------------------------------------
void testApp::onToggle(ofMessage &e){

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