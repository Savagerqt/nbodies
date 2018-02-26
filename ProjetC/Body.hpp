//
//  class_body.hpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 29/10/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#ifndef Body_hpp
#define Body_hpp

#include <stdio.h>

#include <SDL2/SDL.h>

class Quad ; 

class Body{
    
    //                                      Description :
    //
    //    La classe Body est une classe contenant toutes les informations sur un corps, elle contient les informations
    //    sur sa masse, sa position, sa vitesse et la force auquelle elle est soumise.

    
    private :
    
    double _x ;                 //    Coordonnée en x
    double _y ;                 //    Coordonnée en y
    double _vx ;                //    Vitesse selon x
    double _vy ;                //    Vitesse selon y
    double _mass ;              //    Masse du corps
    double _fx ;                //    Force subie selon x
    double _fy ;                //    Force subie selon y
    int _r ;                    //    RED       |
    int _g ;                    //    GREEN     |- Ces variables servent pour définir la couleur de traçage du corps
    int _b ;                    //    BLUE      |
    
    
    public :
    
    Body(double mass,double x,double y,double vx,double vy,int r, int g, int b) ;
    Body() ; 
    
    void printBody() ;                          //    Affiche la masse et la coordonnée du corps
    
    
    // Fonction pour retourner un attribut du corps
    
    //    La position en X
    double getx() {
        return _x ;
    }
    
    //    La position en Y
    double gety() {
        return _y ;
    }
    
    //    La vitesse en X
    double getvx() {
        return _vx ;
    }
    
    //    La vitesse en Y
    double getvy() {
        return _vy ;
    }
    
    //    La masse du corps
    double getMass() {
        return _mass ; 
    }
    
    double distance2(Body* body) ;
    double distance2(double x, double y) ; 
    

    
    //----------------------------------------------------------------------------------------------------------------------------------
    //    Fonction pour calculer la force subie par un corps
    
    void addForce(Body* body) ;                         //    Ajoute la force créée par le corps body
    void addForce(double mass, double x, double y) ;    //    idem que la fonction ci-dessus, mais avec les paramètres directs
    void force(int n, Body* bodies) ;                   //    Update la force créée par le système sur le corps
    void resetForce() ;                                 //    Met à zéro la force du corps
    
    //----------------------------------------------------------------------------------------------------------------------------------
    void updateEuler(double dt) ;                             // Update la position du corps pour une itération de pas dt
    
    // Fonction de traçage d'un corps sur le renderer
    void plot(SDL_Renderer *renderer,double scale) ;          //    Trace le corps sur le renderer
        
};

#endif /* class_body_hpp */
