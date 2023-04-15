#ifndef UTILS_H_
#define UTILS_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>
// STRUCTURE(S)

// LOCAL INCLUDE(S)
#include "checker.h"

// PROTOTYPE(S)
void initChecker(char checker[10][10], char * saving);
int* recurciveKing_checkPiece(char checker[10][10],int* kingPosition,int* targetPosition,int* foundPiece, int nbLoop);
int movePawn(char checker[10][10], int* oldPosition, int* newPosition);
int chooseMove(char checker[10][10],char player);

void showChecker(char checker[10][10]);
int countPieces(char checker[10][10],char side);
void getForcedMoveFromPiece(char checker[10][10], next_move *all_next_move, char piece, int posPiece[2],int nbMoves, int* firstMove);
next_move * getNextForcedMoves(char checker[10][10], char side);


#endif /* !UTILS_H_ */