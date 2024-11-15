//
// Created by Mathi on 10/25/2024.
//

#include "Tree.h"

Tree* createTree(int valueRobotPos, t_localisation robotPos, t_map map) {
    Tree* newTree = (Tree*) malloc(sizeof(Tree));
    newTree->head = createNode(valueRobotPos, NULL, -1);
    newTree->head->totalValue = valueRobotPos;
    newTree->head->min = 10000;
    return newTree;
}

void printTree(Tree tree, int min) {
    printTreeRecur(tree.head, min);
}

int addAllWayToTree(Node *head, t_localisation robotPos, t_map map, t_move *possibilities, int *min, t_stack *minStack, t_stack *currentStack) {
    if (currentStack->nbElts == head->depth) {
        push(currentStack, head->choice);
    } else {
        while (currentStack->nbElts > head->depth) {
            pop(currentStack);
        }
        push(currentStack, head->choice);
    }
    if ((head->depth == 3 || head->value == 0) && head->totalValue < *min) {
        *min = head->totalValue;
        copyStack(*currentStack, minStack);
    }
    if (head->value == 0) { //Base detected
        if (head->totalValue < *min) {
            *min = head->totalValue;
        }
        head->min = *min;
        return 1;
    }
    if (head->totalValue < 9999 && head->totalValue <= *min && head->depth < 3) {
        Node* newNode;
        t_localisation newLoc;
        t_move *move;
        for (int i = 0; i<head->numberChilds; i++) { //Create a new Node for every child
            move = createTabWithoutCurrentValue(possibilities, i, head->numberChilds);
            newNode = NULL;
            if (possibilities[i]<4 && isValidLocalisation(translate(robotPos, possibilities[i]).pos, map.x_max, map.y_max)) {
                newLoc.pos.x = translate(robotPos, possibilities[i]).pos.x;
                newLoc.pos.y = translate(robotPos, possibilities[i]).pos.y;
                newLoc.ori = robotPos.ori;
                newNode = createNode(map.costs[newLoc.pos.y][newLoc.pos.x], move, possibilities[i]);
            } else {
                newNode = createNode(head->value, move, possibilities[i]);
                newLoc.pos.x = robotPos.pos.x;
                newLoc.pos.y = robotPos.pos.y;
                newLoc.ori = rotate(robotPos.ori, possibilities[i]);
            }
            newNode->depth = head->depth+1;
            newNode->numberChilds = head->numberChilds-1;
            newNode->totalValue = head->totalValue+newNode->value;
            newNode->min = *min;
            head->avails[i] = newNode;
            addAllWayToTree(newNode, newLoc, map, move, min, minStack, currentStack);
        }
    }
}

void printTreeRecur(Node *node, int min) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i<node->depth; i++) {
        printf("\t");
    }
    printf("%d", node->totalValue);
    if (node->numberChilds != 0) {
        printf(" ----- ");
    }
    for (int i = 0; i<node->numberChilds; i++) {
        printf("%s  ", getMoveAsString(node->possibilities[i]));
    }
    if (node->totalValue > 9999) {
        printf(" DEAD - STOPS HERE");
    }
    if (node->totalValue > node->min) {
        printf(" TOO HEAVY - STOPS HERE, MIN FOR NOW = %d", node->min);
    }
    if (node->value == 0) {
        printf(" BASE FOUND - STOPS HERE");
    }
    printf("\n");
    for (int i = 0; i<node->numberChilds; i++) {
        printTreeRecur(node->avails[i], min);
    }
}