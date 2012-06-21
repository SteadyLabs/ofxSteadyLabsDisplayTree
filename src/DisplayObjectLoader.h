//
//  DisplayObjectLoader.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/2/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_DisplayObjectLoader_h
#define nikeolympics_DisplayObjectLoader_h

#include <string>
#include <map>

#include "json.h"
#include "DisplayObjectMapper.h"
#include "DisplayObject.h"

/**
 * ALoader class for loading scene graph from file.
 * TODO: Refactor JSON into separate class, needs value wrapper
 */
class DisplayObjectLoader {

    typedef map<string, DisplayObjectMapper*> namedObjectMap;
    
public:
    /// Constructor
    DisplayObjectLoader();
    
    /// Destructor
    virtual ~DisplayObjectLoader();
    
    /// Initializer
    virtual void init();

    /// Loads and constructs display tree from filename
    DisplayObject *loadFile(DisplayObject *parent, string filename);
    
    /// Loads and constructs display tree from a JSON string
    DisplayObject *loadString(DisplayObject *parent, string jsonStr);
    
    /// Adds a map for custom BaseSprite classes to parse from file
    void registerMapper(string tag, DisplayObjectMapper *mapper);
protected:
    /// Map tags to mappers
    namedObjectMap objectMap;

    /// Creates a new DisplayObject, and any children, and maps the attributes 
    /// of the json node to the new instance via a DisplayObjectMapper
    virtual DisplayObject *build(DisplayObject *parentObj, Json::Value value);
    
    // Creates the new instance
    virtual DisplayObject *instance(DisplayObject *parentObj, DisplayObjectMapper *mapper, Json::Value value);
    
    // Loads an include
    virtual DisplayObject *include(DisplayObject *parentObj, Json::Value value);
};


#endif
