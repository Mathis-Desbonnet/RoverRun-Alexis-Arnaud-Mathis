//
// Created by flasque on 19/10/2024.
//

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include "moves.h"

/**
 * @brief Structure for the stack of integers
 */
typedef struct s_stack
{
    int *values;
    int size;
    int nbElts;
} t_stack;

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int);

/**
 * @brief Function to push a value in the stack
 * @param pointer to the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *, int);

/**
 * @brief Function to pop a value from the stack
 * @param : pointer to the stack
 * @return the value popped
 */
int pop(t_stack *);

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
int top(t_stack);

/**
 * @brief Function to display the stack
 * @param stack : the stack
 */
void printStack(t_stack);

/**
 * @brief Function to copy the stack to another one
 * @param src : the source stack
 * @param dest : the destination stack
 */
void copyStack(t_stack src, t_stack* dest);

#endif //STACK_H
