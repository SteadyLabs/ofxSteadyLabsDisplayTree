#include "testApp.h"
#include "MouseEventController.h"
#include "TouchEventController.h"

//--------------------------------------------------------------
void testApp::setup(){
    // MouseEventController::init();
    
    TouchEventController::init();
    
    root = new BaseSprite();
    root->isRoot = true;
    root->name = "root";   
    
    
    //buttons
    button1 = new ButtonSprite("button1");
    button1->name = "button1";
    
    button2 = new ButtonSprite("button2");
    button2->name = "button2";
    
    button3 = new ButtonSprite("button3");
    button3->name = "button3";
    
    button2->x = 400;
    button3->x = 800;
    
    t1 = new TouchEnabler(button1);
    t2 = new TouchEnabler(button2);
    t3 = new TouchEnabler(button3);
    
    t1->enableTouchEvents();
    t2->enableTouchEvents();
    t3->enableTouchEvents();
    
    root->addChild(button1);
    root->addChild(button2);
    root->addChild(button3);

}

//--------------------------------------------------------------
void testApp::update(){
    // MouseEventController::processEvents();
    TouchEventController::processEvents();
    root->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    root->draw();
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