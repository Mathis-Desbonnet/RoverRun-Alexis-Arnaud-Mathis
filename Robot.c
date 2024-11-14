//
// Created by Mathi on 10/25/2024.
//

#include "Robot.h"

Robot* createRobot(int x, int y) {
    Robot* robot = (Robot*) malloc(sizeof(Robot));
    robot->localisation = loc_init(x, y, 0);
    robot->printChar = 'X';
    return robot;
}

void displayRobot(Robot robot) {
    printf("%c", robot.printChar);
}