#pragma once

#include "ofMain.h"
#include "ParticleSystem.hpp"
#include "demoParticle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void resetParticles();
        void resetParticlesHeart();

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
    
        //particle 01
        static const int num = 100;
        Particle particles[num];
        ofVboMesh mesh;
        bool pressed;
    
        //sound
        ofSoundPlayer  song;
        int nBandsToGet;
        float rX;
        ofPoint loc;
    
        float 	* fftSmoothed;
        int hue;
    
        float fallWiggle;
    
        //particle 02
        particleMode currentMode;
        vector <demoParticle> p;
        vector <ofPoint> attractPoints;
        vector <ofPoint> attractPointsWithMovement;
    
        //particle heart
        vector <demoParticle> p2;
        vector <ofPoint> attractPoints2;
        vector <ofPoint> attractPointsWithMovement2;
    
        //arduino
        float data;
        ofSerial serial;
        string msg;
    
    

};
