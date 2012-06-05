//
//  DisplayObjectMapper.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/2/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>
#include "DisplayObjectMapper.h"

#pragma mark - DisplayObjectMapper

void DisplayObjectMapper::map(DisplayObject *object, Json::Value value)
{
    // Required properties
    if (!value["id"].isNull())
        object->name = value["id"].asString();
    
    if (!value["frame"].isNull())
    {
        Json::Value frame=value["frame"];
        object->x=frame[0U].asDouble();
        object->y=frame[1].asDouble();
        object->width=frame[2].asDouble();
        object->height=frame[3].asDouble();
    }

    if (!value["opaque"].isNull())
        object->opaque = value["opaque"].asBool();
    
    if (!value["background"].isNull())
    {
        Json::Value bg=value["background"];
        
        object->backgroundColor=ofColor(bg[0U].asUInt(),bg[1].asUInt(),bg[2].asUInt(),bg[3].asUInt());
    }

    if (!value["x"].isNull())
        object->x = value["x"].asDouble();
    
    if (!value["y"].isNull())
        object->y = value["y"].asDouble();
    
    if (!value["visible"].isNull())
        object->visible = value["visible"].asBool();
    
    if (!value["w"].isNull())
        object->width = value["w"].asDouble();
    
    if (!value["h"].isNull())
        object->height = value["h"].asDouble();
    
    if (!value["clipToBounds"].isNull())
        object->clipToBounds = value["clipToBounds"].asBool();

    if (!value["alpha"].isNull())
        object->alpha = value["alpha"].asDouble();
    
    if (!value["scaleX"].isNull())
        object->scaleX = value["scaleX"].asDouble();
    
    if (!value["scaleY"].isNull())
        object->scaleY = value["scaleY"].asDouble();
    
    if (!value["registrationX"].isNull())
        object->registrationX = value["registrationX"].asDouble();

    if (!value["registrationY"].isNull())
        object->registrationY = value["registrationY"].asDouble();
    
    if (!value["rotation"].isNull())
        object->rotation = value["rotation"].asDouble();
    
    // TODO: Blend Mode
    //object->blendMode;
}

#pragma mark - BitmapSpriteMapper

void BitmapSpriteMapper::map(DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(object,value);
    ((BitmapSprite *)object)->loadFile(value["asset"].asString());
}

DisplayObject *BitmapSpriteMapper::build(Json::Value value) 
{
    BitmapSprite *sprite=new BitmapSprite();
    map(sprite,value);
    
    return sprite;
}

#pragma mark - BitmapSequenceMapper

void BitmapSequenceMapper::map(DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(object,value);
    ((BitmapSequence *)object)->loadDir(value["asset"].asString());
}

DisplayObject *BitmapSequenceMapper::build(Json::Value value) 
{
    BitmapSequence *sprite=new BitmapSequence();
    map(sprite,value);
    
    return sprite;
}

#pragma mark - ButtonSpriteMapper

void ButtonSpriteMapper::map(DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(object,value);
    ((ButtonSprite *)object)->loadFile(value["asset"].asString());
}

DisplayObject *ButtonSpriteMapper::build(Json::Value value) 
{
    ButtonSprite *sprite=new ButtonSprite();
    map(sprite,value);
    
    return sprite;
}

#pragma mark - VideoSpriteMapper

void VideoSpriteMapper::map(DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(object,value);
    ((VideoSprite *)object)->loadFile(value["asset"].asString());
}

DisplayObject *VideoSpriteMapper::build(Json::Value value) 
{
    VideoSprite *sprite=new VideoSprite();
    map(sprite,value);
    
    return sprite;
}