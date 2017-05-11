#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //song
    song.load("Doom-DaDa.mp3");
    while(!song.isLoaded());
    song.play();
    nBandsToGet = 540;
    
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    
    //particle 01
    ofSetFrameRate(60);
    ofBackground(0);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    pressed = true;
    for(int i = 0; i < num; i++){
        particles[i].position = ofVec3f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), ofRandom(-ofGetWidth(), ofGetWidth()));
        particles[i].depth = ofGetWidth();
    }
    
    //particle 02
    int num = 25000;
    p.assign(num, demoParticle());
    currentMode = PARTICLE_MODE_NEAREST_POINTS;
    resetParticles();

    //particle heart
    int num2 = 540;
    p2.assign(num2, demoParticle());
    resetParticlesHeart();
    
    //arduino
    serial.setup("/dev/cu.usbmodem1411", 9600);

}


//--------------------------------------------------------------
void ofApp::resetParticles(){
    
    //these are the attraction points used in the forth demo
    attractPoints.clear();
//    for(int i = 0; i < 3; i++){
//        attractPoints.push_back( ofPoint((ofGetWidth()/3 + i * 80),ofGetHeight()/4) );
////        attractPoints.push_back(ofPoint(ofGetWidth()/2,ofGetHeight()/6));
//        }
    for(int i = 0; i < 29; i++){
        //head
        if(i == 0) attractPoints.push_back(ofPoint(ofGetWidth()/2,ofGetHeight()/9));
        //        else if(i == 21) attractPoints.push_back(ofPoint(ofGetWidth()/2,ofGetHeight()/9-50));
        else if(i == 21) attractPoints.push_back(ofPoint(ofGetWidth()/2-25,ofGetHeight()/9-50));
        else if(i == 22) attractPoints.push_back(ofPoint(ofGetWidth()/2+25,ofGetHeight()/9-50));
        //body
        else if(i >=1 && i <=5)attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-1) * 80),ofGetHeight()/4-50) );
        else if(i >=6 && i <=8) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-5) * 80),ofGetHeight()/4 + 50) );
        else if(i >=26 && i <=28) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-25) * 80),ofGetHeight()/4) );
        else if(i >=23 && i <=25) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-22) * 80),ofGetHeight()/4 + 100) );
        else if(i >=9 && i <=10) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-8) * 100),ofGetHeight()/4 + 150) );
        //feet
        else if(i ==11) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-10) * 100),ofGetHeight()/4 + 250) );
        else if(i ==12) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-11) * 220),ofGetHeight()/4 + 250) );
        else if(i ==13) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-12) * 100),ofGetHeight()/4 + 350) );
        else if(i ==14) attractPoints.push_back( ofPoint((ofGetWidth()/3 + (i-13) * 220),ofGetHeight()/4 + 350) );
        else if(i ==15) attractPoints.push_back( ofPoint((ofGetWidth()/3 + 100),ofGetHeight()/4 + 450) );
        else if(i ==16) attractPoints.push_back( ofPoint((ofGetWidth()/3 + 220),ofGetHeight()/4 + 450) );
        //limb
        else if(i ==17) attractPoints.push_back( ofPoint((ofGetWidth()/3 + 30),ofGetHeight()/4 + 170) );
        else if(i ==18) attractPoints.push_back( ofPoint((ofGetWidth()/3 + 310),ofGetHeight()/4 + 170) );
        else if(i ==19) attractPoints.push_back( ofPoint((ofGetWidth()/3),ofGetHeight()/4 + 70) );
        else if(i ==20) attractPoints.push_back( ofPoint((ofGetWidth()/3+ 320),ofGetHeight()/4 + 70) );
        //        attractPoints.push_back(ofPoint(ofGetWidth()/2,ofGetHeight()/6));
    }
    
    attractPointsWithMovement = attractPoints;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMode(currentMode);
        p[i].setAttractPoints(&attractPointsWithMovement);;
        p[i].reset();
    }
    
}

