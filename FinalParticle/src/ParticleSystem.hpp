//
//  ParticleSystem.hpp
//  FinalParticle
//
//  Created by pfy on 5/9/17.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp
#pragma once
#include "ofMain.h"
#include <stdio.h>


class Particle{

public:
    Particle();
    void addForce(ofVec3f force);
    void addForce(float forceX,float froceY,float forceZ);
    void update();
    void draw();
    
    void bounceOffWalls();
    void throughOffWalls();
    void restToRandomPos();
    
    void addRepulsionForce(float x, float y,float z,float radius, float scale);
    void addRepulsionForce(Particle &p, float raduis, float scale);
    
    void addAtrractionForce(float x,float y,float z,float radius, float scale);
    void addAtrractionForce(Particle &p, float radius, float scale);
    
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float friction;
    float radius;
    bool bFixed;
    float mass;
    float depth;
    float minx, miny, minz;
    float maxx, maxy,maxz;
    

};

#endif /* ParticleSystem_hpp */
