//
// Created by flasque on 19/10/2024.
//

#ifndef MOVES_H
#define MOVES_H

#include "loc.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Array of strings for the possible moves of the robot
 */
static char _moves[9][13] = {"F 10m", "F 20m", "F 30m", "B 10m", "T left", "T right", "U-turn", "NO MOVE", "LOST SIGNAL"};

/**
 * @brief Enum for the possible moves of the robot
 */

typedef enum e_move
{
    F_10, // Forward 10 m
    F_20, // Forward 20 m
    F_30, // Forward 30 m
    B_10, // Backward 10 m
    T_LEFT, // Turn left (+90°)
    T_RIGHT, // Turn right (-90°)
    U_TURN,
    NO_MOVE,
    LOST_SIGNAL
} t_move;

t_move generateMove(int moveProba[7]);

/**
 * @brief function to get a t_move as a string
 * @param move : the move to convert
 * @return the string corresponding to the move
 */
char *getMoveAsString(t_move );

/**
 * @brief function to update the localisation of the robot according to a move
 * @param loc : the localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation move(t_localisation, t_move);

/**
 * @brief wrapper function to update a single location
 * @param p_loc : the pointer to the localisation of the robot
 * @param move : the move to do
 * @return none
 */
void updateLocalisation(t_localisation *, t_move);

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/**
 * @brief Create a new array of possibilities withou the current one
 * @param possibilities : the current array of possibilities
 * @param currentValueIndex : the position of the current move in the array of possibilities
 * @param numberPossibilities : size of current possibilities array
 * @return a new array of possibilities
 */
t_move* createTabWithoutCurrentValue(t_move* , int , int );

#endif //MOVES_H
