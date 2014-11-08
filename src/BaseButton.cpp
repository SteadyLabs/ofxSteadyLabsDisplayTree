//
//  BaseButton.cpp
//  NikePro
//
//  Created by Michael Manh on 10/25/12.
//  Copyright (c) 2012 Uberlabs. All rights reserved.
//

#include <iostream>
#include "BaseButton.h"


string BaseButton::ON_PRESS = "onPress";
string BaseButton::ON_RELEASE = "onRelease";
string BaseButton::ON_RELEASE_OUTSIDE = "onReleaseOutside";
string BaseButton::ON_ROLLOVER = "onRollover";
string BaseButton::ON_ROLLOUT = "onRollout";


void BaseButton::init(){
    enableMouseEvents();
}


