//
//  DisplayObjectMapper.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/2/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_DisplayObjectMapper_h
#define nikeolympics_DisplayObjectMapper_h

#include "json.h"
#include "DisplayObject.h"
#include "BitmapSprite.h"
#include "BitmapSequence.h"
#include "ButtonSprite.h"
#include "VideoSprite.h"

#define getFloatFromUint(num) ofToFloat(ofToString(num))

/**
 * Abstract base class that maps value from json node to any base sprite.
 * For custom BaseSprite classes, you'll have to write your own subclass
 * of DisplayObjectMapper and register it with your DisplayObjectLoader
 * using it's addMapper() method.
 */
class DisplayObjectMapper {
public:
    // Constructs the display object and calls map() to assign properties.
    virtual DisplayObject *build(Json::Value value) { return nil; };
    
    // Does the actual mapping of JSON -> properties.
    virtual void map(DisplayObject *object, Json::Value value);
};

/**
 * BitmapSprite mapper
 */
class BitmapSpriteMapper: public DisplayObjectMapper {
    DisplayObject *build(Json::Value value);
    void map(DisplayObject *object, Json::Value value);
};


/**
 * BitmapSequence mapper
 */
class BitmapSequenceMapper: public DisplayObjectMapper {
    DisplayObject *build(Json::Value value);
    void map(DisplayObject *object, Json::Value value);
};


/**
 * ButtonSprite mapper
 */
class ButtonSpriteMapper: public DisplayObjectMapper {
    DisplayObject *build(Json::Value value);
    void map(DisplayObject *object, Json::Value value);
};


/**
 * VideoSprite mapper
 */
class VideoSpriteMapper: public DisplayObjectMapper {
    DisplayObject *build(Json::Value value);
    void map(DisplayObject *object, Json::Value value);
};

#endif
