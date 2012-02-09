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

#include <iostream>

#include "TouchEventController.h"
#include "TouchEnabler.h"
#include "DisplayObject.h"
#include "PQLabsConnection.h"

//can we just instantiate this once here?
TouchEventController* TouchEventController::instance = new TouchEventController();

//static strings

TouchEventController::TouchEventController(){
    _touchMovedThisFrame = false;
}

void TouchEventController::init(){
    instance->_init();
}

void TouchEventController::_init(){
    ofAddListener(PQLabsConnection::instance()->connection.singleTouchGestureEventDispatcher, this, &TouchEventController::onSingleTouchGestureEvent);
    ofAddListener(PQLabsConnection::instance()->connection.singleTouchMoveGestureEventDispatcher, this, &TouchEventController::onSingleTouchMoveEvent);
    ofAddListener(PQLabsConnection::instance()->connection.gestureClearEventDispatcher, this, &TouchEventController::onGestureClearEvent);
}


void TouchEventController::processEvents(){
    //todo, go through the queue and process the events
    //possibly do some kind of mutex locking and unlocking to prevent race conditions
    
    instance->_sort();//in case something got moved to the top of the deck...
    instance->_processEvents();
}

struct more_than_renderOrder
{
    inline bool operator() ( TouchEnabler* obj1, TouchEnabler* obj2)
    {
        return ( obj1->getTarget()->renderOrder > obj2->getTarget()->renderOrder );
    }
};

void TouchEventController::_sort(){
    std::sort( _touchEnablers.begin(), _touchEnablers.end(), more_than_renderOrder() );
    
    // cout << "_sort::order::" <<endl;
    for( int i = 0; i < _touchEnablers.size(); i++ ){
        // cout << _touchEnablers[ i ]->getTarget()->renderOrder << " " << _touchEnablers[ i ]->getTarget()->name <<",";
    }
    // cout <<endl;
}

void TouchEventController::_processEvents(){
    TouchEvent* curEvent;
    while( _eventQueue.size() > 0 ){
        curEvent = _eventQueue.front();
        _eventQueue.pop(); //seriously, you can't get the reference without handling it?        
        _handleEvent( curEvent );   
        
        delete curEvent;
    }
    
    
    if( !_touchMovedThisFrame && _eventQueue.size() > 0){
        curEvent = new TouchEvent();
        curEvent->args = ofTouchEventArgs();
        //curEvent->args.x = ofGetMouseX();
        //curEvent->args.y = ofGetMouseY();
        TouchEvent *lastEvent = _eventQueue.back();
        curEvent->args.x = lastEvent->args.x;
        curEvent->args.x = lastEvent->args.y;
        curEvent->type = STILL;
        
        _handleEvent(curEvent);
        delete curEvent;
    }
    _touchMovedThisFrame = false;
}

void TouchEventController::_handleEvent( TouchEvent* inEvent){
   
    int touchX = inEvent->args.x;
    int touchY = inEvent->args.y;
    
    switch( inEvent->type ){
        case STILL:
        case TOUCH_MOVE: //todo: do something different if the touch hasn't moved
            
            for ( int i = 0; i < _touchEnablers.size(); i++ ){
                if ( _touchEnablers[ i ]->_touchMoved(inEvent->args) ){
                    if ( _touchEnablers[ i ]->blocking ){
                        for( i = i+1; i < _touchEnablers.size(); i++ ){
                            _touchEnablers[ i ]->_touchMovedBlocked(inEvent->args);
                        }
                    }
                }
            }
            break;
        
        case TOUCH_DOWN:
            
            for ( int i = 0; i < _touchEnablers.size(); i++ ){
                if ( _touchEnablers[ i ]->getTarget()->hitTest(touchX, touchY) ){
                    _touchEnablers[ i ]->_touchPressed(inEvent->args, true);
                    if ( _touchEnablers[ i ]->blocking ){
                        break;//if it's a blocking touch event, then stop sending click events to things below
                    }
                }
            }
            
            break;
            
        case TOUCH_UP:
            
            for ( int i = 0; i < _touchEnablers.size(); i++ ){
                if ( _touchEnablers[ i ]->getTarget()->hitTest(touchX, touchY) ){
                    _touchEnablers[ i ]->_touchReleased(inEvent->args, true);
                    if ( _touchEnablers[ i ]->blocking ){
                        break;//if it's a blocking touch event, then stop sending click events to things below
                    }
                }
            }
            
            break;
    }

}

