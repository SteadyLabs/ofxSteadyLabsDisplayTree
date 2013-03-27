#include "testApp.h"
#include "MouseEventController.h"

//--------------------------------------------------------------
void testApp::setup(){
    //objects with mouse events require the mousecontroller to be initialized before instantiating the objects
    MouseEventController::init();
    
    root = new DisplayObject();
    root->isRoot = true;
    string buttonDir = "testButton";
    
    //instantiate the buttons
    button1 = new ButtonSprite( buttonDir );
    button2 = new ButtonSprite( buttonDir );
    
    //set the registration point to the center, so it draws and scales from the center
    button1->registrationX = button1->width/2;
    button1->registrationY = button1->height/2;
    
    //set the registration point to the center, so it draws and scales from the center
    button2->registrationX = button2->width/2;
    button2->registrationY = button2->height/2;
    
    button1->x = 100;
    button2->x = 300;
    
    //give them a 100 pixel margin from the top
    button1->y = button2->y = 150;
    
    //add it to root
    root->addChild( button1 );
    root->addChild( button2 );
    
    //button 1 gets bigger every time you roll over it, but when you click it, it returns to normal size
    button1->addListener(ButtonSprite::ON_PRESS, this, &testApp::onButton1Pressed);
    button1->addListener(ButtonSprite::ON_ROLLOVER, this, &testApp::onButton1RolledOver);
    
    
    //button 2 gets smaller every time you click it, but when you roll out, it returns to normal size
    button2->addListener(ButtonSprite::ON_PRESS, this, &testApp::onButton2Pressed);
    button2->addListener(ButtonSprite::ON_ROLLOUT, this, &testApp::onButton2RolledOut);
}

//--------------------------------------------------------------
void testApp::onButton1Pressed( ofMessage &e ){
    button1->scaleX = button1->scaleY = 1;
}

void testApp::onButton1RolledOver( ofMessage &e ){
    button1->scaleX *=1.1;
    button1->scaleY = button1->scaleX;
}


//--------------------------------------------------------------
void testApp::onButton2Pressed( ofMessage &e ){
    button2->scaleX *=.95;
    button2->scaleY = button2->scaleX;
    
}

void testApp::onButton2RolledOut( ofMessage &e ){
    button2->scaleX = button2->scaleY = 1;
}

//--------------------------------------------------------------
void testApp::update(){
    root->update();
    MouseEventController::processEvents();
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