//
//  ToggleButton.h
//  


#ifndef _SimpleButton_h
#define _SimpleButton_h

#include "SimpleButton.h"

typedef enum{
    DEFAULT,
    ON_STATE,
    OFF_STATE
}ToggleState;

class BitmapSprite;
class SimpleToggle:public SimpleButton{
public:
    
    SimpleToggle();
    SimpleToggle(string inPath);
    
    void init();
    void loadDir(string inDir);
    void loadImage(ToggleState thisState, string inDir);
    
    
    void flipToggle();
    void renderFont(); // bk: fix
    bool isOn;
    
    ToggleState toggleState;
    
    string buttonTxt;
    ofTrueTypeFont avenir;

    
protected:
    
    BitmapSprite* image_on;
    BitmapSprite* image_off;
    
    ofDirectory dir;
    ofDirectory subDir;

    void onPress(int x, int y, int button);
    void onRelease(int x, int y, int button);
    void onReleaseOutside(int x, int y, int button);
    

    
private:
    
};

#endif
