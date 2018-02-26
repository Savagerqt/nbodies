//
//  class_quad.cpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 31/10/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#include "Quad.hpp"
#include "Body.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream> 
using namespace std;


//===========================================================================
//                              Constructeur
//===========================================================================

//    Constructeur de la classe cadran, qui permet d'initialiser
//    un cadran de longueur length et de centre de coordonnées (x,y)

Quad::Quad(double x, double y, double length) {
    _xmid = x ;
    _ymid = y ;
    _length = length ;
    _external = 1 ;
    _daughters = NULL ;
    _body = new Body;
    *_body = Body(0, 0, 0, 0, 0, 0, 0, 0) ;
    _totalMass = 0 ;
    _xbar = 0 ;
    _ybar = 0 ;
    _nbNodes = 0 ;
}

//===========================================================================
//                      Générateur de sous cadran
//===========================================================================

//    Les méthodes suivantes initialisent des sous-cadrans en
//    fonction du cadran auquel on applique la méthode ci-dessous.
//    Les 4 sous-cadrans correspondant à la division en 4 du cadran
//    initial.
//
//     Sous-cadran Nord-Est

Quad Quad::NE() {
    return Quad(_xmid + _length/4, _ymid + _length/4, _length/2) ;
}

//    Sous-cadran Nord-Ouest

Quad Quad::NW() {
    return Quad(_xmid - _length/4, _ymid + _length/4, _length/2) ;
}

//    Sous-cadran Sud-Est

Quad Quad::SE() {
    return Quad(_xmid + _length/4, _ymid - _length/4, _length/2) ;
}

//    Sous-cadran Sud-Ouest

Quad Quad::SW() {
    return Quad(_xmid - _length/4, _ymid - _length/4, _length/2) ;
}

void Quad::createDaughters() {
    // Quand on crée les fils d'un noeud, on crée 4 nouveaux noeuds à l'arbre
    _nbNodes += 4 ;
    _daughters = (Quad*) malloc( 4 * sizeof(Quad));
    *_daughters = NE() ;
    *(_daughters + 1) = NW() ;
    *(_daughters + 2) = SE() ;
    *(_daughters + 3) = SW() ;
    // ON update la variable qui renseigne si le noeud est exterieur
    // 0 s'il est interieur, 1 s'il est exterieur
    _external = 0 ;

}

//===========================================================================
//                           Fonctions de test
//===========================================================================

//------------------------------------------------------------------------------
//    Retourne si (x,y) est dans le cadran

bool Quad::in(double x, double y) {
    return ((x < _xmid + _length/2) && (x > _xmid - _length/2)
            &&
            (y < _ymid + _length/2) && (y > _ymid - _length/2)) ;
}

//------------------------------------------------------------------------------
//    Retourne si le corps se trouve dans le cadran

bool Quad::in(Body* body) {
    return in(body->getx(), body->gety()) ;
}

//------------------------------------------------------------------------------
//    Affiche le cadran dans la console sous la forme
//
//    S'il y a un corps :
//    CORPS (Position : (1e17,-1e17) | Vitesse (2e4,3e4) | Masse : 3e30 | Force : (3e15,1.2e15))
//    CADRAN (Longueur  1.5e17 | Milieu (1.5e17,-1.5e17) | External : 1)
//
//    Sinon :
//    Pas de corps contenur
//    Longueur : 1.5e17 | Milieu (1.5e17,-1.5e17) | External : 1

void Quad::printQuad() {
    if ((*_body).getMass() == 0 ) {
        cout << "CORPS (" ;
        (*_body).printBody() ;
        cout << ")" ;
    }
    cout << endl <<"CADRAN (Longueur : " <<_length << " | Milieu : (  " << _xmid << " , " << _ymid << " )" ;
    cout << " | External : " << _external << ")"<< endl ;
}

//------------------------------------------------------------------------------
//    Renvoie le sous-cadran correspondant
//          ____________________
//          |         |         |
//          |    0    |    1    |
//          |_________|_________|
//          |         |         |
//          |     2   |    3    |
//          |_________|_________|
//
//
//    Argument : 0->NE cadran Nord-Est, 1->NW cadran Nord-Ouest
//    2->SE cadran Sud-Est, 3->SW cadran Sud-Ouest

Quad Quad::getSub(int i) {
    if (_daughters == NULL ) {
        cout << "NOT CREATED" << endl ;
    }
    return *(_daughters+i) ;
}

