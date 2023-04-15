#ifndef UNTITLED_CHECKER_H
#define UNTITLED_CHECKER_H

// SYSTEME INCLUDE(S)
#include "stdlib.h"
#include "stdio.h"

// STRUCTURE(S)
typedef struct next_move {
    int pieceToMove[2];
    int positionToEnd[2];
    int nbPieceTaken;
    struct next_move *_next;
    struct next_move *_previous;
} next_move;

// LOCAL INCLUDE(S)
void initStructureNextMove(next_move *init_next_move,int* pieceToMove,int*positionToEnd,int nbPieceTaken);

void AddNextMove(next_move *nextMove,int* pieceToMove,int*positionToEnd,int nbPieceTaken);

int getIfMoveIsLegalForced(next_move*nextMove,int * start,int * move);

next_move * deleteFirstMove(next_move *nextMove);

void deleteAllMoves(next_move *nextMove);

next_move *goToFirstMove(next_move *nextMove);

next_move *goToLastMove(next_move *nextMove);

int count(next_move *nextMove);

void printAllForcedMoves(next_move *nextMove);


// PROTOTYPE(S)

#endif // UNTITLED_CHECKER_H