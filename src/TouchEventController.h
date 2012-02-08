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

#ifndef TOUCHEVENTCONTROLLER_H
#define TOUCHEVENTCONTROLLER_H

#include "ofMain.h"
#include "ofxPQLabs.h"

class TouchEnabler;

class TouchEventController{
    
public:
    TouchEventController();
    ~TouchEventController();
    static void addEnabler( TouchEnabler* inEnabler);
    static void removeEnabler( TouchEnabler* inEnabler);
    static void processEvents();
    static void init();
    
    enum TouchEventType
    {
        TOUCH_DOWN,
        TOUCH_UP,
        TOUCH_MOVE
    };
    
    struct TouchEvent{
        TouchEventType type;
        ofTouchEventArgs args;
    };
        
private:
    
protected:
    
    std::vector<TouchEnabler*> _touchEnablers;
    std::map< TouchEnabler*, int> _touchEnablerToIndex;
    
    static TouchEventController* instance;
    
    void _addEnabler( TouchEnabler* inEnabler);
    void _removeEnabler( TouchEnabler* inEnabler);
    
    //a queue of mouse events that have been adding up since before the event phase
    std::queue< TouchEvent* > _eventQueue;
    
    void onSingleTouchGestureEvent(SingleTouchGestureEvent & event);
    void onSingleTouchMoveEvent(SingleTouchMoveEvent & event);
    void onGestureClearEvent(GestureClearEvent & event);
    
    void _handleEvent( TouchEvent* inEvent );
    
    void _init();
    
    void _sort();
    void _processEvents();
    
    // TODO: do we need this for touch events?
    // bool _mouseMovedThisFrame;
    
};


#endif
