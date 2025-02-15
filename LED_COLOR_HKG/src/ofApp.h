#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
//#include "ofxGui.h"
#include "ofEvents.h"
#include "ofArduino.h"
#include "ofSerial.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    ofArduino ard;
    bool bSetupArduino;
    //    ofxJSONElement jsonMilan;
    ofxJSONElement jsonHkg;
    //ofxJSONElement jsonNc;
    //    ofxPanel gui;
    //    ofxIntSlider time;
    
private:
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
    
    string buttonState;
    string potValue;
    
    
};
