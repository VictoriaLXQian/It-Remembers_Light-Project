#include "ofApp.h"
#include "ofSerial.h"
#include "ofArduino.h"

//#define PIN_RED 3
//#define PIN_GREEN 5
//#define PIN_BLUE 6

int milanTime, milanSunrise, milanSunset;
int hongkongTime, hongkongSunrise, hongkongSunset;
int hongkongUV, milanUV, americaUV;
int hkStart, hkEnd;
int americaTime, americaSunrise, americaSunset;
int r, g, b;
bool hongkong;
bool milan;
bool usa;

//--------------------------------------------------------------

void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    std::string urlMilan = "https://api.darksky.net/forecast/your API/45.4642,9.1900";
    std::string urlHkg = "https://api.darksky.net/forecast/your API/22.3193,114.1694";
    std::string urlNc = "https://api.darksky.net/forecast/your API/44.9778,-93.2650";
    bool nc = jsonNc.open(urlNc);
//    bool milan = jsonMilan.open(urlMilan);
//    bool hkg = jsonHkg.open(urlHkg);
//    hongkongTime = jsonHkg["currently"]["time"].asInt();
//    hongkongSunrise = jsonHkg["daily"]["data"][0]["sunriseTime"].asInt();
//    hongkongSunset = jsonHkg["daily"]["data"][0]["sunsetTime"].asInt();
//    hongkongUV = jsonHkg["currently"]["uvIndex"].asInt();
    // USE UV INDEX TO CHANGE THE COLOR
//    hkStart =jsonHkg["daily"]["data"][0]["time"].asFloat();
//    hkEnd =jsonHkg["daily"]["data"][1]["time"].asFloat();
//    gui.setup();
//    gui.add(time.setup("timeTest",hongkongTime,hkStart,hkEnd));
//
    int baud = 57600;
    ard.connect("/dev/cu.usbmodem14601",baud);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    updateArduino();
//    milanTime = jsonMilan["currently"]["time"].asInt();
//    milanSunrise = jsonMilan["daily"]["data"][0]["sunriseTime"].asInt();
//    milanSunset = jsonMilan["daily"]["data"][0]["sunsetTime"].asInt();
//    milanUV = jsonMilan["currently"]["uvIndex"].asInt();
    americaTime = jsonNc["currently"]["time"].asInt();
    americaSunrise = jsonNc["daily"]["data"][0]["sunriseTime"].asInt();
    americaSunset = jsonNc["daily"]["data"][0]["sunsetTime"].asInt();
    americaUV = jsonNc["currently"]["uvIndex"].asInt();
    
    if (americaTime > americaSunrise && americaTime < americaSunset) {
        usa = true;
    }else if (americaTime < americaSunrise || americaTime > americaSunset)
        usa = false;
