#include "ofApp.h"

int byteData;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    serial.setup("/dev/cu.usbmodem1411", 9600);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (serial.available() < 0) {
        msg = "Arduino Error";
    }
    else {
        //While statement looping through serial messages when serial is being provided.
        while (serial.available() > 0) {
            //byte data is being writen into byteData as int.
            byteData = serial.readByte();
            if(byteData<30&&byteData>0){
                data  = 30-byteData;
            }
            else if(byteData<256 && byteData >230){
                data = 286-byteData;
            }
            else data = 0;
            cout<<data<<endl;
            
            //byteData is converted into a string for drawing later.
//            msg = ofToString(byteData);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    if(byteData == 0){
    ofSetColor(0);
    }
    else{
    ofSetColor(byteData,byteData,0);
    }
    ofDrawSphere(ofGetWidth()/2, ofGetHeight()/2,5);
    
    
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
