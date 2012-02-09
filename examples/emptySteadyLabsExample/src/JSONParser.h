//
//  JSONParser.h
//  examples
//
//  Created by Sebastian Lemery on 11/3/11.
//  Copyright 2011 STEADY. All rights reserved.
//

#ifndef dsgRetail_JSONParser_h
#define dsgRetail_JSONParser_h

#include "ofxHttpUtils.h"
#include <json/json.h>
#include "BaseSprite.h"
#include "BitmapSprite.h"
#include "ButtonSprite.h"
#include "VideoSprite.h"
#include "BitmapSequence.h"

#include <string>

using namespace std;

class JSONParser {
public:
	string readfile(string path);
	Json::Value scrapeSpriteObject(Json::Value spriteObj, BaseSprite* parentSprite);
	Json::Value parse(string s);
	
	Json::Reader reader;
	
	void loadSpritesFromJSON(Json::Value spriteObj, BaseSprite* parentSprite);
    
private:
    float getFloatFromUint(uint num);
};

#endif
