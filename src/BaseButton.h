//
//  BaseButton.h
//  NikePro
//
//  Created by Michael Manh on 10/25/12.
//  Copyright (c) 2012 Uberlabs. All rights reserved.
//

#ifndef NikePro_BaseButton_h
#define NikePro_BaseButton_h

#include "BaseSprite.h"

typedef enum{
    ROLLOVER,
    ROLLOUT,
    PRESS,
    DEFAULT
}ButtonState;


class BaseButton: public BaseSprite{
    
public:
    
    BaseButton( string inPath ):BaseSprite(){
        
            init();
            loadFile( inPath );
        
    }
    
    static string ON_PRESS;
    static string ON_RELEASE;
    static string ON_RELEASE_OUTSIDE;
    static string ON_ROLLOVER;
    static string ON_ROLLOUT;
    
    virtual void loadFile( string inPath );
    
protected:
    virtual void onPress(int x, int y, int button);
    virtual void onRelease(int x, int y, int button);
    virtual void onRollOver(int x, int y);
    virtual void onReleaseOutside(int x, int y, int button);
	virtual void onRollOut();
    
    virtual void init();
private:
};

#endif
