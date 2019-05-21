//
//  main.cpp
//  NBODIES
//
//  Created by VIVIER TANGUY on 14/11/2017.
//  Copyright © 2017 VIVIER TANGUY. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "body.hpp"
#include "quad.hpp"
#include "generalbodies.hpp"
#include "initbodies.hpp"
#include <string>
using namespace std;


//===========================================================================
//                      Constantes du problème
//===========================================================================
# define SCALE 1e18                // Echelle
# define Ms 1e30                   // Masse de référence (ici masse solaire)
# define DT 1e11                   // Pas de temps
# define REC 0                     // Enregistrement des frames
//===========================================================================


//    Algorithme Brute Force
void mainloopBF(Body* bodies, int n) {

    // Initialisation du renderer SDL
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("My Screen",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 800, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int j = 0 ;
    while(j<10000) {

        // Calcul de la force subie par chacun des corps
        for (int i=0; i < n; i++) {

            // Terme de force subi par les autres corps
            for (int k=0; k<n; k++) {
                if (k != i) {
                    (bodies + i)->addForce(bodies + k);
                }
            }
            // Terme de force subi par le trou noir central
            //(bodies + i)->addForce(1e36, 0, 0) ;
            // On update la vitesse et la position du corps
        }
        update(N, bodies, DT);
        resetForce(N, bodies) ;

        // Les corps on été mis à jour, on peut donc les tracer sur le renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        plot(N, bodies, SCALE, renderer) ;
        SDL_RenderPresent(renderer);
        SDL_Delay(30) ;

        if(REC) {
            // Enregistrement des screenshots pour la création du film
            SDL_Surface *sshot = SDL_CreateRGBSurface(0, 800, 800, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
            SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
            std::string name = "/Users/viviertanguy/Documents/IMAGES/Simulation/Screenshot" + std::to_string(j) + ".bmp";
            SDL_SaveBMP(sshot, name.c_str());
            j++;
            SDL_FreeSurface(sshot);
        }
    }

}


//    Algorithme avec la structure d'arbre
void mainloopTree(Body* bodies, int n) {

    // Initialisation du renderer SDL
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("N Bodies",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 800, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialisation de l'arbre
    Quad root=Quad(0, 0, 2*SCALE) ;

    // Construction de l'arbre
    for (int i=0; i < n; i++) {
        root.add(bodies + i) ;
    }

    int j = 0 ;
    while(j<10000) {

        // Calcul de la force subie par chacun des corps
        for (int i=0; i < n; i++) {

            // Terme de force subi par les autres corps
            root.computeForce(bodies + i) ;
            // Terme de force subi par le trou noir central
            (bodies + i)->addForce(1e36, 0, 0) ;
            // On update la vitesse et la position du corps
        }
        update(N, bodies, DT);
        resetForce(N, bodies) ;

        // Les corps on été mis à jour, on peut donc les tracer sur le renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        plot(N, bodies, SCALE, renderer) ;
        SDL_RenderPresent(renderer);
        SDL_Delay(30) ;

        if(REC) {
            // Enregistrement des screenshots pour la création du film
            SDL_Surface *sshot = SDL_CreateRGBSurface(0, 800, 800, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
            SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
            std::string name = "/Users/viviertanguy/Documents/IMAGES/Simulation/Screenshot" + std::to_string(j) + ".bmp";
            SDL_SaveBMP(sshot, name.c_str());
            j++;
            SDL_FreeSurface(sshot);
        }
    }
}


int main() {
    Body* bodies = initGalaxy(N) ;       // Choisir la disposition initiale des N corps
    mainloopTree(bodies, N) ;            // Choix de l'algorithme de calcul (Brute force ou BHTree)
}
