//
//  BaseAnimator.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/21/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_DisplayObjectAnimator_h
#define nikeolympics_DisplayObjectAnimator_h

#include "AnimatorDefs.h"
#include "BaseAnimation.h"
#include "CPPTweener.h"


class DisplayObject;

/**
 * DisplayObjectAnimator manages the currently running list of animations for a given DisplayObject.
 *
 * You can run the animations concurrently or chain them:
 *
 * // move to 200,200 AND fade out
 * displayObject->animator->move(200,200)->fadeOut();
 *
 * // move to 200,200 THEN fade out
 * displayObject->animator->move(200,200)->then()->fadeOut();
 *
 * The above example do not clear out the currently running animations, they will be added to the list.
 * The stop() method will stop and clear out any running animations:
 * 
 * // stop other animations, move to 200,200 THEN fade out
 * displayObject->animator->stop()->move(200,200)->then()->fadeOut();
 */
class DisplayObjectAnimator {
private:
    bool chaining;
    BaseAnimation *lastAnimation;
    DisplayObject *target;
    std::vector<BaseAnimation *> deleteQueue;
public:
    std::vector<BaseAnimation *> animations;
    
    DisplayObjectAnimator(DisplayObject *theTarget);
    virtual ~DisplayObjectAnimator();
    
    void addAnimation(BaseAnimation *anim);
    void removeAnimation(BaseAnimation *anim);
    void update();
    
    DisplayObjectAnimator *stop();
    
    DisplayObjectAnimator *fadeTo(float alpha, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    DisplayObjectAnimator *fadeIn(int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION) { return fadeTo(1.0f,duration,transition,equation); };
    DisplayObjectAnimator *fadeOut(int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION) { return fadeTo(0.0f,duration,transition,equation); };
    
    DisplayObjectAnimator *move(int x, int y, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    
    DisplayObjectAnimator *scale(float scaleX, float scaleY, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    
    DisplayObjectAnimator *rotate(float rotation, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);
    
    DisplayObjectAnimator *property(float *propertyValue, float finalValue, int duration=DOA_DEFAULT_DURATION, AnimatorTransition transition=DOA_DEFAULT_TRANSITION, AnimatorEquation equation=DOA_DEFAULT_EQUATION);

    DisplayObjectAnimator *then();
};

#endif
