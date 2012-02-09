#include "testApp.h"
#include "MouseEventController.h"


//--------------------------------------------------------------
void testApp::setup(){
    // Init the MouseEventController
    MouseEventController::init();
    
    // Root BaseSprite to contain all assets on the stage
    root = new BaseSprite();
    root->isRoot = true;
    root->name = "root";
    root->visible = true;
    
    // Loading a background image from the filepath
    stageImg = new BitmapSprite();
    stageImg->loadFile( "stage.png" );
    stageImg->x = 16.5f;
    stageImg->y = 91.0f;
    stageImg->name = "stage";
    
    // Scraping children assets from JSON
    // This steps through all children elements in the demo json 
    // and loads them into sprites for the display tree.
    Json::Value siteJSON = jsonParser.parse("sample_json.json");
    BaseSprite* newSprite = new BaseSprite();
    jsonParser.loadSpritesFromJSON(siteJSON["children"], newSprite);
    newSprite->visible = true;
    
    // Finally we add everything to the root stage
    root->addChild(stageImg);
    root->addChild(newSprite);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Clear our background
    ofBackground(0);
    
    // Update mouse events
    MouseEventController::processEvents();
    
    // Update our display tree
    root->update();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // Draw the root to the display tree
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