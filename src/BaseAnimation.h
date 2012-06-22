//
//  BaseAnimator.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/21/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_BaseAnimator_h
#define nikeolympics_BaseAnimator_h

#include "CPPTweener.h"

#define DOA_DEFAULT_TRANSITION EXPO
#define DOA_DEFAULT_EQUATION EASE_OUT
#define DOA_DEFAULT_DURATION 2000

class DisplayObject;

typedef enum {
    LINEAR,
    SINE,
    QUINT,
    QUART,
    QUAD,
    EXPO,
    ELASTIC,
    CUBIC,
    CIRC,
    BOUNCE,
    BACK
} AnimatorTransition;

typedef enum {
    EASE_IN,
    EASE_OUT,
    EASE_IN_OUT
} AnimatorEquation;

class BaseAnimation {
protected:
    tween::Tweener *tweener;
public:
    DisplayObject *target;

    bool active;
    float duration;
    BaseAnimation *next;
    
    BaseAnimation(DisplayObject *theTarget, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    virtual ~BaseAnimation();
    
    virtual void update();
};

class DisplayObjectAnimator {
private:
    bool chaining;
    BaseAnimation *lastAnimation;
public:
    vector<BaseAnimation *> animations;
    
    DisplayObjectAnimator();
    virtual ~DisplayObjectAnimator();
    
    void addAnimation(BaseAnimation *anim);
    void update();
    void cancelAnimations();
    
    DisplayObjectAnimator *fadeTo(float alpha, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    DisplayObjectAnimator *fadeIn(int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION) { return fadeTo(1.0f,duration,transition,equation); };
    DisplayObjectAnimator *fadeOut(int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION) { return fadeTo(0.0f,duration,transition,equation); };

    DisplayObjectAnimator *move(int x, int y, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    
    DisplayObjectAnimator *zoom(int x, int y, int w, int h, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    
    DisplayObjectAnimator *resize(int width, int height, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    
    DisplayObjectAnimator *chain();
};

class FadeAnimation : public BaseAnimation {
public:
    FadeAnimation(DisplayObject *theTarget, float alpha, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);

};

class MoveAnimation : public BaseAnimation {
public:
    MoveAnimation(DisplayObject *theTarget, int x, int y, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
};

class ResizeAnimation : public BaseAnimation {
public:
    ResizeAnimation(DisplayObject *theTarget, int width, int height, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
};

#endif
