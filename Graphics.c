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
//    if (TTF_Init() == -1) {
//        printf("TTF_Init: %s\n", SDL_GetError());
//        return 0;
//    }
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
                   SDL_Texture **hillUpRightTexture) {
    (*plaineTexture) = SDL_CreateTextureFromSurface(renderer, plainsSurface);
    (*ergTexture) = SDL_CreateTextureFromSurface(renderer, ergSurface);
    (*regTexture) = SDL_CreateTextureFromSurface(renderer, regSurface);
    (*chasmTexture) = SDL_CreateTextureFromSurface(renderer, chasmSurface);
    (*baseTexture) = SDL_CreateTextureFromSurface(renderer, baseSurface);
    (*roverUpRightTexture) = SDL_CreateTextureFromSurface(renderer, roverUpRightSurface);
    (*roverUpLeftTexture) = SDL_CreateTextureFromSurface(renderer, roverUpLeftSurface);
    (*roverDownRightTexture) = SDL_CreateTextureFromSurface(renderer, roverDownRightSurface);
    (*roverDownLeftTexture) = SDL_CreateTextureFromSurface(renderer, roverDownLeftSurface);
    (*roverTexture) = NULL;
    (*hillDownLeftTexture) = SDL_CreateTextureFromSurface(renderer, hillDownLeftSurface);
    (*hillDownRightTexture) = SDL_CreateTextureFromSurface(renderer, hillDownRightSurface);
    (*hillUpLeftTexture) = SDL_CreateTextureFromSurface(renderer, hillUpLeftSurface);
    (*hillUpRightTexture) = SDL_CreateTextureFromSurface(renderer, hillUpRightSurface);//CONVERT SURFACE TO SCREEN TEXTURE
//BASE TEXTURE
//ROVER TEXTURE
//HILL TEXTURE
    SDL_Texture* hillTexture = NULL;

    //DESTROY SURFACE (FREE MEMORY)

    SDL_DestroySurface(plainsSurface);
    SDL_DestroySurface(ergSurface);
    SDL_DestroySurface(regSurface);
    SDL_DestroySurface(chasmSurface);
    SDL_DestroySurface(baseSurface);

    SDL_DestroySurface(roverUpRightSurface);
    SDL_DestroySurface(roverUpLeftSurface);
    SDL_DestroySurface(roverDownRightSurface);
    SDL_DestroySurface(roverDownLeftSurface);

    SDL_DestroySurface(hillDownLeftSurface);
    SDL_DestroySurface(hillDownRightSurface);
    SDL_DestroySurface(hillUpLeftSurface);
    SDL_DestroySurface(hillUpRightSurface);
}


void freeMemory(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *plaineTexture, SDL_Texture *ergTexture,
                SDL_Texture *regTexture, SDL_Texture *chasmTexture, SDL_Texture *baseTexture,
                SDL_Texture *roverUpRightTexture, SDL_Texture *roverUpLeftTexture, SDL_Texture *roverDownRightTexture,
                SDL_Texture *roverDownLeftTexture, SDL_Texture *roverTexture, t_stack *minWayStack,
                t_stack *currentStack, Tree *wayTree) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    free(wayTree);
    free((*currentStack).values);
    free((*minWayStack).values);

    SDL_DestroyTexture(plaineTexture);
    SDL_DestroyTexture(ergTexture);
    SDL_DestroyTexture(regTexture);
    SDL_DestroyTexture(chasmTexture);
    SDL_DestroyTexture(baseTexture);

    SDL_DestroyTexture(roverUpRightTexture);
    SDL_DestroyTexture(roverUpLeftTexture);
    SDL_DestroyTexture(roverDownRightTexture);
    SDL_DestroyTexture(roverDownLeftTexture);
    SDL_DestroyTexture(roverTexture);
}


