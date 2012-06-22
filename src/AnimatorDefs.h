//
//  AnimatorDefs.h
//  nikeolympics
//
//  Created by Jon Gilkison on 6/22/12.
//  Copyright (c) 2012 Interfacelab LLC. All rights reserved.
//

#ifndef nikeolympics_AnimatorDefs_h
#define nikeolympics_AnimatorDefs_h

#define DOA_DEFAULT_TRANSITION EXPO
#define DOA_DEFAULT_EQUATION EASE_OUT
#define DOA_DEFAULT_DURATION 2000

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


#endif
