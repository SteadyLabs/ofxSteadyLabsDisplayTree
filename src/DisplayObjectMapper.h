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
#include "FlipBookSprite.h"

/**
 * Abstract base class that maps value from json node to any base sprite.
 * For custom BaseSprite classes, you'll have to write your own subclass
 * of DisplayObjectMapper and register it with your DisplayObjectLoader
 * using it's addMapper() method.
 */
class DisplayObjectMapper {
public:
    // Constructs the display object and calls map() to assign properties.
    virtual DisplayObject *build(DisplayObject *parentObj, Json::Value value);
    
    // Does the actual mapping of JSON -> properties.
    virtual void map(DisplayObject *parentObj, DisplayObject *object, Json::Value value);
    
    // returns an instance of whatever object this is mapping.
    virtual DisplayObject *newInstance() { return NULL; }
};

/**
 * BaseSprite mapper
 */
class BaseSpriteMapper: public DisplayObjectMapper {
    DisplayObject *newInstance();
};

/**
 * BitmapSprite mapper
 */
class BitmapSpriteMapper: public DisplayObjectMapper {
    void map(DisplayObject *parentObj, DisplayObject *object, Json::Value value);
    DisplayObject *newInstance();
};


/**
 * BitmapSequence mapper
 */
class BitmapSequenceMapper: public DisplayObjectMapper {
    void map(DisplayObject *parentObj, DisplayObject *object, Json::Value value);
    DisplayObject *newInstance();
};


/**
 * ButtonSprite mapper
 */
class ButtonSpriteMapper: public DisplayObjectMapper {
    void map(DisplayObject *parentObj, DisplayObject *object, Json::Value value);
    DisplayObject *newInstance();
};


/**
 * VideoSprite mapper
 */
class VideoSpriteMapper: public DisplayObjectMapper {
    void map(DisplayObject *parentObj, DisplayObject *object, Json::Value value);
    DisplayObject *newInstance();
};



/**
 * VideoSprite mapper
 */
class FlipBookSpriteMapper: public DisplayObjectMapper {
    void map(DisplayObject *parentObj, DisplayObject *object, Json::Value value);
    DisplayObject *newInstance();
};


#endif