SDL_Texture *renderTexture(t_map *map, SDL_Renderer *renderer, SDL_FRect *rectPosition, SDL_Texture *plaineTexture,
                           SDL_Texture *ergTexture, SDL_Texture *regTexture, SDL_Texture *chasmTexture,
                           SDL_Texture *baseTexture, SDL_Texture *roverUpRightTexture, SDL_Texture *roverUpLeftTexture,
                           SDL_Texture *roverDownRightTexture, SDL_Texture *roverDownLeftTexture,
                           SDL_Texture *roverTexture, SDL_Texture *hillDownLeftTexture,
                           SDL_Texture *hillDownRightTexture, SDL_Texture *hillUpLeftTexture,
                           SDL_Texture *hillUpRightTexture, const Robot *robot) {
    SDL_RenderClear(renderer);
    for (int i = 0; i < (*map).y_max; i++) {
        for (int j = 0; j < (*map).x_max; j++) {
            (*rectPosition).x = 32 * (j - i) + 400;
            (*rectPosition).y = 16 * (j + i) + 50;
            (*rectPosition).h = 64;
            (*rectPosition).w = 64;
            switch ((*map).soils[i][j]) {
                case 1:
                    SDL_RenderTexture(renderer, plaineTexture, NULL, rectPosition);
                    break;
                case 2:
                    SDL_RenderTexture(renderer, ergTexture, NULL, rectPosition);
                    break;
                case 3:
                    SDL_RenderTexture(renderer, regTexture, NULL, rectPosition);
                    break;
                case 4:
                    SDL_RenderTexture(renderer, chasmTexture, NULL, rectPosition);
                    break;
                case 5:
                    SDL_RenderTexture(renderer, hillDownLeftTexture, NULL, rectPosition);
                    break;
                case 6:
                    SDL_RenderTexture(renderer, hillDownRightTexture, NULL, rectPosition);
                    break;
                case 7:
                    SDL_RenderTexture(renderer, hillUpLeftTexture, NULL, rectPosition);
                    break;
                case 8:
                    SDL_RenderTexture(renderer, hillUpRightTexture, NULL, rectPosition);
                    break;
                default:
                    (*rectPosition).h = 88;
                    (*rectPosition).w = 64;
                    (*rectPosition).y -= 88 - 64;
                    SDL_RenderTexture(renderer, baseTexture, NULL, rectPosition);
                    break;
            }

        }
    }
    switch (robot->localisation.ori) {
        case 0:
            roverTexture = roverUpRightTexture;
            break;
        case 1:
            roverTexture = roverDownRightTexture;
            break;
        case 2:
            roverTexture = roverDownLeftTexture;
            break;
        case 3:
            roverTexture = roverUpLeftTexture;
            break;
    }
    (*rectPosition).x = 32 * (robot->localisation.pos.x - robot->localisation.pos.y) + 400;
    (*rectPosition).y = 16 * (robot->localisation.pos.x + robot->localisation.pos.y) + 10;
    SDL_RenderTexture(renderer, roverTexture, NULL, rectPosition);
    SDL_RenderPresent(renderer);
    return roverTexture;
}

void movementFunction(t_map *map, const Robot *robot, int beginARound, int *noMoveCounter, t_stack *minWayStack,
                      t_move *nextMove, int *didAMovement) {
    if (!(*didAMovement)) {
        if (beginARound) {
            printf("The best road available is : ");
            printStack((*minWayStack));
            beginARound = 0;
        }
        if ((*minWayStack).nbElts > 0) {
            (*nextMove) = pop(minWayStack);
            if ((*map).soils[robot->localisation.pos.y][robot->localisation.pos.x] == 2) {
                printf("Stuck in the mud !!!!!\n");
                switch ((*nextMove)) {
                    case F_10:
                        (*nextMove) = NO_MOVE;
                        break;
                    case F_20:
                        (*nextMove) = F_10;
                        break;
                    case F_30:
                        (*nextMove) = F_20;
                        break;
                    case B_10:
                        (*nextMove) = NO_MOVE;
                        break;
                    case T_LEFT:
                        (*nextMove) = NO_MOVE;
                        break;
                    case T_RIGHT:
                        (*nextMove) = NO_MOVE;
                        break;
                    case U_TURN:
                        (*nextMove) = rand()%2 + 4;
                        break;
                    default:
                        (*nextMove) = NO_MOVE;
                        break;
                }
            }
            printf("The next movement is gonna be : %s \n", getMoveAsString((*nextMove)));
            (*didAMovement) = 1;
        }
        if ((*nextMove) == NO_MOVE || (*nextMove) == LOST_SIGNAL) {
            (*noMoveCounter) += 1;
        }
    }
}

void hillMovement(t_map *map, Robot *robot) {
    if ((*map).soils[robot->localisation.pos.y][robot->localisation.pos.x] >= 5) {
        switch ((*map).soils[robot->localisation.pos.y][robot->localisation.pos.x]) {
            case 5:
                robot->localisation.pos.y += 1;
                break;
            case 6:
                robot->localisation.pos.x += 1;
                break;
            case 7:
                robot->localisation.pos.x -= 1;
                break;
            case 8:
                robot->localisation.pos.y -= 1;
                break;

        }
    }
}

int stopConditions(t_map *map, int noMoveCounter, const Robot *robot) {
    int running;
    if (noMoveCounter == 5) {
        printf("There is no move that can help our Rover.... It will remain on Mars forever...\n");
        running = 0;
    }
    if ((*map).soils[robot->localisation.pos.y][robot->localisation.pos.x] == 0) {
        printf("YOU WIN !\n");
        running = 0;
    }
    return running;
}

int keyboardEvent(Robot *robot, t_move *nextMove, int didAMovement, SDL_Event *event) {
    int running;
    if (SDL_PollEvent(event) > 0) {
        switch ((*event).type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                if ((*event).key.key == SDLK_RIGHT) {
                    if (didAMovement) {
                        didAMovement = 0;
                        if ((*nextMove) != NO_MOVE) {
                            robot->localisation = move(robot->localisation, (*nextMove));
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    return didAMovement;
}