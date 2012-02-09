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


#include "TouchSprite.h"
#include "ofxPQLabs.h"
#include "HandGestures.h"
#include "PQLabsConnection.h"

//---------PQ LABS stuff--------//

// TODO: move to a subclass 
//PQ Stuff added by steady
/*********** 
 PQLABS stuff
 */
void TouchSprite::enablePQEvents(){
    
   /*
    ofAddListener(PQLabsConnection::instance()->connection.singleTouchGestureEventDispatcher, this, &TouchSprite::onSingleTouchGestureEvent);
    ofAddListener(PQLabsConnection::instance()->connection.singleTouchMoveGestureEventDispatcher, this, &TouchSprite::onSingleTouchMoveEvent);
    ofAddListener(PQLabsConnection::instance()->connection.gestureClearEventDispatcher, this, &TouchSprite::onGestureClearEvent);
    */
    
    /*
    // TODO: hand tracking added to pq events for now, move later
    ofAddListener(PQLabsConnection::instance()->handGestures->singleHandMoveGestureEventDispatcher, this, &TouchSprite::onSingleHandMoveEvent);
     */
}

void TouchSprite::disablePQEvents(){
    
    /*
    ofRemoveListener(PQLabsConnection::instance()->connection.singleTouchGestureEventDispatcher, this, &TouchSprite::onSingleTouchGestureEvent);
    ofRemoveListener(PQLabsConnection::instance()->connection.singleTouchMoveGestureEventDispatcher, this, &TouchSprite::onSingleTouchMoveEvent);
    ofRemoveListener(PQLabsConnection::instance()->connection.gestureClearEventDispatcher, this, &TouchSprite::onGestureClearEvent);
    */
    
    /*
    // TODO: hand tracking added to pq events for now, move later
    ofRemoveListener(PQLabsConnection::instance()->handGestures->singleHandMoveGestureEventDispatcher, this, &TouchSprite::onSingleHandMoveEvent);
     */
}



