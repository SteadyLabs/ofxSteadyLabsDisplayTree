/***********************************************************************
 Copyright (c) 2011,2012, Mike Manh
 ***STEADY LTD http://steadyltd.com ***
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without 
 modification, are permitted provided that the following conditions are met:
 
 *Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 *Redistributions in binary form must reproduce the above copyright notice, 
 this list of conditions and the following disclaimer in the 
 documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************/

#include "MouseEventController.h"
#include "MouseEnabler.h"
#include "DisplayObject.h"
#include "ofEvents.h"

//can we just instantiate this once here?
MouseEventController* MouseEventController::instance = new MouseEventController();

//static strings

MouseEventController::MouseEventController(){
    _mouseMovedThisFrame = false;
}

void MouseEventController::init(){
    instance->_init();
}

void MouseEventController::_init(){
    
    ofAddListener(ofEvents().mousePressed, this, &MouseEventController::_mousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &MouseEventController::_mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &MouseEventController::_mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &MouseEventController::_mouseReleased);    
}


void MouseEventController::processEvents(){
    //todo, go through the queue and process the events
    //possibly do some kind of mutex locking and unlocking to prevent race conditions
    
    instance->_sort();//in case something got moved to the top of the deck...
    instance->_processEvents();
}

struct more_than_renderOrder
{
    inline bool operator() ( MouseEnabler* obj1, MouseEnabler* obj2)
    {
        return ( obj1->getTarget()->renderOrder > obj2->getTarget()->renderOrder );
    }
};

void MouseEventController::_sort(){
    std::sort( _mouseEnablers.begin(), _mouseEnablers.end(), more_than_renderOrder() );
    
    // cout << "_sort::order::" <<endl;
    for( int i = 0; i < _mouseEnablers.size(); i++ ){
        // cout << _mouseEnablers[ i ]->getTarget()->renderOrder << " " << _mouseEnablers[ i ]->getTarget()->name <<",";
    }
    // cout <<endl;
}

void MouseEventController::_processEvents(){
    MouseEvent* curEvent;
    while( _eventQueue.size() > 0 ){
        curEvent = _eventQueue.front();
        _eventQueue.pop(); //seriously, you can't get the reference without handling it?        
        _handleEvent( curEvent );   
        delete curEvent;
    }
    if( !_mouseMovedThisFrame ){
        curEvent = new MouseEvent();
        curEvent->args = ofMouseEventArgs();
        curEvent->args.x = ofGetMouseX();
        curEvent->args.y = ofGetMouseY();
        curEvent->type = STILL;
        
        _handleEvent(curEvent);
        delete curEvent;
    }
    _mouseMovedThisFrame = false;
}

void MouseEventController::_handleEvent( MouseEvent* inEvent){
    int mouseX = inEvent->args.x;
    int mouseY = inEvent->args.y;
	//cout << "MouseEventController::_handleEvent " << _mouseEnablers.size() << endl;
    switch( inEvent->type ){
		
        case MOVED:
        case STILL: //todo: do something different if the mouse hasn't moved
            //mouse move isn't blocked, apparently
	
			//cout << "MouseEventController::_handleEvent MOVED/STILL " << _mouseEnablers.size() << endl;
			
            for ( int i = 0; i < _mouseEnablers.size(); i++ ){
                //if ( _mouseEnablers[ i ]->getTarget()->hitTest(mouseX, mouseY) ){
                //    _mouseEnablers[ i ]->_mouseMoved(inEvent->args, true);
                   
                //}
                if ( _mouseEnablers[ i ]->_mouseMoved(inEvent->args) ){
                    if ( _mouseEnablers[ i ]->blocking ){
                        //cout << "THIS OBJECT IS BLOCKING " << _mouseEnablers[ i ]->getTarget()->name << endl;
                        for( i = i+1; i < _mouseEnablers.size(); i++ ){
                            
                            //cout << " therefore THIS will rollout " << _mouseEnablers[ i ]->getTarget()->name << endl;
                            _mouseEnablers[ i ]->_mouseMovedBlocked(inEvent->args);
                        }
                    }
                    
                }
                
            }
            

            break;
        case PRESSED:
            
	
			cout << "MouseEventController::_handleEvent PRESSED " << _mouseEnablers.size() << endl;
			
            for ( int i = 0; i < _mouseEnablers.size(); i++ ){
                if ( _mouseEnablers[ i ]->getTarget()->hitTest(mouseX, mouseY) ){
                    _mouseEnablers[ i ]->_mousePressed(inEvent->args, true);
                    if ( _mouseEnablers[ i ]->blocking ){
                        break;//if it's a blocking mouse event, then stop sending click events to things below
                    }
                }
            }
            

            break;
        case RELEASED:
            
			//cout << "MouseEventController::_handleEvent RELEASED " << _mouseEnablers.size() << endl;
			
            for ( int i = 0; i < _mouseEnablers.size(); ++i ){
				//cout << "MouseEventController::_handleEvent in the for loop " << _mouseEnablers.size() << endl;
                if ( _mouseEnablers[ i ]->getTarget()->hitTest(mouseX, mouseY) ){
					cout << "MouseEventController::_handleEvent in the hittest " << _mouseEnablers.size() << endl;
                    _mouseEnablers[ i ]->_mouseReleased(inEvent->args, true);
					
					if (i >= _mouseEnablers.size() ) break; // somehow 'i' gets to _mouseEnablers.size() and this causes a crash in Visual Studio 

                    if ( _mouseEnablers[ i ]->blocking ){
						cout << "MouseEventController::_handleEvent in the blocking " << _mouseEnablers.size() << endl;
                        break;//if it's a blocking mouse event, then stop sending click events to things below
                    }
                }
            }

			//cout << "MouseEventController::_handleEvent RELEASED we made it!" << endl;
			
            
            break;
        case DRAGGED:
            
			//cout << "MouseEventController::_handleEvent DRAGGED " << _mouseEnablers.size() << endl;
			
            for ( int i = 0; i < _mouseEnablers.size(); i++ ){
                if ( _mouseEnablers[ i ]->getTarget()->hitTest(mouseX, mouseY) ){
                    _mouseEnablers[ i ]->_mouseDragged(inEvent->args, true);
                    if ( _mouseEnablers[ i ]->blocking ){
                        break;//if it's a blocking mouse event, then stop sending click events to things below
                    }
                }
            }
			
            
            break;
    }
}

