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

DisplayObject *DisplayObjectLoader::instance(DisplayObjectMapper *mapper, Json::Value value)
{
    return mapper->build(value);
}


DisplayObject *DisplayObjectLoader::include(Json::Value value)
{
    DisplayObject *obj=loadFile(value["source"].asString());
    DisplayObjectMapper mapper;
    mapper.map(obj, value);
    return obj;
}

DisplayObject *DisplayObjectLoader::build(Json::Value value)
{
    string type=value["type"].asString();
    
    if (type=="include")
    {
        return include(value);
    }
    
    // make sure a mapper has been defined.
    if (objectMap.find(type)!=objectMap.end())
    {
        // Do the mapping JSON -> properties
        DisplayObject *obj=instance(objectMap[type], value);
        
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
    
    return loadString(jsonStr);
}