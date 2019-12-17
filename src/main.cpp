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
#include "rec.hpp"
#include <string>

# define SCALE 1e18  // Echelle
# define Ms 1e30     // Masse de référence (ici masse solaire)
# define DT 1e11     // Pas de temps

#ifndef REC
    # define REC 0    
#endif

#ifndef DELAY
    #define DELAY 0
#endif

int mainloopTree(Body* bodies, int n) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
		  "N Bodies",
		  SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800, 800, 0);

    if (window == NULL) {
	   printf("Could not create window. %s\n", SDL_GetError());
	   return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
		  window, -1, SDL_RENDERER_ACCELERATED);

    Quad root=Quad(0, 0, 2*SCALE) ;
    for (int i=0; i < n; i++) {
        root.add(bodies + i) ;
    }

    int j = 0 ;

    bool is_running = true;
    SDL_Event event;
    while (is_running) {
	   SDL_PollEvent(&event);
	   if (event.type == SDL_QUIT) {
		  is_running = false;
	   }

	   j++;

	   for (int i = 0; i < n; i++) {
		  root.computeForce(bodies + i) ;
		  (bodies + i)->addForce(1e36, 0, 0) ;
	   }

	   update(N, bodies, DT);
	   resetForce(N, bodies);

	   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	   SDL_RenderClear(renderer);
	   plot(N, bodies, SCALE, renderer) ;
	   SDL_RenderPresent(renderer);

	   if (REC) {
		  save_screenshot(renderer, j);
		  j++;
	   }
    }
    return 0;
}

int main() {
    Body* bodies = initGalaxy(N) ;
    return mainloopTree(bodies, N) ;
}
