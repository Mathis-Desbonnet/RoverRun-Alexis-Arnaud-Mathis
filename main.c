#include <stdio.h>
#include <SDL3/SDL.h>
#include "map.h"
#include "loc.h"
#include "Robot.h"
#include "Tree.h"

int main(int argc, char* argv[]) {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        SDL_Window *gWindow = SDL_CreateWindow( "SDL Tutorial", 1920, 1080, SDL_EVENT_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
//        else
//        {
//            //Initialize PNG loading
//            int imgFlags = IMG_INIT_PNG;
//            if( !( IMG_Init( imgFlags ) & imgFlags ) )
//            {
//                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
//                success = false;
//            }
//            else
//            {
//                //Get window surface
//                gScreenSurface = SDL_GetWindowSurface( gWindow );
//            }
//        }
    }

    return success;
    SDL_Quit();
    return 0;
//    t_map map;
//    srand(time(NULL));
//
//    // The following preprocessor directive checks if the code is being compiled on a Windows system.
//    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
//    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
//#if defined(_WIN32) || defined(_WIN64)
//    map = createMapFromFile("..\\maps\\example1.map");
//#else
//    map = createMapFromFile("../maps/example1.map");
//#endif
//
//    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
//    for (int i = 0; i < map.y_max; i++)
//    {
//        for (int j = 0; j < map.x_max; j++)
//        {
//            printf("%d ", map.soils[i][j]);
//        }
//        printf("\n");
//    }
//    // printf the costs, aligned left 5 digits
//    for (int i = 0; i < map.y_max; i++)
//    {
//        for (int j = 0; j < map.x_max; j++)
//        {
//            printf("%-5d ", map.costs[i][j]);
//        }
//        printf("\n");
//    }
//
//
//    Robot* robot = createRobot(2, 5);
//
//    displayMap(map, *robot);
//
//    int min = 10000;
//    t_stack minWayStack = createStack(7);
//    t_stack currentStack = createStack(7);
//    Tree* wayTree = createTree(map.costs[robot->localisation.pos.x][robot->localisation.pos.y], robot->localisation, map);
//    addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack);
//    printTree(*wayTree, min);
//    printf("%d\n", min);
//    printStack(minWayStack);
//    return 0;
}
