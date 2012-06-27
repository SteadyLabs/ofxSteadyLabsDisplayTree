//
//  FlipBookSprite.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/26/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_FlipBookSprite_h
#define nikeolympics_FlipBookSprite_h


#include "ofMain.h"

#ifdef TARGET_OSX
#include <QuickTime/QuickTime.h>
#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>
#else
#include <QTML.h>
#include <FixMath.h>
#include <QuickTimeComponents.h>
#include <TextUtils.h>
#include <MediaHandlers.h>
//#include <MoviesFormat.h>
#endif

#include "ofTexture.h"
#include "ofQtUtils.h"
#include "ofConstants.h"
#include "ofBaseTypes.h"
#include "ofPixels.h"

#include "BaseSprite.h"

class FlipBookSprite;

class FlipBookThread : public ofThread 
{
public:
    long currentPos;
    long newPos;
    
    FlipBookSprite *flipBook;
    
    void updateTexture();
    void threadedFunction();
};

class FlipBookSprite : public BaseSprite 
{
public:
    int totalFrames;
    
    FlipBookSprite();
    ~FlipBookSprite();
    
    virtual void init();
    
    void loadFile(string fileName);
    
    void update();
    void render();
    
    void setPosition(float position);
    
    void updateTexture();
    
    friend class FlipBookThread;
protected:
    bool newImage;
    
    FlipBookThread thread;
    
    long currentPos;
    
    ofTexture tex;
    ofPixels pixels;
    
    MovieDrawingCompleteUPP myDrawCompleteProc;
    
    GWorldPtr offscreenGWorld;
    Movie moviePtr;
    
    unsigned char *offscreenGWorldPixels;	// 32 bit: argb (qt k32ARGBPixelFormat)
    
    void qtGetFrameCount(Movie & movForcount);
    void createImgMemAndGWorld();
};

#endif
