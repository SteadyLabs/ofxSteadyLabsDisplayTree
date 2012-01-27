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
#include "PQLabsConnection.h"
#include "ofMain.h"

PQLabsConnection* PQLabsConnection::_instance = 0;


PQLabsConnection::PQLabsConnection()
{
	
}

PQLabsConnection* PQLabsConnection::instance()
{
	if( _instance == 0)
	{
		_instance = new PQLabsConnection();
        _instance->init();
	}
	
	return _instance;
}

void PQLabsConnection::init(){
    handGestures = new HandGestures();
    connection.connect("127.0.0.1");
}

ofPoint PQLabsConnection::flipCoords(ofPoint p){
    
    float flipx = p.y;
    float flipy = p.x;
    
    float newx = ofMap(flipx, 1920, 0, 0, 1080);
    float newy = ofMap(flipy, 0, 1080, 0, 1920);
    
    ofPoint newP;
    newP.set(newx, newy);

    return newP;

}