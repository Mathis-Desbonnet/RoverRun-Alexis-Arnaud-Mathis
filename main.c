#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "loc.h"
#include "Robot.h"
#include "Tree.h"

int main(void) {
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


    Robot* robot = createRobot(2, 5);

    displayMap(map, *robot);

    int min = 10000;
    t_stack minWayStack = createStack(7);
    t_stack currentStack = createStack(7);
    Tree* wayTree = createTree(map.costs[robot->localisation.pos.x][robot->localisation.pos.y], robot->localisation, map);
    addAllWayToTree(wayTree->head, robot->localisation, map, wayTree->head->possibilities, &min, &minWayStack, &currentStack);
    printTree(*wayTree, min);
    printf("%d\n", min);
    printStack(minWayStack);
    return 0;
}
