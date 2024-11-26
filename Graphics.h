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

/**
@brief: Initialize SDL engine
*/
int initSDL();

/**
@brief: Load images into memory as collection of pixels
@param: Array of collection of pixels that will stock the image
@return: 1 if the function goes well
*/
int loadBasicRoadSurface(SDL_Surface** basicRoadSurface);

/**
@brief: Convert all surfaces to screen textures for display
@params: All surfaces
*/
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

/**
@brief: Before closing the game, close the window and free the memory
@params: Textures and window
*/
void freeMemory(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *plaineTexture, SDL_Texture *ergTexture,
                SDL_Texture *regTexture, SDL_Texture *chasmTexture, SDL_Texture *baseTexture,
                SDL_Texture *roverUpRightTexture, SDL_Texture *roverUpLeftTexture, SDL_Texture *roverDownRightTexture,
                SDL_Texture *roverDownLeftTexture, SDL_Texture *roverTexture, t_stack *minWayStack,
                t_stack *currentStack, Tree *wayTree);

/**
@brief: Display textures
@params: The map, the renderer and textures to display
@return: Current map
*/
SDL_Texture *renderTexture(t_map *map, SDL_Renderer *renderer, SDL_FRect *rectPosition, SDL_Texture *plaineTexture,
                           SDL_Texture *ergTexture, SDL_Texture *regTexture, SDL_Texture *chasmTexture,
                           SDL_Texture *baseTexture, SDL_Texture *roverUpRightTexture, SDL_Texture *roverUpLeftTexture,
                           SDL_Texture *roverDownRightTexture, SDL_Texture *roverDownLeftTexture,
                           SDL_Texture *roverTexture, SDL_Texture *hillDownLeftTexture,
                           SDL_Texture *hillDownRightTexture, SDL_Texture *hillUpLeftTexture,
                           SDL_Texture *hillUpRightTexture, const Robot *robot);

/**
@brief: Inform the player of the best road and handles cases as robot stuck in the mud.
@params: The map, the robot and information about precedents moves
*/
void movementFunction(t_map *map, const Robot *robot, int beginARound, int *noMoveCounter, t_stack *minWayStack,
                      t_move *nextMove, int *didAMovement);

/**
@brief: Move the robot properly if he is on a hill.
@params: The map and the robot.
*/
void hillMovement(t_map *map, Robot *robot);

/**
@brief: Checks success and loose condition. Print adequate message and send signal to close the game.
@params: The map, the counter of move done, the robot
*/
int stopConditions(t_map *map, int noMoveCounter, const Robot *robot);

/**
@brief: Captures and interprets user inputs.
@params: The robot, the nextMove, didAMovement for letting the game processing the movements, and event for capturing.
*/
int keyboardEvent(Robot *robot, t_move *nextMove, int didAMovement, SDL_Event *event, t_map map);

#endif //ROVERRUN_GRAPHICS_H
