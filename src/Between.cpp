//
//  Between.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/24/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>

#include "ofMain.h"
#include "Between.h"


Between::Between(int theDuration, AnimatorTransition theTransition, AnimatorEquation theEquation)
{
    running=true;
    duration=theDuration;
    transition=theTransition;
    equation=theEquation;
    
    totalTime=0;
    startTime=lastTime=ofGetElapsedTimeMillis();
}

Between::~Between()
{
    for(int i=0; i<params.size(); i++)
        delete params[i];
}

void Between::addParam(float *value, float finalValue)
{
    params.push_back(new BetweenParam(value,finalValue));
}
    
bool Between::update()
{
    if (!running)
        return false;
    
    int ntime=ofGetElapsedTimeMillis();
    int delta=ntime-lastTime;
    lastTime=ntime;
    
    totalTime+=delta;
    
    if (totalTime>=duration)
    {
        for(int i=0; i<params.size(); i++)
            *params[i]->value=params[i]->finalValue;
        
        running=false;
    }
    else
    {
        for(int i=0; i<params.size(); i++)
            *params[i]->value=BetweenFuncs::run(transition, equation, totalTime, params[i]->startValue, params[i]->valueRange, duration);
    }
    
    return running;
}