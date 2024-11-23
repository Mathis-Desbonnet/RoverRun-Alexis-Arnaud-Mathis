#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
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
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    //LOAD SDL
    int running = 1;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        SDL_Log( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("New Window", 1920, 1080, SDL_WINDOW_FULLSCREEN, &window, &renderer);

    IMG_Init(IMG_INIT_PNG);

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
    rectPosition.h = 256;
    rectPosition.w = 256;

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

    Robot* robot = createRobot(3, 5);

    int min = 10000;
    t_move movementDisponibility[7] = {22, 15, 7, 7, 21, 21, 7};
    t_stack minWayStack = createStack(7);
    t_stack currentStack = createStack(7);
    Tree* wayTree = createTree(map.costs[robot->localisation.pos.x][robot->localisation.pos.y], robot->localisation, map, movementDisponibility);
    addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack);
    printTree(*wayTree, min);
    printf("%d\n", min);
    printStack(minWayStack);
    t_move nextMove;

    //SDL LOOP
    while (running) {
        SDL_Event event;
        if (SDL_PollEvent(&event) > 0) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
        for (int i = 0; i<map.y_max; i++) {
            for (int j = 0; j<map.x_max; j++) {
                rectPosition.x = 128*(j-i)+800;
                rectPosition.y = 64*(j+i)+50;
                rectPosition.h = 256;
                rectPosition.w = 256;
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
                        rectPosition.h = 352;
                        rectPosition.w = 256;
                        rectPosition.y -= 352-256;
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
        rectPosition.x = 128*(robot->localisation.pos.x - robot->localisation.pos.y)+800;
        rectPosition.y = 64*(robot->localisation.pos.x + robot->localisation.pos.y)-100;
        SDL_RenderTexture(renderer, roverTexture, NULL, &rectPosition);
        SDL_RenderPresent(renderer);
        if (minWayStack.nbElts > 0) {
            nextMove = pop(&minWayStack);
            robot->localisation = move(robot->localisation, nextMove);
        }
        SDL_Delay(1000);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

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

    return 0;
}
