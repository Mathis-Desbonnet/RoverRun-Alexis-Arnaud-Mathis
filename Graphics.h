//
// Created by Mathi on 11/15/2024.
//

#ifndef ROVERRUN_GRAPHICS_H
#define ROVERRUN_GRAPHICS_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <assert.h>

int initSDL();
int loadBasicRoadSurface(SDL_Surface** basicRoadSurface);

#endif //ROVERRUN_GRAPHICS_H
