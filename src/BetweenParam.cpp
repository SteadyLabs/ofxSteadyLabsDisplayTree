//
//  BetweenParam.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/24/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>

#include "BetweenParam.h"

BetweenParam::BetweenParam(float *theValue, float theFinalValue)
{
    startValue=*theValue;
    value=theValue;
    finalValue=theFinalValue;
    valueRange=finalValue-startValue;
}
