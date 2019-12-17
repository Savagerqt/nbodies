#include "rec.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <string>

void save_screenshot(SDL_Renderer* renderer, int index) {
    SDL_Surface *sshot = SDL_CreateRGBSurface(
		  0, 800, 800, 32, 0x00ff0000, 0x0000ff00, 
		  0x000000ff, 0xff000000);
    SDL_RenderReadPixels(
		  renderer, NULL, SDL_PIXELFORMAT_ARGB8888, 
		  sshot->pixels, sshot->pitch);
    std::string name = (
	   "~/sreenshots/" + std::to_string(index) + ".bmp");
    SDL_SaveBMP(sshot, name.c_str());
    SDL_FreeSurface(sshot);
}
