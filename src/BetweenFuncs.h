//
//  BetweenFuncs.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/24/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_BetweenFuncs_h
#define nikeolympics_BetweenFuncs_h

#include <math.h>
#include "AnimatorDefs.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

class BetweenFuncs
{
public:
    static inline float linear(AnimatorEquation e, float t,float b , float c, float d)
    {
        return c*t/d + b;
    }

    static inline float sine(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return -c * cos(t/d * (PI/2)) + c + b;;
            case EASE_OUT:
                return c * sin(t/d * (PI/2)) + b;
            default:
                return -c/2 * (cos(PI*t/d) - 1) + b;;
        }
    }
    
    static inline float quint(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return c*(t/=d)*t*t*t*t + b;
            case EASE_OUT:
                return c*((t=t/d-1)*t*t*t*t + 1) + b;
            default:
                if ((t/=d/2) < 1) 
                    return c/2*t*t*t*t*t + b;
                return c/2*((t-=2)*t*t*t*t + 2) + b;
        }
    }
    
    static inline float quart(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return c*(t/=d)*t*t*t + b;
            case EASE_OUT:
                return -c * ((t=t/d-1)*t*t*t - 1) + b;
            default:
                if ((t/=d/2) < 1) 
                    return c/2*t*t*t*t + b;
                return -c/2 * ((t-=2)*t*t*t - 2) + b;
        }
    }
    
    static inline float quad(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return c*(t/=d)*t + b;
            case EASE_OUT:
                return -c *(t/=d)*(t-2) + b;
            default:
                if ((t/=d/2) < 1) 
                    return ((c/2)*(t*t)) + b;
                return -c/2 * (((t-2)*(--t)) - 1) + b;
        }
    }
    
    static inline float expo(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
            case EASE_OUT:
                return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
            default:
                if (t==0) return b;
                if (t==d) return b+c;
                if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
                return c/2 * (-pow(2, -10 * --t) + 2) + b;
        }
    }
    
    static inline float elastic(AnimatorEquation e, float t,float b , float c, float d)
    {
        float p,a,s,postFix;
        
        switch(e)
        {
            case EASE_IN:
                if (t==0) return b;  if ((t/=d)==1) return b+c;
                p=d*.3f;
                a=c;
                s=p/4;
                postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
                return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
            case EASE_OUT:
                if (t==0) return b;  if ((t/=d)==1) return b+c;
                p=d*.3f;
                a=c;
                s=p/4;
                return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
            default:
                if (t==0) return b;  if ((t/=d/2)==2) return b+c;
                float p=d*(.3f*1.5f);
                float a=c;
                float s=p/4;
                
                if (t < 1) {
                    float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
                    return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
                }
                float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
                return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
        }
    }
    
    
    static inline float cubic(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return c*(t/=d)*t*t + b;
            case EASE_OUT:
                return c*((t=t/d-1)*t*t + 1) + b;
            default:
                if ((t/=d/2) < 1) return c/2*t*t*t + b;
                return c/2*((t-=2)*t*t + 2) + b;
        }
    }
    
    static inline float circ(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
            case EASE_OUT:
                return c * sqrt(1 - (t=t/d-1)*t) + b;
            default:
                if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
                return c/2 * (sqrt(1 - t*(t-=2)) + 1) + b;
        }
    }
    
    static inline float bounce(AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(e)
        {
            case EASE_IN:
                return c - bounce(EASE_OUT,d-t, 0, c, d) + b;
            case EASE_OUT:
                if ((t/=d) < (1/2.75f)) {
                    return c*(7.5625f*t*t) + b;
                } else if (t < (2/2.75f)) {
                    float postFix = t-=(1.5f/2.75f);
                    return c*(7.5625f*(postFix)*t + .75f) + b;
                } else if (t < (2.5/2.75)) {
                    float postFix = t-=(2.25f/2.75f);
                    return c*(7.5625f*(postFix)*t + .9375f) + b;
                } else {
                    float postFix = t-=(2.625f/2.75f);
                    return c*(7.5625f*(postFix)*t + .984375f) + b;
                }
            default:
                if (t < d/2) return bounce(EASE_IN,t*2, 0, c, d) * .5f + b;
                else return bounce(EASE_OUT,t*2-d, 0, c, d) * .5f + c*.5f + b;
        }
    }
    
    static inline float back(AnimatorEquation e, float t,float b , float c, float d)
    {
        float s, postFix;
        
        switch(e)
        {
            case EASE_IN:
                s = 1.70158f;
                postFix = t/=d;
                return c*(postFix)*t*((s+1)*t - s) + b;
            case EASE_OUT:
                s = 1.70158f;
                return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
            default:
                s = 1.70158f;
                if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
                float postFix = t-=2;
                return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
        }
    }
     
    static inline float run(AnimatorTransition trans, AnimatorEquation e, float t,float b , float c, float d)
    {
        switch(trans)
        {
            case LINEAR: return linear(e,t,b,c,d);
            case SINE: return sine(e,t,b,c,d);
            case QUINT: return quint(e,t,b,c,d);
            case QUART: return quart(e,t,b,c,d);
            case QUAD: return quad(e,t,b,c,d);
            case EXPO: return expo(e,t,b,c,d);
            case ELASTIC: return elastic(e,t,b,c,d);
            case CUBIC: return cubic(e,t,b,c,d);
            case CIRC: return circ(e,t,b,c,d);
            case BOUNCE: return bounce(e,t,b,c,d);
            case BACK: return back(e,t,b,c,d);
        }
    }
};

#endif
