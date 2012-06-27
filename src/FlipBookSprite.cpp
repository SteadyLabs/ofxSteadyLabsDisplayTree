//
//  FlipBookSprite.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/26/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>
#include "FlipBookSprite.h"

void FlipBookThread::updateTexture()
{
    flipBook->newImage=true;
}

void FlipBookThread::threadedFunction()
{
    while(isThreadRunning())
    {
        while(newPos!=currentPos)
        {
            SetMovieTimeValue(flipBook->moviePtr, newPos);
            MoviesTask(flipBook->moviePtr,0);
        }
    }
}

#ifndef TARGET_LINUX

bool  	fpCreateMovieFromPath(char * path, Movie &movie);
bool 	fpCreateMovieFromPath(char * path, Movie &movie){
    
	Boolean 	isdir			= false;
	OSErr 		result 			= 0;
	FSSpec 		theFSSpec;
    
	short 		actualResId 	= DoTheRightThing;
    
#ifdef TARGET_WIN32
    result = NativePathNameToFSSpec (path, &theFSSpec, 0);
    if (result != noErr) {
        ofLog(OF_LOG_ERROR,"NativePathNameToFSSpec failed %d", result);
        ofLog(OF_LOG_ERROR,"Error loading movie");
        return false;
    }
    
#endif
    
#ifdef TARGET_OSX
    FSRef 		fsref;
    result = FSPathMakeRef((const UInt8*)path, &fsref, &isdir);
    if (result) {
        ofLog(OF_LOG_ERROR,"FSPathMakeRef failed %d", result);
        ofLog(OF_LOG_ERROR,"Error loading movie");
        return false;
    }
    result = FSGetCatalogInfo(&fsref, kFSCatInfoNone, NULL, NULL, &theFSSpec, NULL);
    if (result) {
        ofLog(OF_LOG_ERROR,"FSGetCatalogInfo failed %d", result);
        ofLog(OF_LOG_ERROR,"Error loading movie");
        return false;
    }
#endif
    
	short movieResFile;
	result = OpenMovieFile (&theFSSpec, &movieResFile, fsRdPerm);
	if (result == noErr) {
        
		short   movieResID = 0;
		result = NewMovieFromFile(&movie, movieResFile, &movieResID, (unsigned char *) 0, newMovieActive, (Boolean *) 0);
		if (result == noErr){
			CloseMovieFile (movieResFile);
		} else {
			ofLog(OF_LOG_ERROR,"NewMovieFromFile failed %d", result);
			return false;
		}
	} else {
		ofLog(OF_LOG_ERROR,"OpenMovieFile failed %d", result);
		return false;
	}
    
	return true;
}

//--------------------------------------------------------------
OSErr 	fpDrawCompleteProc(Movie theMovie, long refCon);
OSErr 	fpDrawCompleteProc(Movie theMovie, long refCon){
    
	FlipBookThread * ofvp = (FlipBookThread *)refCon;
    ofvp->updateTexture();
    return noErr;
}

//--------------------------------------------------------------
#endif
//--------------------------------------------------------------



FlipBookSprite::FlipBookSprite()
{
    init();
}

FlipBookSprite::~FlipBookSprite()
{
    
}

void FlipBookSprite::init()
{
}

void FlipBookSprite::createImgMemAndGWorld()
{
	Rect movieRect;
	movieRect.top 			= 0;
	movieRect.left 			= 0;
	movieRect.bottom 		= height;
	movieRect.right 		= width;
	offscreenGWorldPixels = new unsigned char[4 * movieRect.right * movieRect.bottom + 32];
	pixels.allocate(width,height,OF_IMAGE_COLOR);
    
    QTNewGWorldFromPtr (&(offscreenGWorld), k24RGBPixelFormat, &(movieRect), NULL, NULL, 0, (pixels.getPixels()), 3 * width);
    
	LockPixels(GetGWorldPixMap(offscreenGWorld));
	SetGWorld (offscreenGWorld, NULL);
	SetMovieGWorld (moviePtr, offscreenGWorld, nil);
}

void FlipBookSprite::loadFile(string fileName)
{
    
    thread.flipBook=this;
    thread.currentPos=0;
    thread.newPos=0;
    
    initializeQuicktime();			// init quicktime
    
    fileName = ofToDataPath(fileName);
    cout << fileName << endl;
    if( !fpCreateMovieFromPath((char *)fileName.c_str(), moviePtr) ) 
        throw;
    
    Rect 				movieRect;
    GetMovieBox(moviePtr, &(movieRect));
    width	= movieRect.right;
    height 	= movieRect.bottom;
    
    createImgMemAndGWorld();
    
    if (moviePtr == NULL)
        throw;
    
    //----------------- callback method
    myDrawCompleteProc = NewMovieDrawingCompleteUPP (fpDrawCompleteProc);
    SetMovieDrawingCompleteProc (moviePtr, movieDrawingCallWhenChanged,  myDrawCompleteProc, (long)&thread);
    
    // ------------- get the total # of frames:
    totalFrames				= 0;
    TimeValue			curMovieTime;
    curMovieTime		= 0;
    TimeValue			duration;
    
    //OSType whichMediaType	= VIDEO_TYPE; // mingw chokes on this
    OSType whichMediaType	= FOUR_CHAR_CODE('vide');
    
    short flags				= nextTimeMediaSample + nextTimeEdgeOK;
    
    while( curMovieTime >= 0 ) {
        totalFrames++;
        GetMovieNextInterestingTime(moviePtr,flags,1,&whichMediaType,curMovieTime,0,&curMovieTime,&duration);
        flags = nextTimeMediaSample;
    }
    
    newImage=false;
    
    totalFrames--; // there's an extra time step at the end of themovie
    
    tex.allocate(width, height, ofGetGLTypeFromPixelFormat(OF_PIXELS_RGB));
    
    TimeValue timeNow 	= 	GetMovieTime(moviePtr, 0);
    GoToBeginningOfMovie(moviePtr);
    SetMovieActive(moviePtr, true);
    SetMovieRate(moviePtr, X2Fix(0));
    PrerollMovie(moviePtr, timeNow, X2Fix(0));
    
    MoviesTask(moviePtr,0);
    
    thread.startThread(false,true);
}

void FlipBookSprite::setPosition(float pos)
{
    long total 		= GetMovieDuration(moviePtr );
    long newPos 	= (long)((float)total * pos);
    
    thread.newPos=newPos;
}

void FlipBookSprite::updateTexture()
{
    tex.loadData(pixels);//.getPixels(), tex.getWidth(), tex.getHeight(), ofGetGLTypeFromPixelFormat(OF_PIXELS_RGB));
}

void FlipBookSprite::update()
{
    DisplayObject::update();
    
    while(newImage)
    {
        newImage=false;
        updateTexture();
    }
}

void FlipBookSprite::render()
{
    tex.draw(0,0,width,height);
}
