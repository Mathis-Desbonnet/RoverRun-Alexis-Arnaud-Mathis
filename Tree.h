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

/**
 * @brief Print the tree create recursively
 * @param node : the first node of the tree
 * @param min : the min value (used in some case for print)
 */
void printTreeRecur(Node *node, int min);

/**
 * @brief Create the tree and find the best way in one function and while creating the tree
 * @param head : the parent node of the tree
 * @param robotPos : position of the robot
 * @param map : the map, seems logical
 * @param possibilities : an array of the next movement possible
 * @param min : the min value that we are updating... sometimes
 * @param minStack : the stack that stock the best way
 * @param currentStack : the stack that stock the way that we are currently on
 * @param numberOfMovement : the number of movement that we are doing
 */
int addAllWayToTree(Node *head, t_localisation robotPos, t_map map, t_move *possibilities, int *min, t_stack *minStack, t_stack *currentStack, int numberOfMovement);

#endif //ROVERRUN_TREE_H
