//
//  JSONParser.cpp
//  examples
//
//  Created by Sebastian Lemery on 11/3/11.
//  Copyright 2011 STEADY. All rights reserved.
//

#include <iostream>
#include "JSONParser.h"

string JSONParser::readfile(string path) {
	string str,strTotal;
	ifstream in;
	in.open(ofToDataPath(path, true).c_str());
	getline(in,str);
	while ( in ) {
		strTotal += str;
		getline(in, str);
	}
	in.close();
	return strTotal;
}

Json::Value JSONParser::parse(string s) {
	string result;
	// std::cout<<"parsing JSON file : " << file_loc << endl;
    
	Json::Value tempJSONObj;
	
	bool parsingSuccessful = reader.parse( readfile( s ), tempJSONObj );
	if ( !parsingSuccessful ) {
		std::cout  << "Failed to parse JSON\n" << reader.getFormatedErrorMessages();
		throw;
	}
    
	return tempJSONObj;
	
    
}

float JSONParser::getFloatFromUint(uint num){
    string str = ofToString(num);
    float f = ofToFloat(str);
    return f;
}

void JSONParser::loadSpritesFromJSON(Json::Value spriteObj, BaseSprite* parentSprite)
{
    // std::cout<<"Scraping children..." << endl; // spriteObj << endl;
	
	for (int i = 0; i < spriteObj.size(); i++) 
	{
		
		BaseSprite* tempSprite;
		
		// Add children
		
		string spriteTypeString = spriteObj[i]["type"].asString();
		
		// Check type
		if( spriteTypeString == "base_sprite" )
		{
            BaseSprite* tempSprite;
			tempSprite = new BaseSprite();
            
            tempSprite->name = spriteObj[i]["id"].asString();
            tempSprite->x = getFloatFromUint(spriteObj[i]["x"].asUInt());
            tempSprite->y = getFloatFromUint(spriteObj[i]["y"].asUInt());
            tempSprite->visible = spriteObj[i]["visible"].asBool();
            
            parentSprite->addChild(tempSprite);
            
            // std::cout << "Added : " << tempSprite->name <<  " to " << parentSprite->name << " index of this child " << parentSprite->getIndexOfChild(tempSprite) << endl;
            
            
            // std::cout<< "Added : " << tempSprite->name <<  " to " << parentSprite->name << endl;
            
            loadSpritesFromJSON( spriteObj[i]["children"], tempSprite );
		}
		
		else if( spriteTypeString == "bitmap_sprite" )
		{	
            BitmapSprite* bitmapSprite;
            
			// Lame, but didn't like the BitmapSprite casting and wouldn't allow me to access loadFile
			if(spriteObj[i]["asset"].asString() == "tbd" ) 
			{
				bitmapSprite = new BitmapSprite();
			} else
			{
				bitmapSprite = new BitmapSprite();
                
                bitmapSprite->loadFile(spriteObj[i]["asset"].asString() );
			}
            
            bitmapSprite->name = spriteObj[i]["id"].asString();
            bitmapSprite->x = getFloatFromUint(spriteObj[i]["x"].asUInt());
            bitmapSprite->y = getFloatFromUint(spriteObj[i]["y"].asUInt());
            bitmapSprite->visible = spriteObj[i]["visible"].asBool();
            
            parentSprite->addChild(bitmapSprite);
            
            // std::cout << "Added : " << bitmapSprite->name <<  " to " << parentSprite->name << " index of this child " << parentSprite->getIndexOfChild(bitmapSprite) << endl;
            
            
            // std::cout<< "Added : " << tempSprite->name <<  " to " << parentSprite->name << endl;
            
            loadSpritesFromJSON( spriteObj[i]["children"], bitmapSprite );
		}
		
		else if( spriteTypeString == "video_sprite" )
		{	
            VideoSprite* videoSprite;
			
            if(spriteObj[i]["asset"].asString() == "tbd" ) 
			{
				videoSprite = new VideoSprite();
			} else
			{
				videoSprite = new VideoSprite(  );
                videoSprite->loadFile(spriteObj[i]["asset"].asString());
                
			}
            
            videoSprite->name = spriteObj[i]["id"].asString();
            videoSprite->x = getFloatFromUint(spriteObj[i]["x"].asUInt());
            videoSprite->y = getFloatFromUint(spriteObj[i]["y"].asUInt());
            videoSprite->visible = spriteObj[i]["visible"].asBool();
            
            
            parentSprite->addChild(videoSprite);
            
            // std::cout << "Added : " << videoSprite->name <<  " to " << parentSprite->name << " index of this child " << parentSprite->getIndexOfChild(videoSprite) << endl;
            
            
            // std::cout<< "Added : " << tempSprite->name <<  " to " << parentSprite->name << endl;
            
            loadSpritesFromJSON( spriteObj[i]["children"], videoSprite );
		}
		
		else if( spriteTypeString == "button_sprite" )
		{
            ButtonSprite* buttonSprite;
            
			if(spriteObj[i]["asset"].asString() == "tbd" ) 
			{
				buttonSprite = new ButtonSprite();
			} else
			{
				buttonSprite = new ButtonSprite(  );
                buttonSprite->loadFile(spriteObj[i]["asset"].asString());
			}
            
            buttonSprite->name = spriteObj[i]["id"].asString();
            buttonSprite->x = getFloatFromUint(spriteObj[i]["x"].asUInt());
            buttonSprite->y = getFloatFromUint(spriteObj[i]["y"].asUInt());
            buttonSprite->visible = spriteObj[i]["visible"].asBool();
            
            parentSprite->addChild(buttonSprite);
            
            // std::cout << "Added : " << buttonSprite->name <<  " to " << parentSprite->name << " index of this child " << parentSprite->getIndexOfChild(buttonSprite) << endl;
            
            
            // std::cout<< "Added : " << tempSprite->name <<  " to " << parentSprite->name << endl;
            
            loadSpritesFromJSON( spriteObj[i]["children"], buttonSprite );
		}
		
		else if( spriteTypeString == "sequence_sprite" )
		{
            BitmapSequence* bitmapSequence;
            
			if(spriteObj[i]["asset"].asString() == "tbd" ) 
			{
				bitmapSequence = new BitmapSequence();
			} else
			{
				bitmapSequence = new BitmapSequence( );
                bitmapSequence->loadDir(spriteObj[i]["asset"].asString());
			}
            
            bitmapSequence->name = spriteObj[i]["id"].asString();
            
            bitmapSequence->x = getFloatFromUint(spriteObj[i]["x"].asUInt());
            bitmapSequence->y = getFloatFromUint(spriteObj[i]["y"].asUInt());
            bitmapSequence->visible = spriteObj[i]["visible"].asBool();
            
            parentSprite->addChild(bitmapSequence);
            
            // std::cout << "Added : " << bitmapSequence->name <<  " to " << parentSprite->name << " index of this child " << parentSprite->getIndexOfChild(bitmapSequence) << endl;
            
            
            // std::cout<< "Added : " << tempSprite->name <<  " to " << parentSprite->name << endl;
            
            loadSpritesFromJSON( spriteObj[i]["children"], bitmapSequence );
		}
	}
}
