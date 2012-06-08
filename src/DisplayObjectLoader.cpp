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

DisplayObject *DisplayObjectLoader::build(Json::Value value)
{
    string type=value["type"].asString();
    
    // make sure a mapper has been defined.
    if (objectMap.find(type)!=objectMap.end())
    {
        // Do the mapping JSON -> properties
        DisplayObject *obj=objectMap[type]->build(value);
        
        // Do any child elements
        if (!value["children"].isNull())
            for(int i=0; i<value["children"].size(); i++)
            {
                DisplayObject *child=build(value["children"][i]);
                if (child)
                    obj->addChild(child);
            }
        
        return obj;
    }
    
    return NULL;
}

void DisplayObjectLoader::registerMapper(string tag, DisplayObjectMapper *mapper)
{
    objectMap[tag]=mapper;
}

DisplayObject *DisplayObjectLoader::loadString(string jsonStr)
{
	Json::Value jsonObj;
    Json::Reader reader;
	
	if (!reader.parse(jsonStr, jsonObj)) 
    {
		std::cout  << "Failed to parse JSON\n" << reader.getFormatedErrorMessages();
		throw;
	}
    
    return build(jsonObj);
}

DisplayObject *DisplayObjectLoader::loadFile(string filename)
{
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
    
    return loadString(jsonStr);
}