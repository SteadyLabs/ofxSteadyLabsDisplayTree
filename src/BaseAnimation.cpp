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

BaseAnimation::BaseAnimation(DisplayObjectAnimator *theAnimator, DisplayObject *theTarget, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    next=NULL;
    animator=theAnimator;
    tweener=new tween::Tweener();
    param=NULL;
}
    
BaseAnimation::~BaseAnimation()
{
    delete tweener;
    
    if (param)
        delete param;
}

void BaseAnimation::update()
{
    tweener->step(ofGetElapsedTimeMillis());
    
    if (tweener->finished)
    {
        if (this->next)
            animator->addAnimation(this->next);
        
        this->next=NULL;
        animator->removeAnimation(this);
    }
}


#pragma mark - FadeAnimation

FadeAnimation::FadeAnimation(DisplayObjectAnimator *theAnimator, DisplayObject *theTarget, float alpha, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theAnimator, theTarget, duration, transition, equation)
{
    param=new tween::TweenerParam(duration,transition,equation);
    param->addProperty(&theTarget->alpha, alpha);
    tweener->addTween(*param);
}


#pragma mark - MoveAnimation

MoveAnimation::MoveAnimation(DisplayObjectAnimator *theAnimator, DisplayObject *theTarget, int x, int y, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theAnimator,theTarget,duration,transition,equation)
{
    param=new tween::TweenerParam(duration,transition,equation);
    param->addProperty(&theTarget->x, x);
    param->addProperty(&theTarget->y, y);
    tweener->addTween(*param);
}


#pragma mark - ResizeAnimation

ScaleAnimation::ScaleAnimation(DisplayObjectAnimator *theAnimator, DisplayObject *theTarget, float scaleX, float scaleY, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theAnimator,theTarget,duration,transition,equation)
{
    param=new tween::TweenerParam(duration,transition,equation);
    param->addProperty(&theTarget->scaleX, scaleX);
    param->addProperty(&theTarget->scaleY, scaleY);
    tweener->addTween(*param);
}


#pragma mark - ZoomAnimation

RotateAnimation::RotateAnimation(DisplayObjectAnimator *theAnimator, DisplayObject *theTarget, float rotation, int duration, AnimatorTransition transition, AnimatorEquation equation) : BaseAnimation(theAnimator,theTarget,duration,transition,equation)
{
    param=new tween::TweenerParam(duration,transition,equation);
    param->addProperty(&theTarget->rotation, rotation);
    tweener->addTween(*param);

}

#pragma mark - PropertyAnimation

PropertyAnimation::PropertyAnimation(DisplayObjectAnimator *theAnimator, DisplayObject *theTarget, float *propertyValue, float finalValue, int duration, AnimatorTransition transition, AnimatorEquation equation): BaseAnimation(theAnimator,theTarget,duration,transition,equation)
{
    param=new tween::TweenerParam(duration,transition,equation);
    param->addProperty(propertyValue, finalValue);
    tweener->addTween(*param);
    
}