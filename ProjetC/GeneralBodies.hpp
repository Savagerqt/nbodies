//
//  operation_bodies.hpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 01/11/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#ifndef GeneralBodies_hpp
#define GeneralBodies_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Body.hpp"

//
//    Ce fichier contient quelques fonctions utiles pour traiter
//    une liste de corps
//

//     Met à jour les corps 
void update(int n, Body* bodies,double dt) ;

//    Trace les corps sur le renderer
void plot(int n, Body* bodies, double scale, SDL_Renderer* renderer) ;

//    Affiche dans la console les n corps (pour debugger notamment)
void printBodies(int n, Body* bodies) ;

//    Remet à 0 les forces des corps de la liste
void resetForce(int n, Body* bodies) ; 

#endif /* operation_bodies_hpp */