void ofApp::resetParticlesHeart(){
    attractPoints2.clear();
    attractPoints2.push_back(ofPoint(ofGetWidth()/2+50,ofGetHeight()/5+30));

    attractPointsWithMovement2 = attractPoints2;
    
    for(unsigned int i = 0; i < p2.size(); i++){
        p2[i].setMode(currentMode);
        p2[i].setAttractPoints(&attractPointsWithMovement2);;
        p2[i].reset();
    }
}

float *val;
int byteData;
bool wavedata;

//--------------------------------------------------------------
void ofApp::update(){
    //arduino
    if (serial.available() < 0) {
        msg = "Arduino Error";
    }
    else {
        //While statement looping through serial messages when serial is being provided.
        while (serial.available() > 0) {
            //byte data is being writen into byteData as int.
            byteData = serial.readByte();
            if(byteData<30&&byteData>=0){
                data  = 30-byteData;
            }
            else if(byteData<256 && byteData >230){
                data = 286-byteData;
            }
            else data = 0;
            cout<<data<<endl;
            if(data > 0) wavedata = false;
            else wavedata = true;
            
            //byteData is converted into a string for drawing later.
            //            msg = ofToString(byteData);
        }
    }

    
        //sound
    ofSoundUpdate();
    
    val = ofSoundGetSpectrum(nBandsToGet);
    
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
    
    //particle 01
    mesh.clear();
    float time = ofGetElapsedTimef();
    
    for(int i = 0; i< num; i++){
        if(pressed){
            particles[i].addAtrractionForce(ofGetWidth()/2 + 20,ofGetHeight()/2-70,ofRandom(ofGetHeight()),ofGetHeight()*1.5,fallWiggle);
            particles[i].addRepulsionForce(ofGetWidth()/2 + 20,ofGetHeight()/2-70, ofRandom(ofGetHeight()), ofGetHeight() * 0.8, fallWiggle);
            particles[i].restToRandomPos();
   
            fallWiggle = val[i]*10;
//            cout<<fallWiggle<<endl;
        }
        particles[i].update();
        particles[i].bounceOffWalls();
        mesh.addVertex(ofVec3f(particles[i].position.x,particles[i].position.y,particles[i].position.z));
    }
    
    //particle 02
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].setMode(currentMode);
        p[i].update(1,wavedata);
    }
    for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
        attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0+data * 0.5;
        attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }
    
    //particle heart
    for(unsigned int i = 0; i < p2.size(); i++){
        p2[i].setMode(currentMode);
        p2[i].update((fftSmoothed[i]*80000),wavedata);
    }
    for(unsigned int i = 0; i < attractPointsWithMovement2.size(); i++){
        attractPointsWithMovement2[i].x = attractPoints2[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0 * fftSmoothed[i]*8;
//        attractPointsWithMovement2[i].x = attractPoints2[i].x + fftSmoothed[i]*80;
//        attractPointsWithMovement2[i].y = attractPoints2[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0 * fftSmoothed[i]*2 ;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0,0);
//    //particle 01
//    ofSetColor(170);
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
//    static GLfloat distance[] = { 0.0, 0.0, 5.0 };
//    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
//    glPointSize(3000);
//    mesh.draw();
//    ofDisableBlendMode();
    
    //particle 02
    for(unsigned int i = 0; i < p.size()-1; i++){
        p[i].draw(data * 3,data * 4,data * 6,5);
    }
    
    ofSetColor(data * 5);
    if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
        for(unsigned int i = 0; i < attractPoints.size(); i++){
            
            ofNoFill();
            ofDrawCircle(attractPointsWithMovement[i], 10);
            ofFill();
            ofDrawCircle(attractPointsWithMovement[i], 4);
        }
    }
    
    //particle 02
    
    for(unsigned int i = 0; i < p2.size(); i++){
//        p2[i].draw(241,190,30,7);
    }
    
    if(byteData == 0){
        ofSetColor(0);
    }
    else{
        ofSetColor(byteData,byteData,0);
    }
    if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
        for(unsigned int i = 0; i < attractPoints2.size(); i++){
            ofNoFill();
            ofDrawCircle(attractPointsWithMovement2[i], fftSmoothed[i]*8);
            ofFill();
            ofDrawCircle(attractPointsWithMovement2[i], fftSmoothed[i]*8);
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    pressed = true;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     pressed = false;
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
