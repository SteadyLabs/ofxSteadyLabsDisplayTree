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
#include "CaptureSprite.h"
#include "DisplayObject.h"

CaptureSprite::CaptureSprite( int inWidth, int inHeight, int inSamples ){
    fbo.allocate(inWidth, inHeight, GL_RGBA8, inSamples);
//    fbo.
    BaseSprite::BaseSprite();
    width = inWidth;
    height = inHeight;
}

void CaptureSprite::draw(){
    
    
    fbo.begin();
    
    glPushAttrib(GL_ALL_ATTRIB_BITS);  
    ofClear( 0,0,0,0);

    glEnable(GL_BLEND);  
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    DisplayObject::draw();
    
    glDisable(GL_BLEND);
  
    glPopAttrib();  
    fbo.end();
    
    
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); 
    fbo.draw(0, 0);
    glDisable(GL_BLEND); 
  
    
    
}

void CaptureSprite::drawFromCapture(float x, float y, float width, float height){
    //ie don't redraw the children
    fbo.draw( x,  y,  width,  height);
}