//    if (milanTime > milanSunrise && milanTime < milanSunset){
//        milan = true;
//    }else if (milanTime < milanSunrise || milanTime > milanSunset)
//        milan = false;
//    if (time > hongkongSunrise && time < hongkongSunset) {
//        hongkong = true;
//    }else if (time < hongkongSunrise||time > hongkongSunset)
//        hongkong = false;
//    if (hongkongUV == 4 || milanUV == 4 || americaUV == 4){
//        r = 55;
//        g = 127;
//        b = 195;
//        //        color = ofColor (55, 127, 195);
//    }else if (hongkongUV == 3 || milanUV == 3 || americaUV == 3){
//        //        color = ofColor (122, 176, 227);
//        r = 122;
//        g = 176;
//        b = 227;
//    }else if (hongkongUV == 2 || milanUV == 2 || americaUV == 2){
//        //        color = ofColor (194, 221, 246);
//        r = 194;
//        g = 221;
//        b = 246;
//    }else if (hongkongUV == 1 || milanUV == 1 || americaUV == 1){
//        //        color = ofColor (223, 237, 251);
//        r = 223;
//        g = 237;
//        b = 251;
//    }else if (hongkongUV == 0 || milanUV == 0 || americaUV == 0){
//        //        color = ofColor (255, 255, 255);
//        r = 255;
//        g = 255;
//        b = 255;
//    }
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
        
        //        if (hongkong==true){
        //            ard.sendDigitalPinMode(11, ARD_HIGH);
        //            msg = "HK DAY";
        //            ofDrawBitmapString(msg, 200, 200);
        //        }else
        //            ard.sendDigitalPinMode(11, ARD_LOW);
        //            msg = "HK NIGHT";
        //            ofDrawBitmapString(msg, 200, 200);
        //        if (milan == true){
        //            msg = "IT DAY";
        //            ofDrawBitmapString(msg, 200, 300);
        //            ard.sendDigital(13, ARD_HIGH);
        //        }else
        //            ard.sendDigital(13,ARD_LOW);
        //            msg = "IT NIGHT";
        //            ofDrawBitmapString(msg, 200, 300);
        //    }
        //        if (usa == true){
        //            ard.sendDigital(8, ARD_HIGH);
        //            msg = "USA DAY";
        //            ofDrawBitmapString(msg, 200, 400);
        //        }else
        //            ard.sendDigital(8, ARD_LOW);
        //            msg = "USA NIGHT";
        //            ofDrawBitmapString(msg, 200, 400);
                if (usa == true) {
                    ard.sendPwm(11, 139); //R
                    ard.sendPwm(10, 195); //G
                    ard.sendPwm(6, 151); //B
                    msg = "USA Day";
                    ofDrawBitmapString(msg, 200, 400);
                }else if (usa == false) {
                    ard.sendPwm(11, 0);
                    ard.sendPwm(10, 0);
                    ard.sendPwm(6, 0);
                };
        //   ard.sendDigital(9, 120);
        //   ard.sendDigital(10, 100);
        //   ard.sendDigital(11, 50);
        //    ard.sendAnalogPinReporting(1, 120);
        //    ard.sendAnalogPinReporting(2, 200);
        //    ard.sendAnalogPinReporting(3, 50);
    }
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
    //    if (hongkong == true)
    //        ofDrawBitmapString("HK DAY", 200, 200);
    //    if (milan == true)
    //        ofDrawBitmapString("IT DAY", 200, 300);
    //    if (usa == true)
    //        ofDrawBitmapString("USA DAY", 200, 400);
    //    if (bSetupArduino){
    //        cout << bSetupArduino << endl;
    //        string msg;
    //        if (hongkong==true){
    //            ard.sendDigitalPinMode(13, ARD_HIGH);
    //            msg = "HK DAY";
    //            ofDrawBitmapString(msg, 200, 200);
    //        }else
    //            ard.sendDigitalPinMode(13, ARD_LOW);
    //            msg = "HK NIGHT";
    //            ofDrawBitmapString(msg, 200, 200);
    //        if (milan == true){
    //            msg = "IT DAY";
    //            ofDrawBitmapString(msg, 200, 300);
    //            ard.sendDigital(12, ARD_HIGH);
    //        }else
    //            ard.sendDigital(12,ARD_LOW);
    //            msg = "IT NIGHT";
    //            ofDrawBitmapString(msg, 200, 300);
    //        if (usa == true){
    //            ard.sendDigital(8, ARD_HIGH);
    //            msg = "USA DAY";
    //            ofDrawBitmapString(msg, 200, 400);
    //        }else
    //            ard.sendDigital(8, ARD_LOW);
    //            msg = "USA NIGHT";
    //            ofDrawBitmapString(msg, 200, 400);
    //    }
    if (!bSetupArduino){
        ofDrawBitmapString("Arduino is not ready", 200, 200);
    }else{
        ofDrawBitmapString("Arduino is connected", 200, 300);
    }
//    gui.draw();
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
