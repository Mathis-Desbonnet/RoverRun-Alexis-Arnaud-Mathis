//
// Created by Mathi on 10/25/2024.
//

#ifndef ROVERRUN_ROBOT_H
#define ROVERRUN_ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#include "loc.h"

typedef struct robot {
    t_localisation localisation;
    char printChar;
} Robot;

Robot* createRobot(int x, int y);

void displayRobot(Robot robot);

#endif //ROVERRUN_ROBOT_H