void MouseEventController::addEnabler(MouseEnabler* inEnabler){
    MouseEventController::instance->_addEnabler( inEnabler );
}

void MouseEventController::removeEnabler(MouseEnabler* inEnabler){
    MouseEventController::instance->_removeEnabler( inEnabler );
}

void MouseEventController::_addEnabler(MouseEnabler* inEnabler){
    
    //look to make sure it's not already added
    map<MouseEnabler*, int>::const_iterator iter = _mouseEnablerToIndex.find(inEnabler);
    if ( iter == _mouseEnablerToIndex.end() ){
        //it's not in there, go ahead and add it
        _mouseEnablers.push_back(inEnabler);
        _mouseEnablerToIndex[ inEnabler ] = _mouseEnablers.size(); //for now, until we sort it again
    }
    else{
        cout << inEnabler->_target->name << " MouseEventController::addEnabler::warning, trying to add an enabler that's already here\n";
    }
    
    //cout << "MouseEventController::_addEnabler::map.size:" << _mouseEnablerToIndex.size() <<endl;
    //cout << "MouseEventController::_addEnabler::vector.size:" << _mouseEnablers.size() <<endl;
}

void MouseEventController::_removeEnabler(MouseEnabler* inEnabler){
    // cout << "MouseEventController::_removeEnabler " << inEnabler->_target->name << endl;
    
    map<MouseEnabler*, int>::iterator iter = _mouseEnablerToIndex.find(inEnabler);
    int index = 0;
    if ( iter != _mouseEnablerToIndex.end() ){
        //it's there
        index = _mouseEnablerToIndex[ inEnabler ];
        cout << "MouseEventController::_removeEnabler delete it from _mouseEnablerToIndex" << inEnabler->_target->name << endl;
        _mouseEnablerToIndex.erase( iter );
     
    }

    index = 0;
    while ( index < _mouseEnablers.size() && _mouseEnablers[index] != inEnabler ){
        index++;
    }
      
    if( index < _mouseEnablers.size() ){
        //delete it from mouseEnablers
        cout << "MouseEventController::_removeEnabler delete it from _mouseEnablers index::" << index << " size::" << _mouseEnablers.size() << " " << inEnabler->_target->name << endl;
        _mouseEnablers.erase( _mouseEnablers.begin() + index );  
    }
      
    
    //cout << "MouseEventController::_removeEnabler::map.size:" << _mouseEnablerToIndex.size() << endl;
    //cout << "MouseEventController::_removeEnabler::vector.size:" << _mouseEnablers.size() << endl;
}

//---------------------------------------------------------------------------------------------
void MouseEventController::_mousePressed(ofMouseEventArgs &e) {
    MouseEvent* savedEvent = new MouseEvent();
    savedEvent->type = PRESSED;
    savedEvent->args = e;
    _eventQueue.push( savedEvent );
}

void MouseEventController::_mouseDragged(ofMouseEventArgs &e) {
    MouseEvent* savedEvent = new MouseEvent();
    savedEvent->type = DRAGGED;
    savedEvent->args = e;
    _eventQueue.push( savedEvent );
}

void MouseEventController::_mouseMoved(ofMouseEventArgs &e) {
    _mouseMovedThisFrame = true;
    MouseEvent* savedEvent = new MouseEvent();
    savedEvent->type = MOVED;
    savedEvent->args = e;
    _eventQueue.push( savedEvent );
}

void MouseEventController::_mouseReleased(ofMouseEventArgs &e) {
    MouseEvent* savedEvent = new MouseEvent();
    savedEvent->type = RELEASED;
    savedEvent->args = e;
    _eventQueue.push( savedEvent );
}

MouseEventController::~MouseEventController(){
    while( _eventQueue.size() > 0 ){
        MouseEvent* curEvent = _eventQueue.front();
        _eventQueue.pop();
        delete curEvent;
    }
}

