//
//  BaseAnimator.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/21/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>
#include "BaseAnimation.h"
#include "DisplayObject.h"
#include "DisplayObjectAnimator.h"

#pragma mark - BaseAnimation

BaseAnimation::BaseAnimation(DisplayObject *theTarget, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    next=NULL;
    tweener=new Between(duration,transition,equation);
}
    
BaseAnimation::~BaseAnimation()
{
    delete tweener;
}

bool BaseAnimation::update()
{
    return tweener->update();
}


#pragma mark - FadeAnimation

FadeAnimation::FadeAnimation(DisplayObject *theTarget, float alpha, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theTarget, duration, transition, equation)
{
    tweener->addParam(&theTarget->alpha, alpha);
}


#pragma mark - MoveAnimation

MoveAnimation::MoveAnimation(DisplayObject *theTarget, int x, int y, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theTarget,duration,transition,equation)
{
    tweener->addParam(&theTarget->x, x);
    tweener->addParam(&theTarget->y, y);
}


#pragma mark - ResizeAnimation

ScaleAnimation::ScaleAnimation(DisplayObject *theTarget, float scaleX, float scaleY, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theTarget,duration,transition,equation)
{
    tweener->addParam(&theTarget->scaleX, scaleX);
    tweener->addParam(&theTarget->scaleY, scaleY);
}


#pragma mark - ZoomAnimation

RotateAnimation::RotateAnimation(DisplayObject *theTarget, float rotation, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theTarget,duration,transition,equation)
{
    tweener->addParam(&theTarget->rotation, rotation);
}

#pragma mark - PropertyAnimation

PropertyAnimation::PropertyAnimation(DisplayObject *theTarget, float *propertyValue, float finalValue, int duration, AnimatorTransition transition, AnimatorEquation equation): BaseAnimation(theTarget,duration,transition,equation)
{
    tweener->addParam(propertyValue, finalValue);
}