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
 
#ifndef dsgRetail_DisplayObject_h
#define dsgRetail_DisplayObject_h

#include "ofMain.h"
#include "Dispatcher.h"
//#include "InteractionEnabler.h"

class InteractionEnabler;
class MouseEnabler;

/**
 * Base class for display object hierarchy.
 */
class DisplayObject : public ofRectangle, public Dispatcher {
public:
    typedef map< string, DisplayObject*> NameObjectHash;
    
    std::vector< DisplayObject* > children;
    
    // Name of the node
    string name;
    
    // Reference to parent
    DisplayObject* parentSprite;
    
    // This is weird.  z-index?
    int renderOrder;
    
    // Visibility
    bool visible;
    
    // Controls if the display object renders a filled background
    bool opaque;
    // Background color to use if opaque
    ofColor backgroundColor;
    
    // Clips the drawing of sub nodes to the bounds of this sprite
    bool clipToBounds;
    
    // Alpha
    float alpha;
    
    // Rotation of the display object
    float rotation;
    
    // Scaling
    float scaleX;
    float scaleY;
    
    // Blending mode
    ofBlendMode blendMode;
    
    // Anchor point
    float registrationX;
    float registrationY;
    
    // Determines if this isRoot, though should probably be (parentSprite==NULL)
    bool isRoot;
    
    // Enables the mouse stuff
    MouseEnabler* mouseEnabler;
    
    DisplayObject();
    virtual ~DisplayObject();
    
    void init();
    
    void enableMouseEvents();
    void disableMouseEvents();
    
    virtual void update();
    virtual int draw( int inRenderOrder = -1);
    virtual void render();
    int drawChildren( int inRenderOrder );
    
    void addChild( DisplayObject* inSprite );
    void removeChild( DisplayObject* inSprite );
    int getIndexOfChild( DisplayObject* inSprite );
    DisplayObject *rootSprite();
    DisplayObject *spriteNamed(std::string spriteName, bool descend=true);
    
    virtual bool hitTest( int tx, int ty );  
    
    DisplayObject* getChildByName( string inName );
    
    void mouseEnable();
    void mouseDisable();
    void setMouseBlocking( bool inBlocking );
    void traceTransform();
    void traceTransformChain();
    
    
    ofPoint unprojectPoint( int x, int y ); 
    //end basesprite
    
    
    //mouse activity, meant to be implemented in subclasses
    
    virtual void onRollOver(int x, int y)					{}		// called when mouse enters object x, y, width, height
	virtual void onRollOut()								{}		// called when mouse leaves object x, y, width, height
	virtual void onMouseMove(int x, int y)					{}		// called when mouse moves while over object x, y, width, height
	virtual void onDragOver(int x, int y, int button)		{}		// called when mouse moves while over object and button is down
	virtual void onDragOutside(int x, int y, int button)	{}		// called when mouse moves while outside the object after being clicked on it
	virtual void onPress(int x, int y, int button)			{}		// called when mouse presses while over object
	virtual void onPressOutside(int x, int y, int button)	{}		// called when mouse presses while outside object
	virtual void onRelease(int x, int y, int button)		{}		// called when mouse releases while over object
	virtual void onReleaseOutside(int x, int y, int button)	{}		// called when mouse releases outside of object after being pressed on object
    
       
protected:
    //refactored from baseSprite
    //float worldX;
    //float worldY;
    
    float worldAlpha;
    bool worldVisible;
    bool worldMouseEnabled;
    
    void calcTransform();
    NameObjectHash nameToChild;
    
    bool mouseEnabled;
    //end basesprite
    
    ofMatrix4x4 transformedMatrix;
    static ofMatrix4x4 baseMatrix;
    void depthFirstTraversalWithVoid( void (DisplayObject::*pt2Func)(void) );
    void depthFirstTraversalWithInt( int (DisplayObject::*pt2Func)( int ) );
    
    bool startClip();
    void endClip();
    
private:
    //refactored from basesprite
    bool _visible;
    void drawComplete();
    void recalcMouseState();
    //end basesprite

    
};


#endif
