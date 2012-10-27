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

#include "MouseEnabler.h"
#include "DisplayObject.h"
#include "MouseEventController.h"
//look in the .h file for the constructor

MouseEnabler::~MouseEnabler(){

}

void MouseEnabler::enableMouseEvents() {
    MouseEventController::addEnabler(this);
}

void MouseEnabler::disableMouseEvents() {
    // cout << "MouseEnabler::disableMouseEvents()" << endl;
    _mouseOver	= false;
    _mouseDown	= false;
    MouseEventController::removeEnabler(this);
}



bool MouseEnabler::_mouseMoved(ofMouseEventArgs &e) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
	
	_mouseX = x;
	_mouseY = y;
	
	if( _target->hitTest(x, y)) {               // if mouse is over the object
        
        //cout << "_mouseMoved hitTest " << _target->name << "\n" ;
        
		if(!_mouseOver) {						// if wasn't over previous frame
			_target->onRollOver(x, y);			// call onRollOver
            cout << "_mouseMoved rollover " << _target->name << "\n";
			_mouseOver = true;					// update flag
		}
		_target->onMouseMove(x, y);				// and trigger onMouseMove
        return true;
	} else if( _mouseOver) {					// if mouse is not over the object, but the flag is true (From previous frame)
		_target->onRollOut();					// call onRollOut
        cout << "_mouseMoved rollout " << _target->name << "\n";
		_mouseOver = false;						// update flag
	}
    return false;
}

void MouseEnabler::_mouseMovedBlocked(ofMouseEventArgs &e){
    if (_mouseOver) {
        _target->onRollOut();// call onRollOut
        cout << "_mouseMovedBlocked rollout " << _target->name << "\n" ;
    }							
    _mouseOver = false;	// update flag
}


void MouseEnabler::_mousePressed(ofMouseEventArgs &e, bool overRideHitTest) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
    
	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
	
	if( overRideHitTest || _target->hitTest(x, y)) {// if mouse is over
		if(!_mouseDown) {                           // if wasn't down previous frame
			_target->onPress(x, y, button);			// call onPress
			_mouseDown = true;						// update flag
		}
	} else {                                        // if mouse is not over
		_target->onPressOutside(x, y, button);
	}
}

void MouseEnabler::_mouseDragged(ofMouseEventArgs &e, bool overRideHitTest) {
	int x = e.x;
	int y = e.y;
	int button = e.button;

	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
    
	if( overRideHitTest || _target->hitTest(x, y)) {    // if mouse is over the object
		if( !_mouseOver ) {                             // if wasn't over previous frame
			//onPress(x, y);                            // call onPress - maybe not
			_mouseOver = true;                          // update flag
		}
		_target->onDragOver(x, y, button);				// and trigger onDragOver
	} else {
		if( _mouseOver ) {					// if mouse is not over the object, but the flag is true (From previous frame)
			_target->onRollOut();			// call onRollOut
			_mouseOver = false;				// update flag
		}
		if( _mouseDown) {
			_target->onDragOutside(x, y, button);
		}
	}
}

void MouseEnabler::_mouseReleased(ofMouseEventArgs &e, bool overRideHitTest) {
	int x = e.x;
	int y = e.y;
	int button = e.button;
    
	_mouseX = x;
	_mouseY = y;
	_mouseButton = button;
	
	if( overRideHitTest ||_target->hitTest(x, y) ) {
		_target->onRelease(x, y, button);
	} else {
		if( _mouseDown) 
            _target->onReleaseOutside(x, y, button);
        
	}
	_mouseDown = false;
    
}


//---enablers are stored in a vector and iterated through... there is also a hashmap that keeps track of the sorted index--//
        

