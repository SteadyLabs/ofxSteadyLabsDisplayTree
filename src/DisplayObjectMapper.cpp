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

void DisplayObjectMapper::map(DisplayObject *parentObj, DisplayObject *object, Json::Value value)
{
    if (parentObj)
        parentObj->addChild(object);
    
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
    
    if (!value["clipMargins"].isNull())
        object->clipMargins = ofVec2f(value["clipMargins"][0U].asDouble(),value["clipMargins"][1].asDouble());

    if (!value["alpha"].isNull())
        object->alpha = value["alpha"].asDouble();
    
    if (!value["frame"].isNull())
    {
        Json::Value frame=value["frame"];
        object->x=frame[0U].asDouble();
        object->y=frame[1].asDouble();
        object->width=frame[2].asDouble();
        object->height=frame[3].asDouble();
    }

    if (!value["scale"].isNull())
    {
        Json::Value scale=value["scale"];
        object->scaleX=scale[0U].asDouble();
        object->scaleY=scale[1].asDouble();
    }

    if (!value["registration"].isNull())
    {
        Json::Value registration=value["registration"];
        object->registrationX=registration[0U].asDouble();
        object->registrationY=registration[1].asDouble();
    }
    
    if (!value["rotation"].isNull())
        object->rotation = value["rotation"].asDouble();
    
    // TODO: Blend Mode
    //object->blendMode;
}


DisplayObject *DisplayObjectMapper::build(DisplayObject *parentObj, Json::Value value) 
{
    DisplayObject *sprite=newInstance();
    
    if (sprite)
        map(parentObj,sprite,value);
    
    return sprite;
}

#pragma mark - BaseSpriteMapper

DisplayObject *BaseSpriteMapper::newInstance()
{
    return new BaseSprite();
}

#pragma mark - BitmapSpriteMapper

void BitmapSpriteMapper::map(DisplayObject *parentObj, DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(parentObj, object,value);
    ((BitmapSprite *)object)->loadFile(value["asset"].asString());
}

DisplayObject *BitmapSpriteMapper::newInstance()
{
    return new BitmapSprite();
}


#pragma mark - BitmapSequenceMapper

void BitmapSequenceMapper::map(DisplayObject *parentObj, DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(parentObj, object,value);
    ((BitmapSequence *)object)->loadDir(value["asset"].asString());
}

DisplayObject *BitmapSequenceMapper::newInstance()
{
    return new BitmapSequence();
}


#pragma mark - ButtonSpriteMapper

void ButtonSpriteMapper::map(DisplayObject *parentObj, DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(parentObj, object,value);
    ((ButtonSprite *)object)->loadFile(value["asset"].asString());
}

DisplayObject *ButtonSpriteMapper::newInstance()
{
    return new ButtonSprite();
}


#pragma mark - VideoSpriteMapper

void VideoSpriteMapper::map(DisplayObject *parentObj, DisplayObject *object, Json::Value value)
{
    DisplayObjectMapper::map(parentObj, object,value);
    ((VideoSprite *)object)->loadFile(value["asset"].asString());
}

DisplayObject *VideoSpriteMapper::newInstance()
{
    return new VideoSprite();
}

