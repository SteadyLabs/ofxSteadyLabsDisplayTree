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
    button3 = new ButtonSprite( buttonDir );
    button4 = new ButtonSprite( buttonDir );
    
    
    //make button 2 overlap with button1
    button1->x = 100;
    button2->x = button1->width + button1->x - 30;
    
    //make button4 overlap with button 3
    button3->x = 500;
    button4->x = button3->x + button3->width - 30;
    
    //but this time, make button 4 a blocking button
    button4->setMouseBlocking(true);
    
    //give them a 100 pixel margin from the top
    button1->y = button2->y = button3->y = button4->y = 100;
    
    button1->name = "button1";
    button2->name = "button2";
    button3->name = "button3";
    button4->name = "button4";
    
    //add it to root
    root->addChild( button1 );
    root->addChild( button2 );
    root->addChild( button3 );
    root->addChild( button4 );
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