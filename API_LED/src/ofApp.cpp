#include "ofApp.h"
#include "ofSerial.h"
#include "ofArduino.h"

float a;
// average 12 hours a day, 12 interval
float milanTime, milanSunrise, milanSunset;
float milanCloud;
string milanSummary;
int r, g, b;
bool milan;

//--------------------------------------------------------------

void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    std::string urlMilan = "https://api.darksky.net/forecast/352dc2df4f80b08a0b3d0b71250b3b7b/45.4642,9.1900";
//    std::string urlHkg = "https://api.darksky.net/forecast/352dc2df4f80b08a0b3d0b71250b3b7b/22.3193,114.1694";
//    std::string urlNc = "https://api.darksky.net/forecast/352dc2df4f80b08a0b3d0b71250b3b7b/35.7796,-78.6382";
    bool milan = jsonMilan.open(urlMilan);
    int baud = 57600;
    ard.connect("/dev/cu.usbmodem14601",baud);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateArduino();
    milanTime = jsonMilan["currently"]["time"].asFloat();
    milanSunrise = jsonMilan["daily"]["data"][0]["sunriseTime"].asFloat();
    milanSunset = jsonMilan["daily"]["data"][0]["sunsetTime"].asFloat();
    milanCloud = jsonMilan["currently"]["cloudCover"].asFloat();
    milanSummary = jsonMilan["currently"]["summary"].asString();
    a = (milanSunset - milanSunrise)/12;
    cout<< milanSummary<<endl;
    cout<< a << endl;

    if (milanTime > milanSunrise && milanTime < milanSunset){
        milan = true;
    }else if (milanTime < milanSunrise || milanTime > milanSunset)
        milan = false;
// ************************************************************** COLOR BALANCE *******************************
    if (milanCloud < 0.5 && milanTime <= milanSunrise + a){
        r = 240;
        g = 183;
        b = 125;
//        color = ofColor (55, 127, 195);
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +a && milanTime <= milanSunrise + 2*a){
//        color = ofColor (122, 176, 227);
        r = 221;
        g = 214;
        b = 150;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +2*a && milanTime <= milanSunrise + 3*a){
//        color = ofColor (194, 221, 246);
        r = 205;
        g = 223;
        b = 183;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +3*a && milanTime <= milanSunrise + 4*a){
//        color = ofColor (223, 237, 251);
        r = 208;
        g = 227;
        b = 209;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +4*a && milanTime <= milanSunrise + 5*a){
//        color = ofColor (255, 255, 255);
        r = 234;
        g = 249;
        b = 239;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +5*a && milanTime <= milanSunrise + 7*a){
        //       NOON - 1PM WHITE
        r = 255;
        g = 255;
        b = 255;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +7*a && milanTime <= milanSunrise + 8*a){
        //        color = ofColor (255, 255, 255);
        r = 245;
        g = 244;
        b = 246;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +8*a && milanTime <= milanSunrise + 9*a){
        //        color = ofColor (255, 255, 255);
        r = 224;
        g = 222;
        b = 236;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +9*a && milanTime <= milanSunrise + 10*a){
        //        color = ofColor (255, 255, 255);
        r = 211;
        g = 193;
        b = 219;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +10*a && milanTime <= milanSunrise + 11*a){
        //        color = ofColor (255, 255, 255);
        r = 214;
        g = 167;
        b = 208;
    }else if (milanCloud < 0.5 && milanTime > milanSunrise +11*a && milanTime <= milanSunset){
        //        color = ofColor (255, 255, 255);
        r = 227;
        g = 143;
        b = 143;
// ****************************************** CLOUDY DAYS ************************************
    }else if (milanCloud >= 0.5 && milanTime <= milanSunrise + a){
        //        color = ofColor (255, 255, 255);
        r = 79;
        g = 148;
        b = 199;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +a && milanTime <= milanSunrise + 2*a){
        //        color = ofColor (122, 176, 227);
        r = 154;
        g = 224;
        b = 229;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +2*a && milanTime <= milanSunrise + 3*a){
        //        color = ofColor (122, 176, 227);
        r = 159;
        g = 213;
        b = 225;
    }
    else if (milanCloud >= 0.5 && milanTime > milanSunrise +3*a && milanTime <= milanSunrise + 4*a){
        //        color = ofColor (122, 176, 227);
        r = 183;
        g = 212;
        b = 221;
    }
    else if (milanCloud >= 0.5 && milanTime > milanSunrise +4*a && milanTime <= milanSunrise + 5*a){
        //        color = ofColor (122, 176, 227);
        r = 216;
        g = 232;
        b = 236;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +5*a && milanTime <= milanSunrise + 7*a){
        //        color = ofColor (122, 176, 227);
        r = 214;
        g = 238;
        b = 240;
        //  ################################## CLOUDY DAY COLOR SAME  ##################################
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +7*a && milanTime <= milanSunrise + 8*a){
        //        color = ofColor (122, 176, 227);
        r = 216;
        g = 232;
        b = 236;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +8*a && milanTime <= milanSunrise + 9*a){
        //        color = ofColor (122, 176, 227);
        r = 183;
        g = 212;
        b = 221;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +9*a && milanTime <= milanSunrise + 10*a){
        //        color = ofColor (122, 176, 227);
        r = 159;
        g = 213;
        b = 225;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +10*a && milanTime <= milanSunrise + 11*a){
        //        color = ofColor (122, 176, 227);
        r = 154;
        g = 224;
        b = 229;
    }else if (milanCloud >= 0.5 && milanTime > milanSunrise +11*a && milanTime <= milanSunset){
        //        color = ofColor (122, 176, 227);
        r = 79;
        g = 148;
        b = 199;
    }
    cout << r << endl;
    cout << g << endl;
    cout << b << endl;
}

void ofApp::setupArduino(const int & version){

    ofRemoveListener(ard.EInitialized, this,&ofApp::setupArduino);
    bSetupArduino = true;
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    ard.sendDigitalPinMode(6, ARD_PWM); // ard_output for turn on and off
    ard.sendDigitalPinMode(10, ARD_PWM);
    ard.sendDigitalPinMode(11, ARD_PWM);
//    ard.sendAnalogPinReporting(1, ARD_PWM);
//    ard.sendAnalogPinReporting(2, ARD_PWM);
//    ard.sendAnalogPinReporting(3, ARD_PWM);
 //   ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::updateArduino(){
    ard.update();
    if (bSetupArduino){
        ofSetColor (255,255,255);
        string msg;
    
       // cout << bSetupArduino << endl;

        if (milan == true){
            msg = "IT DAY";
            ofDrawBitmapString(msg, 200, 300);
            ard.sendPwm(11, r);
            ard.sendPwm(10, g);
            ard.sendPwm(6, b);
        }else if (milan == false)
//            ard.sendDigital(13,ARD_LOW);
            ard.sendPwm(11, 0);
            ard.sendPwm(10, 0);
            ard.sendPwm(6, 0);
            msg = "IT NIGHT";
            ofDrawBitmapString(msg, 200, 300);
    }

//    ard.sendPwm(11, 116);
//    ard.sendPwm(10, 184);
//    ard.sendPwm(6, 44);
    //gui.draw();
    
}
void ofApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor (255,255,255);
    if (!bSetupArduino){
        ofDrawBitmapString("Arduino is not ready", 200, 200);
    }else{
        ofDrawBitmapString("Arduino is connected", 200, 300);
    }
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
