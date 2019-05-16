//
//  class_body.cpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 29/10/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#include "body.hpp"
#include <math.h> // pow
#include <iostream>
#include <SDL2/SDL.h>

#define SIZE 400     // Taille de l'écran

using namespace std ;


Body::Body(double mass,double x,double y,double vx ,double vy, int r, int g, int b) {
    // Initialisation du corps
    _mass = mass ;
    _x = x ;
    _y = y ;
    _vx = vx ;
    _vy = vy ;
    _r = r ;
    _g = g ;
    _b = b ;
    _fx = 0 ;
    _fy = 0 ;

}

Body::Body() {
    _mass = 0 ;
    _x = 0 ;
    _y = 0 ;
    _vx = 0 ;
    _vy = 0 ;
    _fx=0 ;
    _fy = 0 ;
    _r = 0 ;
    _g = 0 ;
    _b = 0 ;
}

//------------------------------------------------------------------------------
//    Affiche le corps dans la console sous la forme :
//
//    Position : (1e17,-1e17) | Vitesse (2e4,3e4) | Masse : 3e30 | Force : (3e15,1.2e15)

void Body::printBody() {
    cout << "Position : (" << _x << ","<< _y <<")" << " | Vitesse : ("<< _vx << "," << _vy << ")"<<" | Masse : "<< _mass << " | Force : (" << _fx << ","<< _fy <<")"<< endl;
}


//===========================================================================
//                     Fonction de retour d'attributs
//===========================================================================

//------------------------------------------------------------------------------
//    Retourne la distance au carré entre deux corps

double Body::distance2(Body* body) {
    // Retourne la distance au carré entre deux corps
    return ((_x - body->getx()) * (_x - body->getx()) + (_y - body->gety()) * (_y - body->gety())) ;
}

double Body::distance2(double x, double y) {
    return ((_x - x) * (_x - x) + (_y - y) * (_y - y)) ;
}


//===========================================================================
//                            Calcul des forces
//===========================================================================

//------------------------------------------------------------------------------
//    Renvoie la force exercée par le corps body sur le corps self

void Body::addForce(Body* body) {
    double EPS = 3 * pow(10, 4) ;              // Paramètre pour adoucir la force lorsque la distance tend vers 0
    double dx = body->getx() - _x ;
    double dy = body->gety() - _y ;
    double F = 6.67 * 1e-11 * _mass * body->getMass() / (distance2(body) + EPS ) ;
    _fx += F*dx / pow(distance2(body), 0.5) ;
    _fy += F*dy / pow(distance2(body), 0.5) ;
}


//------------------------------------------------------------------------------
//    On ajoute la force exercée par la masse mass au point (x,y)
//    Cette fonction est utilisée pour calculer la force exercée par le barycentre
//    d'un cadran

void Body::addForce(double mass, double x, double y) {
    double EPS = 3 * pow(10, 4) ;              // Paramètre pour adoucir la force lorsque la distance tend vers 0
    double dx = x - _x ;
    double dy = y - _y ;
    double d2 = (dx * dx + dy * dy) ;
    double F = 6.67 * pow(10, -11) * _mass * mass / (d2 + EPS ) ;
    _fx += F * dx / pow(d2, 0.5) ;
    _fy += F * dy / pow(d2, 0.5) ;
}


//------------------------------------------------------------------------------
//    On calcule la force exercée par la liste de corps bodies
//    Cette fonction n'est utile que pour la méthode d'Euler classique
//    Avec la méthode de Barnes-Hut, on utilise plutôt un arbre

void Body::force(int n, Body* bodies) {
    _fx = 0 ;
    _fy = 0 ;
    for (int i =0 ; i < n ; i++ ) {
        if (distance2((bodies + i)) != 0 ) {
            addForce((bodies + i)) ;
        }
    }
}

//------------------------------------------------------------------------------
//    On remet à 0 la force du corps
void Body::resetForce() {
    _fx = 0 ;
    _fy = 0 ;
}



//===========================================================================
//                            Fonction de calcul
//===========================================================================

//    Fonction qui sert à actualiser les vitesses et les positions
//    en fonction du paramètre dt, le pas de temps

void Body::updateEuler(double dt) {
    if (_mass == 0) {
        _vx = 0 ;
        _vy = 0 ;
    }
    else {
        _vx += (dt * _fx) / _mass ;
        _vy += (dt * _fy) / _mass ;
        _x += dt * _vx ;
        _y += dt * _vy ;
    }
}


//===========================================================================
//                       Tracé des corps sur le canvas
//===========================================================================
//
//    On trace le corps sur le canvas

void Body::plot(SDL_Renderer *renderer, double scale) {
    SDL_SetRenderDrawColor(renderer, _r, _g, _b, 255) ;
    // Echelle de la fenêtre

    int plotx = floor(SIZE + SIZE * _x / scale) ;
    int ploty = floor(SIZE + SIZE * _y / scale) ;

    SDL_RenderDrawPoint(renderer, plotx, ploty);
}
