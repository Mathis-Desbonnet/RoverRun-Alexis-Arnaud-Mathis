//
// Created by Mathi on 11/15/2024.
//

#include "Graphics.h"

int initSDL() {
    if(!SDL_Init( SDL_INIT_VIDEO ))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("SDL IMAGE could not initialize!");
        return 0;
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}
int loadBasicRoadSurface(SDL_Surface** basicRoadSurface) {
    basicRoadSurface[0] = IMG_Load("../src/img/plains.png");
    assert(basicRoadSurface[0] == NULL);
    basicRoadSurface[1] = IMG_Load("../src/img/erg.png");
    assert(basicRoadSurface[1] == NULL);
    basicRoadSurface[2] = IMG_Load("../src/img/reg.png");
    assert(basicRoadSurface[2] == NULL);
    basicRoadSurface[3] = IMG_Load("../src/img/chasm.png");
    assert(basicRoadSurface[3] == NULL);
    basicRoadSurface[4] = IMG_Load("../src/img/base.png");
    assert(basicRoadSurface[4] == NULL);
    return 1;
}