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
}

void DisplayObjectLoader::mapValue(Json::Value value, DisplayObject *parent)
{
    string type=value["type"].asString();
    
    // make sure a mapper has been defined.
    if (objectMap.find(type)!=objectMap.end())
    {
        // Do the mapping JSON -> properties
        DisplayObject *obj=objectMap[type]->build(value);
        
        if (obj)
            parent->addChild(obj);
        
        // Do any child elements
        if (!value["children"].isNull())
            for(int i=0; i<value["children"].size(); i++)
                mapValue(value["children"][i],obj);
    }
    
}

void DisplayObjectLoader::addMapper(string tag, DisplayObjectMapper *mapper)
{
    objectMap[tag]=mapper;
}

DisplayObject *DisplayObjectLoader::load(string filename)
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
    
    // parse into a json object
	Json::Value jsonObj;
    Json::Reader reader;
	
	bool parsingSuccessful = reader.parse(jsonStr, jsonObj);
	if ( !parsingSuccessful ) {
		std::cout  << "Failed to parse JSON\n" << reader.getFormatedErrorMessages();
		throw;
	}
    
    // build the graph
    BaseSprite *root=new BaseSprite();
    
    for (int i=0; i<jsonObj.size(); i++)
        mapValue(jsonObj[i],root);
    
    return root;
}