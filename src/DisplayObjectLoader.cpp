//
//  DisplayObjectLoader.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/2/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>
#include "DisplayObjectLoader.h"

DisplayObjectLoader::DisplayObjectLoader()
{
    init();
}

DisplayObjectLoader::~DisplayObjectLoader()
{
    
}

void DisplayObjectLoader::init() 
{
    // Default mappers
    objectMap["image"]=new BitmapSpriteMapper();
    objectMap["bitmap"]=new BitmapSpriteMapper();
    objectMap["video"]=new VideoSpriteMapper();
    objectMap["sequence"]=new BitmapSequenceMapper();
    objectMap["button"]=new ButtonSpriteMapper();
    objectMap["node"]=new BaseSpriteMapper();
}

DisplayObject *DisplayObjectLoader::instance(DisplayObject *parentObj, DisplayObjectMapper *mapper, Json::Value value)
{
    return mapper->build(parentObj, value);
}


DisplayObject *DisplayObjectLoader::include(DisplayObject *parentObj, Json::Value value)
{
    DisplayObject *obj=loadFile(parentObj,value["source"].asString());
    DisplayObjectMapper mapper;
    mapper.map(parentObj, obj, value);
    return obj;
}

DisplayObject *DisplayObjectLoader::build(DisplayObject *parentObj, Json::Value value)
{
    string type=value["type"].asString();
    
    if (type=="include")
    {
        return include(parentObj, value);
    }
    
    // make sure a mapper has been defined.
    if (objectMap.find(type)!=objectMap.end())
    {
        // Do the mapping JSON -> properties
        DisplayObject *obj=instance(parentObj, objectMap[type], value);
        
        // Do any child elements
        if (!value["children"].isNull())
            for(int i=0; i<value["children"].size(); i++)
                build(obj,value["children"][i]);
        
        return obj;
    }
    
    return NULL;
}

void DisplayObjectLoader::registerMapper(string tag, DisplayObjectMapper *mapper)
{
    objectMap[tag]=mapper;
}

DisplayObject *DisplayObjectLoader::loadString(DisplayObject *parent, string jsonStr)
{
	Json::Value jsonObj;
    Json::Reader reader;
	
	if (!reader.parse(jsonStr, jsonObj)) 
    {
		std::cout  << "Failed to parse JSON\n" << reader.getFormatedErrorMessages();
		throw;
	}
    
    return build(parent,jsonObj);
}

DisplayObject *DisplayObjectLoader::loadFile(DisplayObject *parent, string filename)
{
    cout << ofToDataPath(filename) << endl;
    // read from string
    string str,jsonStr;
	ifstream in;
	in.open(ofToDataPath(filename, true).c_str());
	getline(in,str);
	while ( in ) {
		jsonStr += str;
		getline(in, str);
	}
	in.close();
    
    return loadString(parent, jsonStr);
}