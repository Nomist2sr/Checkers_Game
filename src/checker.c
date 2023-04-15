#include "checker.h"

void initStructureNextMove(next_move *init_next_move,int* pieceToMove,int*positionToEnd,int nbPieceTaken)
{
    if (init_next_move != NULL)
    {
        init_next_move->pieceToMove[0]=pieceToMove[0];
        init_next_move->pieceToMove[1]=pieceToMove[1];
        init_next_move->positionToEnd[0]=positionToEnd[0];
        init_next_move->positionToEnd[1]=positionToEnd[1];
        init_next_move->_next = NULL;
        init_next_move->_previous = NULL;
        init_next_move->nbPieceTaken=nbPieceTaken;
    }
}


void AddNextMove(next_move *nextMove,int* pieceToMove,int*positionToEnd,int nbPieceTaken)
{
    nextMove=goToLastMove(nextMove);
    if (nextMove != NULL)
    {
        next_move *n_next_move = malloc(sizeof(next_move));
        initStructureNextMove(n_next_move,pieceToMove,positionToEnd,nbPieceTaken);
        if(n_next_move!=NULL){
            if (nextMove->_next == NULL)
            {
                n_next_move->_previous = nextMove;
                n_next_move->_next = NULL;
                nextMove->_next = n_next_move;
            }
        }
    }else{
        next_move *n_next_move = malloc(sizeof(next_move));
        initStructureNextMove(n_next_move,pieceToMove,positionToEnd,nbPieceTaken);
    }
}

int getIfMoveIsLegalForced(next_move*nextMove,int * start,int * move){
    if(nextMove==NULL)return 1;
    nextMove=goToFirstMove(nextMove);
    int isMoveLegal=0;
    while(nextMove!=NULL){
        if(nextMove->pieceToMove[0]==start[0]&&nextMove->pieceToMove[1]==start[1]){
            if(nextMove->positionToEnd[0]==move[0]&&nextMove->positionToEnd[1]==move[1]){
                isMoveLegal=1;
            }
        }
        nextMove= nextMove->_next;
    }
    return isMoveLegal;

}

void resetHeadMoves(next_move **nextMove){
    *nextMove=NULL;
}

next_move * deleteFirstMove(next_move *nextMove){//Used to remove the first element that is a placeholder
    nextMove=goToFirstMove(nextMove);
    next_move * next_move_next= NULL;
    if(nextMove->_next!=NULL){
        next_move_next=nextMove->_next;
    }
    free(nextMove);
    if(next_move_next!=NULL){
        next_move_next->_previous=NULL;
        nextMove=next_move_next;
        return nextMove;
    }else{
        resetHeadMoves(&nextMove);
        return NULL;
    }
}

void deleteAllMoves(next_move *nextMove)
{
    if(nextMove==NULL)return ;
    nextMove=goToFirstMove(nextMove);
    while(nextMove->_next!=NULL){
        next_move * next_move_next= nextMove->_next;
        free(nextMove);
        nextMove= next_move_next;
    }
    if(nextMove!=NULL){
        free(nextMove);
    }
    resetHeadMoves(&nextMove);
}



next_move * goToFirstMove(next_move *nextMove){
    while (nextMove->_previous != NULL)
    {
        nextMove = nextMove->_previous;
    }

    return(nextMove);
}

next_move * goToLastMove(next_move *nextMove){
    while (nextMove->_next != NULL)
    {
        nextMove = nextMove->_next;
    }

    return(nextMove);
}

int count(next_move *nextMove){
    int count=0;
    nextMove=goToFirstMove(nextMove);
    while(nextMove->_next!=NULL){
        count++;
    }
    return count;
}

void printAllForcedMoves(next_move *nextMove){
    if(nextMove==NULL)return;
    nextMove=goToFirstMove(nextMove);
    printf("Liste des mouvements obligatoires: \n");
    while(nextMove!=NULL){
        printf("| [%d:%d] vers [%d:%d] |",nextMove->pieceToMove[0]+1,nextMove->pieceToMove[1]+1,nextMove->positionToEnd[0]+1,nextMove->positionToEnd[1]+1);
        nextMove=nextMove->_next;
    }
    printf("\n");
}
