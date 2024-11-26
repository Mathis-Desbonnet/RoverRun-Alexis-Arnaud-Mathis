//
// Created by Mathi on 10/25/2024.
//

#ifndef ROVERRUN_TREE_H
#define ROVERRUN_TREE_H

#include "Node.h"
#include "moves.h"
#include "map.h"
#include "stack.h"
#include <stdio.h>

/**
 * @brief The tree storing each road alvailable
 */
typedef struct tree {
    Node* head;
} Tree;

/**
 * @brief Creates and Initializes the tree from the position of the robot
 * @param valueRobotPos : the case where the robot is currently placed
 * @param moveProba : Probability of each movement being drawn
 */
Tree* createTree(int valueRobotPos, int moveProba[7]);
void printTree(Tree* tree, int min);
void printTreeRecur(Node *node, int min);
int addAllWayToTree(Node *head, t_localisation robotPos, t_map map, t_move *possibilities, int *min, t_stack *minStack, t_stack *currentStack, int numberOfMovement);

#endif //ROVERRUN_TREE_H
