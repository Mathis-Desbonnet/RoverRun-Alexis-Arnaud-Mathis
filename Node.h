//
// Created by Mathi on 10/25/2024.
//

#ifndef ROVERRUN_NODE_H
#define ROVERRUN_NODE_H

#include <stdlib.h>
#include "moves.h"

typedef struct node {
    int value;
    int depth;
    int numberChilds;
    int totalValue;
    struct node **avails;
    t_move possibilities[9];
    int min;
    int choice;
} Node;

Node* createNode(int valueRobotPos, t_move* possibilities, int choice, int moveProba[7]);

#endif //ROVERRUN_NODE_H
