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

typedef struct tree {
    Node* head;
} Tree;

Tree* createTree(int valueRobotPos, t_localisation robotPos, t_map map, int moveProba[7]);
void printTree(Tree* tree, int min);
void printTreeRecur(Node *node, int min);
int addAllWayToTree(Node *head, t_localisation robotPos, t_map map, t_move *possibilities, int *min, t_stack *minStack, t_stack *currentStack, int numberOfMovement);

#endif //ROVERRUN_TREE_H
