//
//  DisplayObjectAnimator.cpp
//  nikeolympics
//
//  Created by Jon Gilkison on 6/22/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#include <iostream>

#include "DisplayObjectAnimator.h"
#include "BaseAnimation.h"
#include "DisplayObject.h"

DisplayObjectAnimator::DisplayObjectAnimator(DisplayObject *theTarget)
{
    target=theTarget;
    chaining=false;
    lastAnimation=NULL;
}

DisplayObjectAnimator::~DisplayObjectAnimator()
{
    stop();
    
    for(int i=0; i<deleteQueue.size(); i++)
        delete deleteQueue[i];
}

void DisplayObjectAnimator::addAnimation(BaseAnimation *anim)
{
    if ((chaining) && (lastAnimation))
    {
        lastAnimation->next=anim;
    }
    else
    {
        lastAnimation=anim;
        animations.push_back(anim);
    }

    for(int i=0; i<deleteQueue.size(); i++)
        delete deleteQueue[i];
     deleteQueue.clear();
    
    chaining=false;
}


void DisplayObjectAnimator::removeAnimation(BaseAnimation *anim)
{
    if (lastAnimation==anim)
        lastAnimation=NULL;
    
    for(int i=0; i<animations.size(); i++)
        if (animations[i]==anim)
        {
            animations.erase(animations.begin()+i);
            deleteQueue.push_back(anim);
            
            cout << target->name << " REMOVED alpha: " << animations.size() << endl;
            
            if (anim->next)
            {
                removeAnimation(anim->next);
                anim->next=NULL;
            }
            
            return;
        }

    deleteQueue.push_back(anim);
}

void DisplayObjectAnimator::update()
{
    vector<BaseAnimation *>current;
    current.assign(animations.begin(),animations.end());
    
    for(int i=0; i<current.size(); i++)
    {
        if (!current[i]->update())
        {
            if (current[i]->next)
                addAnimation(current[i]->next);
            
            current[i]->next=NULL;
            removeAnimation(current[i]);
        }
    }
}

DisplayObjectAnimator *DisplayObjectAnimator::stop()
{
    chaining=false;
    
    while(animations.size())
        removeAnimation(animations[0]);
    
    return this;
}

DisplayObjectAnimator *DisplayObjectAnimator::fadeTo(float alpha, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    addAnimation(new FadeAnimation( target, alpha, duration, transition, equation));
    return this;
}

DisplayObjectAnimator *DisplayObjectAnimator::move(int x, int y, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    addAnimation(new MoveAnimation( target, x, y, duration, transition, equation));
    return this;
}
    
DisplayObjectAnimator *DisplayObjectAnimator::scale(float scaleX, float scaleY, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    addAnimation(new ScaleAnimation( target, scaleX, scaleY, duration, transition, equation));
    return this;
}


DisplayObjectAnimator *DisplayObjectAnimator::rotate(float rotation, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    addAnimation(new RotateAnimation( target, rotation, duration, transition, equation));
    return this;
}

DisplayObjectAnimator *DisplayObjectAnimator::property(float *propertyValue, float finalValue, int duration, AnimatorTransition transition, AnimatorEquation equation)
{
    addAnimation(new PropertyAnimation( target, propertyValue, finalValue, duration, transition, equation));
    return this;
}
    
DisplayObjectAnimator *DisplayObjectAnimator::then()
{
    chaining=true;
    return this;
}
