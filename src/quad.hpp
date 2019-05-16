//
//  class_quad.hpp
//  PROJET_CPP
//
//  Created by VIVIER TANGUY on 31/10/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#ifndef quad_hpp
#define quad_hpp

#include <stdio.h>
#include "body.hpp"

class Body;
class System;


class Quad {

	//                                      Description :
    //
    //    La classe Quad représente des cadrans qui contiennent les corps, ils sont de forme carrée
    //    et peuvent être divisés en 4 sous-cadrans de même forme, mais 4 fois moins grand.
    //    L'interêt de ces cadrans est de pouvoir regrouper les corps dans des amas afin de calculer
    //    la force exercée par le barycentre de ces amas, plutôt que de calculer la force exercée par
    //    chacun des corps. On peut ainsi réduire le temps de calcul drastiquement, en passant d'une
    //    compléxité en O(n^2) à une compléxité en O(nlog(n)). L'algorithme fût présenté pour la première
    //    fois par les chercheurs Barnes et Hut.
    //    http://arborjs.org/docs/barnes-hut

    private :

    double _xmid;                  //    Milieu du cadran (x)
    double _ymid;                  //    Milieu du cadran (y)
    double _length;                //    Longueur du cadran

    double _xbar;                  //    Coordonnée du barycentre du cadran
    double _ybar;                  //    Coordonnée du barycentre du cadran
    double _totalMass;             //    Masse totale du cadran
    int _external;                 //    Renseigne si le noeud est externe (1 si oui, 0 sinon)

    Quad* _daughters;              //    Cadrans enfants
    Body* _body;                   //    Corps contenu dans le noeud
    int _nbNodes;                  //    Nombre de noeuds dans le cadran (Utile pour l'affichage en temps réel)

    public :

    Quad(double x, double y, double length);

    Quad NE();                     //    Sous-cadran Nord-Est
    Quad NW();                     //    Sous-cadran Nord-Ouest
    Quad SE();                     //    Sous-cadran Sud-Est
    Quad SW();                     //    Sous-cadran Sud-Ouest

    void createDaughters();        //    Initialisation des sous-cadran

    void add(Body* body);          //    Ajoute un nouveau corps dans le cadran
    bool in(double x, double y);   //    Verifie si (x,y) est dans le cadran
    bool in(Body* body);           //    Vérifie si le corps est dans le cadran
    void printQuad();              //    Affiche le cadran dans la console (pour debugger)
    Quad getSub(int i);            //    Renvoie le sous cadran i, (0:NE, 1:NW, 2:SE, 3:SW)
    int getNodes();                //    Renvoie le nombre de noeuds dans le cadran

    void computeForce(Body* body); //    Calcule la force imposée à body grâce au cadran

};

#endif /* class_quad_hpp */
