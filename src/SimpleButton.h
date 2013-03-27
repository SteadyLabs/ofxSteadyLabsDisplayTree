//
//  SimpleButton.h
//  NikePro
//
//  Created by Michael Manh on 10/25/12.
//  Copyright (c) 2012 Uberlabs. All rights reserved.
//

#ifndef NikePro_SimpleButton_h
#define NikePro_SimpleButton_h

#include "BaseSprite.h"

class BitmapSprite;
class SimpleButton:public BaseSprite{
public:
    static string ON_PRESS;
    static string ON_RELEASE;
    static string ON_RELEASE_OUTSIDE;
    
    SimpleButton();
    SimpleButton(string inPath);
    void loadFile( string inPath );
    
    void init();
    
protected:
    BitmapSprite* image;

    void onPress(int x, int y, int button);
    void onRelease(int x, int y, int button);
    void onReleaseOutside(int x, int y, int button);
   

    
private:
    
};

#endif
