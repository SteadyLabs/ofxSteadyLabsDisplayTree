//
//  BetweenParam.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/24/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_BetweenParam_h
#define nikeolympics_BetweenParam_h

class BetweenParam {
public:
    float *value;
    
    float startValue;
    float finalValue;
    float valueRange;
    
    BetweenParam(float *theValue, float finalValue);
};

#endif
