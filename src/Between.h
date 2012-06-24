//
//  Between.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/24/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_Between_h
#define nikeolympics_Between_h

#include "AnimatorDefs.h"
#include "BetweenFuncs.h"
#include "BetweenParam.h"

#include <vector>

class Between {
protected:
    int lastTime;
    int totalTime;
public:
    std::vector<BetweenParam *> params;
    bool running;
    
    AnimatorTransition transition;
    AnimatorEquation equation;

    int duration;
    int startTime;
    
    Between(int theDuration=DOA_DEFAULT_DURATION, AnimatorTransition theTransition=DOA_DEFAULT_TRANSITION, AnimatorEquation theEquation=DOA_DEFAULT_EQUATION);
    virtual ~Between();
    
    void addParam(float *theValue, float theFinalValue);
    
    bool update();
};

#endif
