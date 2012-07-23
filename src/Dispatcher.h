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
//#include "DisplayObject.h"
#include <string>
#include "ofEvents.h"
#include <map>

class Dispatcher{

    typedef std::map <string, ofEvent< ofMessage >* > StringToEventPtrMap; 
    
public:
    Dispatcher();
    //template <class ListenerClass, class ArgumentsType>
    
    /*
    void addListener(string inEvent, ListenerClass  * listener, void (ListenerClass::*listenerMethod)(const void*, ArgumentsType&)){
        
        
    }
    */
    template <class ListenerClass, class ArgumentsType>
    void addListener(string inEvent, ListenerClass  * listener, void (ListenerClass::*listenerMethod)( ArgumentsType&)){
        ofEvent<ofMessage>* myEvent = getEventForMessage( inEvent );
        //myEvent += Poco::delegate( listener, listenerMethod );
        ofAddListener( *myEvent, listener, listenerMethod);
        // cout<<"what??\n";
        
    }
    
    template <class ListenerClass, class ArgumentsType>
    void removeListener(string inEvent, ListenerClass  * listener, void (ListenerClass::*listenerMethod)( ArgumentsType&)){
        ofEvent<ofMessage>* myEvent = getEventForMessage( inEvent );
        //myEvent += Poco::delegate( listener, listenerMethod );
        ofRemoveListener( *myEvent, listener, listenerMethod);
        
    }
    
    
    void dispatchEvent( string inEvent );
    void dispatchEvent( string inEvent, string inMessage );    
                
protected:
    ofEvent< ofMessage >* getEventForMessage( string inEventName );                  
    StringToEventPtrMap nameToEvent;
private:
            //template <class EventType,typename ArgumentsType, class ListenerClass

    
    
};