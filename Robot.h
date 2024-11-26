//
// Created by Mathi on 10/25/2024.
//

#ifndef ROVERRUN_ROBOT_H
#define ROVERRUN_ROBOT_H

#include <stdlib.h>
#include <stdio.h>

#include "loc.h"
#include "stack.h"

/**
 * @brief Struct of the robot, storing localisation and its symbol for the array map
 */
typedef struct robot {
    t_localisation localisation;
    char printChar;
} Robot;

/**
 * @brief Creates a robot, initializes it and assign the correct position.
 * @param x: Position on the x-axis.
 * @param y: Position on the y-axis.
 * @return : Pointer to the robot
 */
Robot* createRobot(int x, int y);

/**
 * @brief Just print the robot symbol.
 * @param robot: The robot.
 */
void displayRobot(Robot robot);

#endif //ROVERRUN_ROBOT_H
