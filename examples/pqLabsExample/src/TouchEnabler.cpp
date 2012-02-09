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
#include "TouchEnabler.h"
#include "DisplayObject.h"
#include "TouchEventController.h"
//look in the .h file for the constructor

TouchEnabler::~TouchEnabler(){
}

void TouchEnabler::enableTouchEvents() {
    TouchEventController::addEnabler(this);
}

void TouchEnabler::disableTouchEvents() {
    TouchEventController::removeEnabler(this);
}

bool TouchEnabler::_touchMoved(ofTouchEventArgs &e) {
	int x = e.x;
	int y = e.y;
	_touchX = x;
	_touchY = y;
	
	if( _target->hitTest(x, y)) {               
        
        cout << "_touchMoved hitTest " << _target->name << "\n" ;
        
		if(!_touchOver && !_touchDown) {						
			_target->onRollOver(x, y);			
            // cout << "_touchMoved rollover " << _target->name << "\n";
			_touchOver = true;					
		}
		_target->onMouseMove(x, y);				
        return true;
	} else if( _touchOver || _touchDown) {					
		_target->onRollOut();					
        // cout << "_touchMoved rollout " << _target->name << "\n";
		_touchOver = false;		
        _touchDown = false;
	}
    
    return false;
}

void TouchEnabler::_touchMovedBlocked(ofTouchEventArgs &e){
    if (_touchOver) {
        _target->onRollOut();
        // cout << "_touchMovedBlocked rollout " << _target->name << "\n" ;
    }							
    _touchOver = false;	
    _touchDown = false;
}


void TouchEnabler::_touchPressed(ofTouchEventArgs &e, bool overRideHitTest) {
	int x = e.x;
	int y = e.y;
    // TODO: need an id
    
	_touchX = x;
	_touchY = y;

	if( overRideHitTest || _target->hitTest(x, y)) {
		if(!_touchDown) {   
            // cout << "_touchPressed _target->onPress" << _target->name << "_touchX " << x << " _touchY " << y << "\n";
			_target->onPress(x, y, 0);			
			_touchDown = true;						
		}
	} else { 
        // cout << "_touchPressed _target->onPressOutside" << _target->name << "_touchX " << x << " _touchY " << y << "\n";
		_target->onPressOutside(x, y, 0);
	}
}



void TouchEnabler::_touchReleased(ofTouchEventArgs  &e, bool overRideHitTest) {
	int x = e.x;
	int y = e.y;
	// TODO: need an id
    
	_touchX = x;
	_touchY = y;

	
	if( overRideHitTest ||_target->hitTest(x, y) ) {
        // cout << "_touchReleased _target->onRelease" << _target->name << "_touchX " << x << " _touchY " << y << "\n";
		_target->onRelease(x, y, 0);
	} else {
		if( _touchDown) 
            // cout << "_touchReleased _target->onReleaseOutside" << _target->name << " _touchX " << x << "_touchY " << y << "\n";
            _target->onReleaseOutside(x, y, 0);
        
	}
	_touchDown = false;
    _touchOver = false;
}


/*
 void TouchEnabler::_touchDragged(ofTouchEventArgs &e, bool overRideHitTest) {
 int x = e.x;
 int y = e.y;
 // TODO: need an id
 
 _touchX = x;
 _touchY = y;
 
 
 if( overRideHitTest || _target->hitTest(x, y)) {    
 if( !_touchOver ) {                             
 //onPress(x, y);                           
 _touchOver = true;                          
 }
 _target->onDragOver(x, y, 0);				
 } else {
 if( _touchOver ) {					
 _target->onRollOut();			
 _touchOver = false;				
 }
 if( _touchDown) {
 _target->onDragOutside(x, y, 0);
 }
 }
 }
 */



//---enablers are stored in a vector and iterated through... there is also a hashmap that keeps track of the sorted index--//
