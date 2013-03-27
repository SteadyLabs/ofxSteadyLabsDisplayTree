#include "testApp.h"
#include "MouseEventController.h"

//--------------------------------------------------------------
void testApp::setup(){
    MouseEventController::init();
    root = new BaseSprite();
    root->isRoot = true;
    root->name = "root";
}

//--------------------------------------------------------------
void testApp::update(){
    MouseEventController::processEvents();
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