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
    object->name = value["id"].asString();
    object->x = getFloatFromUint(value["x"].asUInt());
    object->y = getFloatFromUint(value["y"].asUInt());
    object->visible = value["visible"].asBool();
    
    // Optional properites
    if (!value["alpha"].isNull())
        object->alpha = getFloatFromUint(value["alpha"].asUInt());
    
    if (!value["scaleX"].isNull())
        object->scaleX = getFloatFromUint(value["scaleX"].asUInt());
    
    if (!value["scaleY"].isNull())
        object->scaleY = getFloatFromUint(value["scaleY"].asUInt());
    
    if (!value["registrationX"].isNull())
        object->registrationX = getFloatFromUint(value["registrationX"].asUInt());

    if (!value["registrationY"].isNull())
        object->registrationY = getFloatFromUint(value["registrationY"].asUInt());
    
    if (!value["rotation"].isNull())
        object->rotation = getFloatFromUint(value["rotation"].asUInt());
    
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