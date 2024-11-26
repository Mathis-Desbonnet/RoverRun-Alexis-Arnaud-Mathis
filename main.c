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
    map = createMapFromFile("..\\maps\\map2.map");
#else
    map = createMapFromFile("../maps/map2.map");
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

    SDL_Surface* hillDownLeftSurface = IMG_Load("../src/img/hill/hillDownLeft.png");
    SDL_Surface* hillDownRightSurface = IMG_Load("../src/img/hill/hillDownRight.png");
    SDL_Surface* hillUpLeftSurface = IMG_Load("../src/img/hill/hillUpLeft.png");
    SDL_Surface* hillUpRightSurface = IMG_Load("../src/img/hill/hillUpRight.png");


    if (plainsSurface == NULL || ergSurface == NULL || regSurface == NULL || chasmSurface == NULL) {
        printf("Problem Surface");
    }

    //CREATE RECT TO PLACE SURFACE

    SDL_FRect rectPosition;
    rectPosition.y = 50;
    rectPosition.x = 50;
    rectPosition.h = 128;
    rectPosition.w = 128;

    SDL_Texture *plaineTexture;
    SDL_Texture *ergTexture;
    SDL_Texture *regTexture;
    SDL_Texture *chasmTexture;
    SDL_Texture *baseTexture;
    SDL_Texture *roverUpRightTexture;
    SDL_Texture *roverUpLeftTexture;
    SDL_Texture *roverDownRightTexture;
    SDL_Texture *roverDownLeftTexture;
    SDL_Texture *roverTexture;
    SDL_Texture *hillDownLeftTexture;
    SDL_Texture *hillDownRightTexture;
    SDL_Texture *hillUpLeftTexture;
    SDL_Texture *hillUpRightTexture;

    createTextureImage(renderer, plainsSurface, ergSurface, regSurface, chasmSurface, baseSurface, roverUpRightSurface,
                       roverUpLeftSurface, roverDownRightSurface, roverDownLeftSurface, hillDownLeftSurface,
                       hillDownRightSurface,
                       hillUpLeftSurface, hillUpRightSurface, &plaineTexture, &ergTexture, &regTexture, &chasmTexture,
                       &baseTexture,
                       &roverUpRightTexture, &roverUpLeftTexture, &roverDownRightTexture, &roverDownLeftTexture,
                       &roverTexture,
                       &hillDownLeftTexture, &hillDownRightTexture, &hillUpLeftTexture, &hillUpRightTexture);

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
        movementFunction(&map, robot, beginARound, &noMoveCounter, &minWayStack, &nextMove, &didAMovement);
        SDL_Event event;
        didAMovement = keyboardEvent(robot, &nextMove, didAMovement, &event);
        roverTexture = renderTexture(&map, renderer, &rectPosition, plaineTexture, ergTexture, regTexture, chasmTexture,
                                     baseTexture,
                                     roverUpRightTexture, roverUpLeftTexture, roverDownRightTexture,
                                     roverDownLeftTexture, roverTexture,
                                     hillDownLeftTexture, hillDownRightTexture, hillUpLeftTexture, hillUpRightTexture,
                                     robot);
        hillMovement(&map, robot);
        running = stopConditions(&map, noMoveCounter, robot);
        //CREATE NEXT TREE
        if (minWayStack.nbElts <= 0 && !didAMovement && running) {
            noMoveCounter = 0;
            min = 10000;
            printf("Trying to create a Tree\n");
            free(wayTree);
            free(currentStack.values);
            free(minWayStack.values);
            printf("free memory\n");
            currentStack = createStack(7);
            minWayStack = createStack(7);
            wayTree = createTree(map.costs[robot->localisation.pos.y][robot->localisation.pos.x], robot->localisation,
                                 map, moveProba);
            printf("x :%d, y :%d, ori : %d\n", x, y, robot->localisation.ori);
            printf("0 -> NORD\n 1-> EST\n 2-> SUD\n 3 -> OUEST\n");
            if (map.soils[robot->localisation.pos.y][robot->localisation.pos.x] == 3 % 10) {
                addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min,
                                &minWayStack, &currentStack, 4);
            } else {
                addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min,
                                &minWayStack, &currentStack, 5);
            }
            if (minWayStack.nbElts == 0) {
                printf("NO POSSIBILITIES !!\n");
                running = 0;
            }
            printf("TREE CREATED\n");
            if (minWayStack.nbElts > 0) {
                pop(&minWayStack);
            }
            beginARound = 1;
            for (int i = 0; i<15; i++) {
                printf("\n");
            }
        }
    }
    freeMemory(window, renderer, plaineTexture, ergTexture, regTexture, chasmTexture, baseTexture, roverUpRightTexture,
               roverUpLeftTexture, roverDownRightTexture, roverDownLeftTexture, roverTexture, &minWayStack,
               &currentStack,
               wayTree);

    free(robot);

    return 0;
}