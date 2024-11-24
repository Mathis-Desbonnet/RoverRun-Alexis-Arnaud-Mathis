#include <stdio.h>
#include "Graphics.h"
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "loc.h"
#include "Robot.h"
#include "Tree.h"

int main(int argc, char* args[]) {
    //LOAD MAP AND INITIALIZE VARIABLE
    t_map map;
    srand(time(NULL));

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\map1.map");
#else
    map = createMapFromFile("../maps/map1.map");
#endif

    //INIT SDL
    if (!initSDL()) {
        printf("Something went wrong....");
        return 0;
    }

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    //CREATE WINDOW AND RENDERER
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("New Window", 1080, 720, SDL_WINDOW_MAXIMIZED, &window, &renderer);

    //LOAD PNG TO SURFACE
    SDL_Surface* plainsSurface = IMG_Load("../src/img/plains.png");
    SDL_Surface* ergSurface = IMG_Load("../src/img/erg.png");
    SDL_Surface* regSurface = IMG_Load("../src/img/reg.png");
    SDL_Surface* chasmSurface = IMG_Load("../src/img/chasm.png");
    SDL_Surface* baseSurface = IMG_Load("../src/img/base.png");

    SDL_Surface* roverUpRightSurface = IMG_Load("../src/img/rover/RoverUpRight.png");
    SDL_Surface* roverUpLeftSurface = IMG_Load("../src/img/rover/RoverUpLeft.png");
    SDL_Surface* roverDownRightSurface = IMG_Load("../src/img/rover/RoverDownRight.png");
    SDL_Surface* roverDownLeftSurface = IMG_Load("../src/img/rover/RoverDownLeft.png");

    if (plainsSurface == NULL || ergSurface == NULL || regSurface == NULL || chasmSurface == NULL) {
        printf("Problem Surface");
    }

    //CREATE RECT TO PLACE SURFACE

    SDL_FRect rectPosition;
    rectPosition.y = 50;
    rectPosition.x = 50;
    rectPosition.h = 128;
    rectPosition.w = 128;

    //CONVERT SURFACE TO SCREEN TEXTURE
        //BASE TEXTURE
    SDL_Texture* plaineTexture = SDL_CreateTextureFromSurface(renderer, plainsSurface);
    SDL_Texture* ergTexture = SDL_CreateTextureFromSurface(renderer, ergSurface);
    SDL_Texture* regTexture = SDL_CreateTextureFromSurface(renderer, regSurface);
    SDL_Texture* chasmTexture = SDL_CreateTextureFromSurface(renderer, chasmSurface);
    SDL_Texture* baseTexture = SDL_CreateTextureFromSurface(renderer, baseSurface);
        //ROVER TEXTURE
    SDL_Texture* roverUpRightTexture = SDL_CreateTextureFromSurface(renderer, roverUpRightSurface);
    SDL_Texture* roverUpLeftTexture = SDL_CreateTextureFromSurface(renderer, roverUpLeftSurface);
    SDL_Texture* roverDownRightTexture = SDL_CreateTextureFromSurface(renderer, roverDownRightSurface);
    SDL_Texture* roverDownLeftTexture = SDL_CreateTextureFromSurface(renderer, roverDownLeftSurface);
    SDL_Texture* roverTexture = NULL;

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

    //CREATE TEXT VARIABLE

//    TTF_Font *font;
//    font = TTF_OpenFont("../CircleOfDust.ttf", 16);
//    if(!font) {
//        printf("TTF_OpenFont: %s\n", SDL_GetError());
//    }

//    SDL_Color color={255,255,255};
//    TTF_CreateRendererTextEngine(renderer);
//    SDL_Surface *text_surface = TTF_RenderText_Solid(font,"Hello World!", 13, color);
//    SDL_Texture* textTexture;
//    if(text_surface == NULL) {
//        printf("Cannot create a text surface");
//    } else {
//        printf("OUIII");
//        textTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
//    }

    //CREATE ROBOT VARIABLE

    int x,y;

    int noMoveCounter = 0;

    do {
        x = rand()%map.x_max;
        y = rand()%map.y_max;
    } while (map.soils[y][x] == 4 || map.soils[y][x] == 0);

    Robot* robot = createRobot(x, y);
    robot->localisation.ori = rand()%4;

    printf("x :%d, y :%d, ori : %d\n", x, y, robot->localisation.ori);
    printf("0 -> NORD\n 1-> EST\n 2-> SUD\n 3 -> OUEST\n");

    int min = 10000;
    t_stack minWayStack = createStack(7);
    t_stack currentStack = createStack(7);
    int moveProba[7] = {22, 15, 7, 7, 21, 21, 7};
    Tree* wayTree = createTree(map.costs[robot->localisation.pos.y][robot->localisation.pos.x], robot->localisation, map, moveProba);
    if (map.soils[robot->localisation.pos.y][robot->localisation.pos.x] == 3%10) {
        addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack, 4);
    } else {
        addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack, 5);
    }
    //printTree(wayTree, min);
    printf("%d\n", min);

    t_move nextMove;

    for (int i = 0; i<15; i++) {
        printf("\n");
    }

    int didAMovement = 0;
    int beginARound = 1;

    if (minWayStack.nbElts > 0) {
        pop(&minWayStack);
    }

    currentStack = createStack(7);

    //SDL LOOP
    int running = 1;
    while (running) {
        if (!didAMovement) {
            if (beginARound) {
                printf("The best road available is : ");
                printStack(minWayStack);
                beginARound = 0;
            }
            if (minWayStack.nbElts > 0) {
                nextMove = pop(&minWayStack);
                printf("The next movement is gonna be : %s \n", getMoveAsString(nextMove));
                didAMovement = 1;
            }
            if (nextMove == NO_MOVE || nextMove == LOST_SIGNAL) {
                noMoveCounter += 1;
            }
        }
        SDL_Event event;
        if (SDL_PollEvent(&event) > 0) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_RIGHT) {
                        if (didAMovement) {
                            didAMovement = 0;
                            if (nextMove != NO_MOVE) {
                                robot->localisation = move(robot->localisation, nextMove);
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
//        rectPosition.x = 1000;
//        rectPosition.y = 100;
//        rectPosition.h = 1000;
//        rectPosition.w = 1000;
//        SDL_RenderTexture(renderer, textTexture, NULL, &rectPosition);
        for (int i = 0; i<map.y_max; i++) {
            for (int j = 0; j<map.x_max; j++) {
                rectPosition.x = 32*(j-i)+300;
                rectPosition.y = 16*(j+i)+50;
                rectPosition.h = 64;
                rectPosition.w = 64;
                switch (map.soils[i][j]) {
                    case 1:
                        SDL_RenderTexture(renderer, plaineTexture, NULL, &rectPosition);
                        break;
                    case 2:
                        SDL_RenderTexture(renderer, ergTexture, NULL, &rectPosition);
                        break;
                    case 3:
                        SDL_RenderTexture(renderer, regTexture, NULL, &rectPosition);
                        break;
                    case 4:
                        SDL_RenderTexture(renderer, chasmTexture, NULL, &rectPosition);
                        break;
                    default:
                        rectPosition.h = 88;
                        rectPosition.w = 64;
                        rectPosition.y -= 88-64;
                        SDL_RenderTexture(renderer, baseTexture, NULL, &rectPosition);
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
        rectPosition.x = 32*(robot->localisation.pos.x - robot->localisation.pos.y)+300;
        rectPosition.y = 16*(robot->localisation.pos.x + robot->localisation.pos.y)+10;
        SDL_RenderTexture(renderer, roverTexture, NULL, &rectPosition);
        SDL_RenderPresent(renderer);
        if (noMoveCounter == 5) {
            printf("There is no move that can help our Rover.... It will remain on Mars forever...\n");
            running = 0;
        }
        if (map.soils[robot->localisation.pos.y][robot->localisation.pos.x] == 0) {
            printf("YOU WIN !\n");
            running = 0;
        }
        if (minWayStack.nbElts <= 0 && !didAMovement && running) {
            noMoveCounter = 0;
            do {
                printf("Trying to create a Tree\n");
                free(wayTree);
                free(currentStack.values);
                free(minWayStack.values);
                printf("free memory\n");
                currentStack = createStack(7);
                minWayStack = createStack(7);
                wayTree = createTree(map.costs[robot->localisation.pos.y][robot->localisation.pos.x], robot->localisation, map, moveProba);
                printf("x :%d, y :%d, ori : %d\n", x, y, robot->localisation.ori);
                printf("0 -> NORD\n 1-> EST\n 2-> SUD\n 3 -> OUEST\n");
                if (map.soils[robot->localisation.pos.y][robot->localisation.pos.x] == 3%10) {
                    addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack, 4);
                } else {
                    addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack, 5);
                }
            } while (minWayStack.nbElts == 0);
            printf("TREE CREATED\n");
            //printTree(wayTree, min);
            if (minWayStack.nbElts > 0) {
                pop(&minWayStack);
            }
            beginARound = 1;
            for (int i = 0; i<15; i++) {
                printf("\n");
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    free(wayTree);
    free(currentStack.values);
    free(minWayStack.values);

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

    free(robot);

    return 0;
}
