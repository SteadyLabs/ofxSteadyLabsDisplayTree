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
#include "IOSTouchEnabler.h"
#include "DisplayObject.h"
#include "IOSTouchEventController.h"
#include "IOSTouchSprite.h"
//look in the .h file for the constructor

IOSTouchEnabler::~IOSTouchEnabler(){
}

void IOSTouchEnabler::enableTouchEvents() {
    IOSTouchEventController::addEnabler(this);
}

void IOSTouchEnabler::disableTouchEvents() {
    IOSTouchEventController::removeEnabler(this);
}

//DO we want drag into interaction ??
void IOSTouchEnabler::_touchMoved(ofTouchEventArgs &e) {
	//int x = e.x;
	//int y = e.y;
	/*
	if( _target->hitTest(x, y)) {               
                
		if(!isTouchOver && !isTouchDown) {						
			_target->onTouchDown( e );			
			isTouchOver = true;	
            isTouchDown = true;
		}
		_target->onTouchMoved( e );				
        return true;
	}else if( isTouchOver || isTouchDown ) {
        _target->onTouchMoved( e );				
        return true;
    }
    */
    /*else if( _touchOver || _touchDown) {					
		_target->onTouchUp( e );					
		_touchOver = false;		
        _touchDown = false;
	}*/
    if ( _target->fingerIndex != e.id ) return;
    _target->onTouchMoved( e );
    
    /*
    if( isTouchOver || isTouchDown ) {
        _target->onTouchMoved( e );				
        return true;
    }
    
    return false;
    */
}

void IOSTouchEnabler::_touchMovedBlocked(ofTouchEventArgs &e){
    /*
    if (isTouchOver) {
        _target->onTouchUp( e );
    }							
    isTouchOver = false;	
    isTouchDown = false;
     */
}


void IOSTouchEnabler::_touchDown(ofTouchEventArgs &e, bool overRideHitTest) {
	
    _target->fingerIndex = e.id;
    
    //printf("IOSTouchEnabler::_touchDown : touch id == %i \n", e.id);
    
    _target->onTouchDown( e );
    /*
	if( overRideHitTest || _target->hitTest(x, y)) {
		if(!isTouchDown) {   
			_target->onTouchDown( e );
			isTouchDown = true;						
		}
	} else { 
		_target->onTouchUp( e );
	}
     */
}


void IOSTouchEnabler::_touchUp(ofTouchEventArgs  &e, bool overRideHitTest) {
	//int x = e.x;
	//int y = e.y;

	//printf("IOSTouchEnabler::_touchUp \n");
    //printf("IOSTouchEnabler::_touchUp : touch id == %i \n", e.id);
    
    if ( _target->fingerIndex == e.id ) _target->fingerIndex = NULL;
    else return;
    
    _target->onTouchUp( e );
    /*
	if( overRideHitTest || _target->hitTest(x, y) ) {
        
		_target->onTouchUp( e );
	} else {
		if( isTouchDown || isTouchOver )
            
            _target->onTouchUp( e );
	}
	isTouchDown = false;
    isTouchOver = false;
    */
}

void IOSTouchEnabler::_touchDoubleTap(ofTouchEventArgs  &e, bool overRideHitTest) {
	//int x = e.x;
	//int y = e.y;
    
	printf("IOSTouchEnabler::_touchDoubleTap \n");
    
    _target->onTouchDoubleTap( e );
    /*
	if( overRideHitTest || _target->hitTest(x, y) ) {
        
		_target->onTouchUp( e );
	}
    */
}

/*
bool IOSTouchEnabler::getTouchState()
{
    return isTouchDown;
}
*/
//---enablers are stored in a vector and iterated through... there is also a hashmap that keeps track of the sorted index--//
