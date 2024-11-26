//
// Created by Mathi on 10/25/2024.
//

#include "Node.h"

Node* createNode(int valueRobotPos, t_move* possibilities, int choice, int moveProba[7]) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->depth = 0;
    newNode->numberChilds = 9;
    newNode->value = valueRobotPos;
    newNode->totalValue = 0;
    newNode->avails = (Node**) calloc(sizeof(Node*), 9);
    if (possibilities == NULL) {
        for (int i = 0; i<newNode->numberChilds; i++) {
            newNode->possibilities[i] = generateMove(moveProba);
        }
    } else {
        for (int i = 0; i<newNode->numberChilds; i++) {
            newNode->possibilities[i] = possibilities[i];
        }
    }
    newNode->choice = choice;
    return newNode;
}