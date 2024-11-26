//
// Created by Mathi on 11/15/2024.
//

#ifndef ROVERRUN_GRAPHICS_H
#define ROVERRUN_GRAPHICS_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
//#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include "Tree.h"

int initSDL();
int loadBasicRoadSurface(SDL_Surface** basicRoadSurface);
void
createTextureImage(SDL_Renderer *renderer, SDL_Surface *plainsSurface, SDL_Surface *ergSurface, SDL_Surface *regSurface,
                   SDL_Surface *chasmSurface, SDL_Surface *baseSurface, SDL_Surface *roverUpRightSurface,
                   SDL_Surface *roverUpLeftSurface, SDL_Surface *roverDownRightSurface,
                   SDL_Surface *roverDownLeftSurface, SDL_Surface *hillDownLeftSurface,
                   SDL_Surface *hillDownRightSurface, SDL_Surface *hillUpLeftSurface, SDL_Surface *hillUpRightSurface,
                   SDL_Texture **plaineTexture, SDL_Texture **ergTexture, SDL_Texture **regTexture,
                   SDL_Texture **chasmTexture, SDL_Texture **baseTexture, SDL_Texture **roverUpRightTexture,
                   SDL_Texture **roverUpLeftTexture, SDL_Texture **roverDownRightTexture,
                   SDL_Texture **roverDownLeftTexture, SDL_Texture **roverTexture, SDL_Texture **hillDownLeftTexture,
                   SDL_Texture **hillDownRightTexture, SDL_Texture **hillUpLeftTexture,
                   SDL_Texture **hillUpRightTexture);

void freeMemory(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *plaineTexture, SDL_Texture *ergTexture,
                SDL_Texture *regTexture, SDL_Texture *chasmTexture, SDL_Texture *baseTexture,
                SDL_Texture *roverUpRightTexture, SDL_Texture *roverUpLeftTexture, SDL_Texture *roverDownRightTexture,
                SDL_Texture *roverDownLeftTexture, SDL_Texture *roverTexture, t_stack *minWayStack,
                t_stack *currentStack, Tree *wayTree);

SDL_Texture *renderTexture(t_map *map, SDL_Renderer *renderer, SDL_FRect *rectPosition, SDL_Texture *plaineTexture,
                           SDL_Texture *ergTexture, SDL_Texture *regTexture, SDL_Texture *chasmTexture,
                           SDL_Texture *baseTexture, SDL_Texture *roverUpRightTexture, SDL_Texture *roverUpLeftTexture,
                           SDL_Texture *roverDownRightTexture, SDL_Texture *roverDownLeftTexture,
                           SDL_Texture *roverTexture, SDL_Texture *hillDownLeftTexture,
                           SDL_Texture *hillDownRightTexture, SDL_Texture *hillUpLeftTexture,
                           SDL_Texture *hillUpRightTexture, const Robot *robot);

void movementFunction(t_map *map, const Robot *robot, int beginARound, int *noMoveCounter, t_stack *minWayStack,
                      t_move *nextMove, int *didAMovement);

void hillMovement(t_map *map, Robot *robot);

int stopConditions(t_map *map, int noMoveCounter, const Robot *robot);

int keyboardEvent(Robot *robot, t_move *nextMove, int didAMovement, SDL_Event *event);

#endif //ROVERRUN_GRAPHICS_H