//===========================================================================
//                          Ajouter un corps
//===========================================================================
//
//    La fonction suivante permet de construire l'arbre en
//    insérant les corps dans l'abre initialisé.
//
//    Le principe de construction de cet arbre est assez simple :
//
//        - Si le corps est inséré dans un cadran sans corps, on
//          l'insère dans celui-ci, puis si le cadran est extérieur
//          (est une feuille ou ne contient qu'un seul et unique corps),
//          on rajoute le poids du corps dans le barycentre du cadran,
//          puis on l'insère dans le sous-cadran correspondant.
//
//        - Si le corps possède déjà un corps, on ajoute le corps
//          sur le barycentre du cadran, puis on insère le corps déjà
//          contenu ainsi que le nouveau corps dans les sous-cadrans
//          correspondants
//
//    Pour construire l'arbre entièrement, on applique la fonction add
//    à tous les corps du système étudié

void Quad::add(Body* body) {
    
    //    Si le corps n'est pas dans le cadran, on ne fait rien
    if (in(body) == false) {
        return ;
    }
    //    S'il n'y a pas de corps, on rajoute le corps sur le noeud
    if ((*_body).getMass() == 0 ) {
        
        *_body = *body ;
        // On actualise la valeur du centre de masse
        _totalMass += body->getMass() ;
        _xbar = (body->getx() * body->getMass() + _xbar * _totalMass)/(_totalMass + body->getMass()) ;
        _ybar = (body->gety() * body->getMass() + _ybar * _totalMass)/(_totalMass + body->getMass()) ;
        //   Si le noeud est interieur
        if (_external == 0 ) {
            //    On ajoute ensuite le corps dans un sous cadran
            for (int i = 0; i < 4; i++) {
                (_daughters + i)->add(body);
            }
            //    On oublie pas d'enlever le corps du noeud
            *_body = Body(0, 0, 0, 0, 0, 0, 0, 0) ;
        }
    }
    else {
        //    Sinon le noeud est exterieur et non vide
        //    On crée donc des nouveaux enfants
        createDaughters() ;
        _totalMass += body->getMass() ;
        _xbar = (body->getx() * body->getMass() + _xbar * _totalMass)/(_totalMass + body->getMass()) ;
        _ybar = (body->gety() * body->getMass() + _ybar * _totalMass)/(_totalMass + body->getMass()) ;
        
        //    Ensuite on place ces deux corps dans les sous-cadran
        for (int i = 0; i < 4; i++) {
            (_daughters + i)->add(_body);
            (_daughters + i)->add(body);
        }
        //    On place le corps nul (de masse 0) dans le noeud
        *_body = Body(0, 0, 0, 0, 0, 0, 0, 0) ;

    }
}

//===========================================================================
//                            Calcul de la force
//===========================================================================
//
//    La fonction suivante calcule la force à laquelle est soumis
//    le corps *body, à l'aide de l'arbre préalablement construit.
//
//    Pour le calculer, on va descendre progressivement dans l'arbre :
//
//    Si le cadran rencontré est une feuille, on verifie qu'il ne contient
//    pas le corps étudié, puis on ajoute la force appliqué par ce cadran
//
//    Sinon, on regarde si la cadran peut être approximé par son barycentre
//    à l'aide du critère :
//     2 x (Longueur du cadran) < (Distance entre le corps et le barycentre)
//    Si le critère est vérifié, on applique la force imposée par le barycentre,
//    et sinon, on continue dans la descente de l'arbre
//

void Quad::computeForce(Body* body) {
    //    On commence depuis root
    
    //    Si le premier noeud rencontré est exterieur (et que ce n'est pas body)
    //    On ajoute la force au corps
    
    if (_external == 1){
        if ((body->getx() != _body->getx()) || (body->gety() != _body->gety())) {
            body->addForce(_body) ;
        }
    }
    //    Sinon on regarde si 2*_length < distance
    else {
        double d = body->distance2(_xbar, _ybar);
        if (4 * _length * _length < d) {
            //    On ajoute la force que subit le corps par le barycentre des masses
            //    contenues dans le cadran
            body->addForce(_totalMass, _xbar, _ybar) ;
        }
        else {
            //    Si le critère n'est pas satisfait, on reitère dans les sous-cadrans
            for (int i = 0; i < 4; i++) {
                (_daughters + i)->computeForce(body) ;
            }
        }
    }
}
