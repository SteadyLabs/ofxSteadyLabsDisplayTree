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
    virtual DisplayObject *load(string filename);
    
    /// Adds a map for custom BaseSprite classes to parse from file
    void addMapper(string tag, DisplayObjectMapper *mapper);
protected:
    /// Map tags to mappers
    namedObjectMap objectMap;

    /// Maps the attributes of the json node to a new instance
    /// via a DisplayObjectMapper and adds to parent object.
    virtual void mapValue(Json::Value value, DisplayObject *parent);
};


#endif
