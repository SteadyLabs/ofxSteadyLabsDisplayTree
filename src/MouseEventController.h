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

#pragma once
#ifndef MouseEventController_h
#define MouseEventController_h

#include "ofMain.h"

class MouseEnabler;



class MouseEventController{
    
public:
    MouseEventController();
    ~MouseEventController();
    static void addEnabler( MouseEnabler* inEnabler);
    static void removeEnabler( MouseEnabler* inEnabler);
    static void processEvents();
    static void init();
    
    enum MouseEventType
    {
        MOVED,
        PRESSED,
        DRAGGED,
        RELEASED,
        STILL
    };
    
    struct MouseEvent{
        MouseEventType type;
        ofMouseEventArgs args;
    };
    
    //typedef std::pair< MouseEventType, ofMouseEventArgs> mouseEvent;
    
private:
    
protected:
    
    std::vector<MouseEnabler*> _mouseEnablers;
    std::map< MouseEnabler*, int> _mouseEnablerToIndex;
    
    static MouseEventController* instance;
    
    void _addEnabler( MouseEnabler* inEnabler);
    void _removeEnabler( MouseEnabler* inEnabler);
    
    //a queue of mouse events that have been adding up since before the event phase
    std::queue< MouseEvent* > _eventQueue;
    
    void _mouseMoved(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);
	void _mouseDragged(ofMouseEventArgs &e);
	void _mouseReleased(ofMouseEventArgs &e);
    void _handleEvent( MouseEvent* inEvent );
    
    void _init();
    
    void _sort();
    void _processEvents();
    
    bool _mouseMovedThisFrame;

};


#endif
