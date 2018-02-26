//
//  init_bodies.cpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 31/10/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#include "InitBodies.hpp"
#include "Body.hpp"
#include <random>
#define Ms 1e30            // Masse solaire (On s'intéresse aux systèmes d'étoiles surtout :) )
#define PI 3.14159265358979323846
using namespace std ;


//===========================================================================
//                         Fonctions Auxiliaires
//===========================================================================


//    Fonctions auxiliaires pour calculer la vitesse du corps à la position rx,ry
//    pour un corps massif de poids 10^6*Ms
double circlev(double rx,double ry) {
    double r2=sqrt(rx*rx+ry*ry);
    double numerator=(6.67e-11)*1e6*Ms;
    return sqrt(numerator/r2);
}

int sign(long double x) {
    if (x>0) {
        return 1 ;
    }
    return -1 ;
}

//===========================================================================
//                          Initialisation Corps 
//===========================================================================


Body* initGalaxy(int N) {
    //    Initialise N corps dans une configuration galactique autour d'un corps central très massif
    //    Toutes les étoiles possèdent la même masse
    
    double radius = pow(10,17) ;                    // Rayon de la galaxie
    Body *bodies;
    srand((unsigned)time(0)) ;
    default_random_engine generator;
    normal_distribution<double> distribution(0,2.2);
    //    Initialisaion d'une liste de corps
    bodies = (Body*) malloc(N*sizeof(Body)) ;       // On alloue la place en mémoire
    for (int i = 0; i<N; i++) {
        
        //    On tire deux nombre générés par une gaussienne centrée sur 0 d'écart type 0.05
        //    En moyenne les étoiles se retrouvent à une distance de 0.7*radius du centre
        
        double number1 = distribution(generator) ;
        double number2 = distribution(generator) ;
        double px = radius*number1;
        double py = radius*number2;
        
        //    Calculs physiques
        
        double magv = circlev(px,py);
        double absangle = fabs(atan((py/px)));
        double thetav= PI/2-absangle;
        double vx   = -1*sign(py)*cos(thetav)*magv;
        double vy   = sign(px)*sin(thetav)*magv;
        
        
        //    On choisit une masse aléatoirement aussi comprise en 10^20 et 10*Ms environ
        //    On colorie ensuite les corps selon leur masse, avec un gradient rouge
        //    Plus les planètes sont massives, plus elles seront rouge vif
        
        float r2 = rand()%1000 ;
        double mass = (r2/1000)*Ms*10+1e20;
        int g = (int) floor(mass*254/(Ms*10+1e20));
        int b = (int) floor(mass*254/(Ms*10+1e20));
        int r = 255;
        bodies[i]   = Body(mass, px, py, vx, vy, r, g, b);
    }
    return bodies;
}




Body* initU(int n,double scale) {
    Body* bodies ;
    bodies = (Body*) malloc(n*sizeof(Body)) ;
    int row = floor(pow(n,0.5)) ;
    for (int k = 0; k<row; k++) {
        for (int l=0; l<row; l++) {
            *(bodies + l + row*k + 1 ) = Body(Ms,
                            -scale + k * (2*scale/row),
                            -scale + l * (2*scale/row),
                            0,
                            0,
                            255,255,255) ;
        }
    }
    return bodies ;
}




































