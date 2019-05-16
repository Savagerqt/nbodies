//
//  init_bodies.hpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 31/10/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#ifndef initbodies_hpp
#define initbodies_hpp
#include "body.hpp"
#include <stdio.h>

double circlev(double rx, double ry) ;              //    Fonction auxiliaire
int sign(long double x) ;                           //    Renvoie le signe de x
Body* initGalaxy(int N) ;                           //    Initialise N corps dans une configuration galactique
Body* initU(int n, double scale) ;                  //    Initialise N corps répartis uniformément sur le cadran
Body* init2Galaxies(int N) ;



#endif /* init_bodies_hpp */