void TouchEventController::addEnabler(TouchEnabler* inEnabler){
    TouchEventController::instance->_addEnabler( inEnabler );
}

void TouchEventController::removeEnabler(TouchEnabler* inEnabler){
    TouchEventController::instance->_removeEnabler( inEnabler );
}

void TouchEventController::_addEnabler(TouchEnabler* inEnabler){
    
    //look to make sure it's not already added
    map<TouchEnabler*, int>::const_iterator iter = _touchEnablerToIndex.find(inEnabler);
    if ( iter == _touchEnablerToIndex.end() ){
        //it's not in there, go ahead and add it
        _touchEnablers.push_back(inEnabler);
        _touchEnablerToIndex[ inEnabler ] = _touchEnablers.size(); //for now, until we sort it again
    }
    else{
        cout << inEnabler->_target->name << " TouchEventController::addEnabler::warning, trying to add an enabler that's already here\n";
    }
}

void TouchEventController::_removeEnabler(TouchEnabler* inEnabler){
    map<TouchEnabler*, int>::iterator iter = _touchEnablerToIndex.find(inEnabler);
    int index = 0;
    if ( iter != _touchEnablerToIndex.end() ){
        
        //it's there
        index = _touchEnablerToIndex[ inEnabler ];
        
        // cout << "TouchEventController::_removeEnabler " << inEnabler->_target->name << endl;
        _touchEnablerToIndex.erase( iter );
        
    }
    else{
        
        if ( _touchEnablers[ index ] != inEnabler ){ //index is the correct one for that enabler
            //find the correct index
            index = 0;
            while ( index < _touchEnablers.size() && _touchEnablers[index] != inEnabler ){
                index++;
            }
        }
        if( index < _touchEnablers.size() ){
            //delete it from touchEnablers
            // cout << "TouchEventController::_removeEnabler " << inEnabler->_target->name << endl;
            _touchEnablers.erase( _touchEnablers.begin() + index );
        }
    }   
}

//---------------------------------------------------------------------------------------------
// TODO: which events are going here

void TouchEventController::onSingleTouchGestureEvent(SingleTouchGestureEvent & event)
{
    ofPoint p = event.point;
    ofTouchEventArgs e;
    e.x = p.x - ofGetWindowPositionX();
    e.y = p.y - ofGetWindowPositionY();
    
    //cout << "TouchEventController::onSingleTouchGestureEvent _x: " << p.x << " _y: " << p.y << endl;
    
    // for some reason the first event is always 0,0, ignoring it
    if(p.x == 0 && p.y == 0) 
        return;
    
    TouchEvent *savedEvent = new TouchEvent();
    savedEvent->type = TOUCH_DOWN;
    savedEvent->args = e;
    _eventQueue.push(savedEvent);
 
}


void TouchEventController::onSingleTouchMoveEvent(SingleTouchMoveEvent & event)
{
   
    ofPoint p = event.point;
    ofTouchEventArgs e;
    e.x = p.x- ofGetWindowPositionX();;
    e.y = p.y- ofGetWindowPositionY();;
    
    //cout << "TouchEventController::onSingleTouchMoveEvent _x: " << p.x << " _y: " << p.y << endl;
    
    TouchEvent *savedEvent = new TouchEvent();
    savedEvent->type = TOUCH_MOVE;
    savedEvent->args = e;
    _eventQueue.push(savedEvent);
   
}


void TouchEventController::onGestureClearEvent(GestureClearEvent & event)
{
    
    
    ofTouchEventArgs e;
    TouchEvent *lastEvent = _eventQueue.back();
    e.x = lastEvent->args.x;
    e.y = lastEvent->args.y;
    
    //cout << "TouchEventController::onGestureClearEvent _x: " << e.x << " _y: " << e.y << endl;
    
    TouchEvent *savedEvent = new TouchEvent();
    savedEvent->type = TOUCH_UP;
    savedEvent->args = e;
    _eventQueue.push(savedEvent);

}


