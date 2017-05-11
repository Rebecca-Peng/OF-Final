//
//  ParticleSystem.cpp
//  FinalParticle
//
//  Created by pfy on 5/9/17.
//
//

#include "ParticleSystem.hpp"

Particle::Particle(){

    radius = 5.0;
    friction = 0.08;
    mass = 1.0;
    position.set(ofGetWidth()/2.0,ofGetHeight()/2.0,-100);
    velocity.set(0,0,0);
    acceleration.set(0,0,0);
    minx = 0;
    miny = 0;
    minz = -ofGetHeight();
    maxx = ofGetWidth();
    maxy = ofGetHeight();
    maxz = ofGetHeight();

}

void Particle::update(){

    acceleration -= velocity * friction;
    velocity += acceleration;
    position += velocity;
    acceleration.set(0,0,0);
    
}

void Particle::draw(){
    ofNoFill();
    ofDrawSphere(position.x, position.y, position.z,radius);
}

void Particle::addForce(ofVec3f force){
    acceleration += force/mass;
}

void Particle::addForce(float forceX,float froceY,float forceZ){
    acceleration += ofVec3f(forceX,froceY,forceZ)/mass;
}

void Particle::bounceOffWalls(){
    if(position.x > maxx){
        position.x = maxx;
        velocity.x *= -1;
    }
    if(position.x < minx){
        position.x = minx;
        velocity.x *= -1;
    }
    if(position.y > maxy){
        position.y = maxy;
        velocity.y *= -1;
    }
    if(position.y < miny){
        position.y = miny;
        velocity.y *= -1;
    }
    if(position.z > maxz){
        position.z = maxz;
        velocity.z *= -1;
    }
    if (position.z < minz){
        position.z = minz;
        velocity.z *= -1;
    }
}

void Particle::throughOffWalls(){
    if(position.x <minx){
        position.x = maxx;
    }
    if (position.y < miny) {
        position.y = maxy;
    }
    if (position.z < minz) {
        position.z = maxz;
    }
    if (position.x > maxx) {
        position.x = minx;
    }
    if (position.y > maxy) {
        position.y = miny;
    }
    if (position.z > maxz) {
        position.z = minz;
    }
}

void Particle::restToRandomPos(){
    float minx = 0;
    float miny = 0;
    float minz = -depth;
    float maxx = ofGetWidth();
    float maxy = ofGetHeight();
    float maxz = depth;
    if(position.x < minx || position.y<miny || position.z < minz || position.x > maxx || position.y > maxy || position.z > maxz){
        position.set(ofRandom(minx,maxx), ofRandom(miny, maxy), ofRandom(minz, maxz));
    }
}

void Particle::addRepulsionForce(float x, float y, float z, float radius, float scale){
    ofVec3f posOfForce;
    posOfForce.set(x,y,z);
    ofVec3f diff = position - posOfForce;
    float length = diff.length();
    bool bAmCloseEnough = true;
    if(radius > 0){
        if(length > radius){
            bAmCloseEnough = false;
        }
    }
    if(bAmCloseEnough == true){
        float pct = 1 - (length/radius);
        diff.normalize();
        acceleration = acceleration + diff * scale * pct;
    }
}

void Particle::addRepulsionForce(Particle &p, float raduis, float scale){
    ofVec3f posOfForce;
    posOfForce.set(p.position.x, p.position.y,p.position.z);
    ofVec3f diff = position - posOfForce;
    float length = diff.length();
    bool bAmCloseEnough = true;
    if(radius > 0){
        if(length > radius){
            bAmCloseEnough = false;
        }
    }
    if(bAmCloseEnough == true){
        float pct = 1 -(length/radius);
        diff.normalize();
        acceleration = acceleration + diff * scale * pct;
    }
}

void Particle::addAtrractionForce(float x, float y, float z, float radius, float scale){
    ofVec3f posOfForce;
    posOfForce.set(x, y, z);
    ofVec3f diff = position - posOfForce;
    float length = diff.length();
    bool bAmCloseEnough = true;
    if(radius > 0){
        if(length > radius){
            bAmCloseEnough = false;
        }
    }
    if(bAmCloseEnough == true){
        float pct = 1- (length/radius);
        diff.normalize();
        acceleration = acceleration-diff * scale * pct;
    }
}

void Particle::addAtrractionForce(Particle &p, float radius, float scale){
    ofVec3f posOfForce;
    posOfForce.set(p.position.x, p.position.y, p.position.z);
    ofVec3f diff = position - posOfForce;
    float length = diff.length();
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);
        diff.normalize();
        acceleration = acceleration - diff * scale * pct;
    }
}
































