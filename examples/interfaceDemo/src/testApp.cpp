#include "testApp.h"
#include "MouseEventController.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();


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
    
    
    timeline = new TimelineSprite();
    
    
    root->addChild(timeline);
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

    
    root->draw();
    
    
    toggle1->renderFont();
    toggle2->renderFont();
    
    // timeline->render();

}



//--------------------------------------------------------------
void testApp::onToggle(ofMessage &e){

    cout << " show panel " << endl;
    
    if (toggle1->isOn) {
        
        timeline->visible = true;
        
    } else if (!toggle1->isOn) {
        
        timeline->visible = false;
        
    }
    
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