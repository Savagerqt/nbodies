//
//  operation_bodies.cpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 01/11/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#include "GeneralBodies.hpp"
#include "Body.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

void update(int n, Body* bodies,double dt) {
    for (int i = 0; i<n ; i++) {
        (bodies+i)->updateEuler(dt) ;
    }
}

void plot(int n, Body* bodies,double scale, SDL_Renderer* renderer) {
    for (int i = 0; i<n ; i++) {
        (bodies+i)->plot(renderer,scale) ;
    }
}

void printBodies(int n, Body* bodies) {
    for (int i = 0; i<n ; i++) {
        cout << i <<" : " ;
        (bodies+i)->printBody() ;
    }
}

void resetForce(int n, Body* bodies) {
    for (int i = 0; i<n ; i++) {
        (bodies+i)->resetForce() ;
    }
}

