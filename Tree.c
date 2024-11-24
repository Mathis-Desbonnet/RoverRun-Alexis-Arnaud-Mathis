//
// Created by Mathi on 10/25/2024.
//

#include "Tree.h"

Tree* createTree(int valueRobotPos, t_localisation robotPos, t_map map, int moveProba[7]) {
    Tree* newTree = (Tree*) malloc(sizeof(Tree));
    newTree->head = createNode(valueRobotPos, NULL, -1, moveProba);
    newTree->head->totalValue = valueRobotPos;
    newTree->head->min = 10000;
    if (map.soils[robotPos.pos.y][robotPos.pos.x] == 2%10) {
        printf("Movement before modif with erg : ");
        for (int i = 0; i<newTree->head->numberChilds; i++) {
            printf(" %s ->", getMoveAsString(newTree->head->possibilities[i]));
            switch (newTree->head->possibilities[i]) {
                case F_10:
                    newTree->head->possibilities[i] = NO_MOVE;
                    break;
                case F_20:
                    newTree->head->possibilities[i] = F_10;
                    break;
                case F_30:
                    newTree->head->possibilities[i] = F_20;
                    break;
                case B_10:
                    newTree->head->possibilities[i] = NO_MOVE;
                    break;
                case T_LEFT:
                    newTree->head->possibilities[i] = NO_MOVE;
                    break;
                case T_RIGHT:
                    newTree->head->possibilities[i] = NO_MOVE;
                    break;
                case U_TURN:
                    newTree->head->possibilities[i] = rand()%2 + 4;
                    break;
            }
        }
        printf("\n");
    }
    return newTree;
}

void printTree(Tree* tree, int min) {
    if (tree != NULL) {
        printTreeRecur(tree->head, min);
    } else {
        printf("WARNING : TREE IS NULL !\n");
    }
}

int addAllWayToTree(Node *head, t_localisation robotPos, t_map map, t_move *possibilities, int *min, t_stack *minStack, t_stack *currentStack, int numberOfMovement) {
    if (currentStack->nbElts == head->depth) {
        push(currentStack, head->choice);
    } else {
        while (currentStack->nbElts > head->depth) {
            if (currentStack->nbElts > 0) {
                pop(currentStack);
            }
        }
        push(currentStack, head->choice);
    }
    if ((head->depth == numberOfMovement || head->value == 0) && head->totalValue < *min) {
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
    if (head->choice == LOST_SIGNAL) {
        return 1;
    }
    if (head->totalValue < 9999 && head->totalValue <= *min && head->depth < numberOfMovement) {
        Node* newNode;
        t_localisation newLoc;
        t_move *move;
        for (int i = 0; i<head->numberChilds; i++) { //Create a new Node for every child
            move = createTabWithoutCurrentValue(possibilities, i, head->numberChilds);
            newNode = NULL;
            if (isValidLocalisation((translate(robotPos, possibilities[i])).pos, map.x_max, map.y_max)) {
                if (possibilities[i]<4) {
                    newLoc.pos.x = translate(robotPos, possibilities[i]).pos.x;
                    newLoc.pos.y = translate(robotPos, possibilities[i]).pos.y;
                    newLoc.ori = robotPos.ori;
                    newNode = createNode(map.costs[newLoc.pos.y][newLoc.pos.x], move, possibilities[i], NULL);
                } else {
                    newNode = createNode(head->value, move, possibilities[i], NULL);
                    newLoc.pos.x = robotPos.pos.x;
                    newLoc.pos.y = robotPos.pos.y;
                    newLoc.ori = rotate(robotPos.ori, possibilities[i]);
                }
            } else {
                //printf("HORS MAP ! \t");
                newNode = createNode(head->value, move, LOST_SIGNAL, NULL);
                newLoc.pos.x = robotPos.pos.x;
                newLoc.pos.y = robotPos.pos.y;
                //printf("depth : %d, x : %d, y : %d, badNewX : %d, badNewY : %d\n", head->depth+1, newLoc.pos.x, newLoc.pos.y, (translate(robotPos, possibilities[i])).pos.x, (translate(robotPos, possibilities[i])).pos.y);
            }
            newNode->depth = head->depth+1;
            newNode->numberChilds = head->numberChilds-1;
            newNode->totalValue = head->totalValue+newNode->value;
            newNode->min = *min;
            head->avails[i] = newNode;
            addAllWayToTree(newNode, newLoc, map, move, min, minStack, currentStack, numberOfMovement);
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
    if (node->choice == LOST_SIGNAL) {
        printf(" WE LOST CONTACT... HOUSTON WE HAVE A PROBLEM ! - STOPS HERE");
    }
    if (node->depth > 0) {
        printf(" -> %s ", getMoveAsString(node->choice));
    }
    printf("\n");
    for (int i = 0; i<node->numberChilds; i++) {
        printTreeRecur(node->avails[i], min);
    }
}