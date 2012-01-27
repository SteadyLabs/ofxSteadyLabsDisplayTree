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
#ifndef BASESPRITE_H
#define BASESPRITE_H

#include <vector>
#include "DisplayObject.h"


class BaseSprite : public DisplayObject{

    public:
        typedef map< string, BaseSprite> NameSpriteHash;
    
        BaseSprite();
        ~BaseSprite();
        
        /*
        bool visible;
        void update();
        virtual void draw();
        virtual void render();
        void drawChildren();
        float alpha;
        
        void addChild( BaseSprite* inSprite );
        void removeChild( BaseSprite* inSprite );
        int getIndexOfChild( BaseSprite* inSprite );
        bool hitTest( int tx, int ty );  
        
        BaseSprite* getChildByName( string inName );
    
        string name;
        BaseSprite* parentSprite;
    
    void mouseEnable();
    void mouseDisable();
    */
    
        
    protected:
    /*
        float worldX;
        float worldY;
        float worldAlpha;
        bool worldMouseEnabled;
    
        void calcTransform();
        NameSpriteHash nameToChild;
    
        bool mouseEnabled;
     */
        
        
    private:
        
    };


#endif //BASESPRITE_H