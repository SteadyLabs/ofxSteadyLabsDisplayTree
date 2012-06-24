//
//  BaseAnimator.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/21/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_BaseAnimation_h
#define nikeolympics_BaseAnimation_h

#include "Between.h"

class DisplayObject;

class BaseAnimation {
protected:
    Between *tweener;
public:
    BaseAnimation *next;
    
    BaseAnimation(DisplayObject *theTarget, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    virtual ~BaseAnimation();
    
    virtual bool update();
};

class FadeAnimation : public BaseAnimation {
public:
    FadeAnimation(DisplayObject *theTarget, float alpha, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);

};

class MoveAnimation : public BaseAnimation {
public:
    MoveAnimation(DisplayObject *theTarget, int x, int y, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
};

class ScaleAnimation : public BaseAnimation {
public:
    ScaleAnimation(DisplayObject *theTarget, float scaleX, float scaleY, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
};

class RotateAnimation : public BaseAnimation {
public:
    RotateAnimation(DisplayObject *theTarget, float rotation, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
};


class PropertyAnimation : public BaseAnimation {
public:
    PropertyAnimation(DisplayObject *theTarget, float *propertyValue, float finalValue, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
};

#endif
