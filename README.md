#Steady Labs Display Tree

##Introduction
Steady ltd creates interactive installations. The openframeworks community has provided a great starting point, but we found it was limited for building more complex states and event management. To address this, we created the display tree to mimic some of the parenting and event behaviors like those in Adobe's flash Actionscript 3, but with the capability to build on these behaviors that C++ can provide us.

##DisplayObject
The DisplayObject takes its names from a similar object in AS3. Its most important aspects are its capability transform and to nest transformations. Say you have a "bicycle" object with two "wheel" objects (children of the bicycle object), if you transform the bicycle (translate, scale and rotate), the wheels transform with it. DisplayObjects have the capability for scaleX, scaleY, alpha, rotation, and x, y translations. We also (experimentally) have added registration points, if you want to rotate/scale/translate around a point that is not the upper left of an object.

`object->x = 100;//move right 100 px`

`object->rotation = 90; //rotate object 90 degrees`

`object->scaleX = object->scaleY = 1.5; //scale to 150% normal size`

`object->alpha = 0.5f; //set to 50% opacity`

To add a child object to a displayObject, just do:

 `object->addChild( child );`

##Drawing
Younger siblings (added later) are drawn after older siblings. So if you add two wheels and then a frame to a bicycle object, the frame would be the last to draw, and it would draw on top of the wheels. All of the frames children (handles, kickstand) will draw after all of the wheel's children (spokes, tires, etc) as well. Slightly more formally, this is known as depth-first tree traversal.

Any object that extends displayObject can override the render function, which happens during the draw. With this capability, custom objects can add functionality. We have several of these custom object premade, a bitmap object, a bitmap sequence, button objects, even a video object. Try them out!

##Phases
The normal ofx loops goes update, draw. Pretty simple. We added one more: event. So it goes, update->draw->process events

This way, an event manager can collect events and only execute them in a single phase, and the developer can be certain there won't be events popping up in the middle of an update. We have written one for mouse events, and the model can be followed for any other events.

##Events
All DisplayObjects extend Dispatcher, which gives them the capability to dispatch an event specified by an unique string. Additionally, it can dispatch a message with each event. For instance, the wheels can listen to the "brake" event from the frame, and can decelerate. Additionally, the brake event can also specify a second string like "slowly" or "hard", to modify how quickly the wheels decelerate.

It's easy, just do:


`string eventType = "brake";`

`string eventMessage = "softly";`

`frame->addListener( eventType, wheel1, &Wheel::onBrake );`

`frame->dispatchEvent( eventType, eventMessage);`


##Inputs
In our projects, we have had to do a variety of inputs, keyboard, mouse, touch, and kinect gestures. Instead of wrapping all of this functionality directly into the DisplayObject, it sits in an InteractionEnabler. We have included one such enabler, the `MouseEnabler` by default into the DisplayObject. It collects the events throughout the phases and releases them during the event processing phase (which has to be explicitly called in the app's update function). 

`MouseController::processEvents();`

The reason to do this is two fold: first, it lets us separate code and functionality, and avoid compiling it in when its not needed. If you aren't using a touch library or a Kinect gesture library, it won't be compiled into the base object. We leave mouseEnabler in there, but you could modify displayObject so it doesn't have it anymore. Second, we can have z-depth occlusion for the mouse, so rolling over a the frame will prevent it from rolling over the wheel.

##Examples
Examples should compile from their current folder. 'openFrameworks/addons/ofxSteadyLabsDisplayTree/examples/'

##JSON Loader
For the more complex applications, you might want to do all your loading from a json file. Our json loader will walk through it, instantiate the objects you will need, and also load the necessary files. To reference these objects in your code after they've been loaded, just use `getChildByName( childName )' .

##Feedback
We've been using this library for a long time now, and wanted to bring it to the community. If you have any question or suggestions please direct them to labs@steadyltd.com

And have fun creating!