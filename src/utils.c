#include "utils.h"

//Add the pawns and kings(by default if no saves)
//BLACK ON TOP and WHITE ON BOTTOM
//return char[10][10]
void initChecker(char checker[10][10], char * saving){
    if(saving==NULL){       //If no saves is given

        for(int i=0;i<4;i++){
            for(int j=(i+1)%2;j<10;j+=2){
                checker[i][j] = '@';
            }
        }
        for(int i=6;i<10;i++){
            for(int j=(i+1)%2;j<10;j+=2){
                checker[i][j] = 'O';
            }
        }
    }
}

/*
Recurcive fonction : check and mesure the lenght beetween a hypothetic PAWN in the wy of the KING
@INPUT : foundPiece->[10,10] by default
nbLoop=0 by default

returns:
[x,y] return the piece to transform
[-1,-1] multiple pieces were found, error
[10,10] no piece found
return int[2]
*/
int * recurciveKing_checkPiece(char** checker,int* kingPosition,int* targetPosition,int* foundPiece, int nbLoop){
    int dirX;
    int dirY;
    nbLoop++;       //Incremente nbLoop

    // Diagonal direction
    if(kingPosition[0] > targetPosition[0]){dirX = -1;} else{dirX = 1;}
    if(kingPosition[1] > targetPosition[1]){dirY = -1;} else{dirY = 1;}

    // White player
    if(checker[kingPosition[0]][kingPosition[1]]=='W'){
        //If meet a piece of opposing color
        if (checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == 'B'||
            checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == '@'){
            if(foundPiece[0] == 10 && foundPiece[1] == 10){
                foundPiece[0] = kingPosition[0] + (nbLoop*dirX);
                foundPiece[1] = kingPosition[1] + (nbLoop*dirY);
            }
            else{
                printf("Vous ne pouvez pas prendre plusieurs pieces");
                return (NULL);
            }
            //If meet a piece of same color
        }else if (checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == 'W'||
                  checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == 'O'){
            printf("Vous ne pouvez pas vous deplacer sur ou par dessus un pion allie");
            return (NULL);
        }
    }

    // Black payer
    if(checker[kingPosition[0]][kingPosition[1]]=='B'){
        //If meet a piece of opposing color
        if (checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == 'W' ||
            checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == 'O'){
            if(foundPiece[0] == 10 && foundPiece[1] == 10){
                foundPiece[0] = kingPosition[0] + (nbLoop*dirX);
                foundPiece[1] = kingPosition[1] + (nbLoop*dirY);
            }
            else{
                printf("Vous ne pouvez pas prendre plusieurs pieces");
                return (NULL);
            }
            //If meet a piece of same color
        }else if (checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == 'B' ||
                  checker[kingPosition[0] + (nbLoop*dirX)][kingPosition[1] + (nbLoop*dirY)] == '@'){
            printf("Vous ne pouvez pas vous deplacer sur ou par dessus un pion allie");
            return (NULL);
        }
    }

    if(targetPosition[0] == kingPosition[0] + (nbLoop*dirX)){
        return foundPiece;
    }else{
        return recurciveKing_checkPiece(checker,kingPosition,targetPosition,foundPiece,nbLoop);
    }
}


int movePawn(char** checker, int* oldPosition, int* newPosition){
    int x = oldPosition[0];
    int y = oldPosition[1];
    int newX = newPosition[0];
    int newY = newPosition[1];
    int *pieceToTransform;
    int defaultList[2] = {10,10};

    if ( checker[newX][newY] != ' ') return (0);
    if ( checker[x][y] == 'B' || checker[x][y] == 'W' ){
        // you tring to move the KING
        //verify if we move in diagonal
        if (abs(x-newX) != abs(y-newY)) return(0);
        pieceToTransform = recurciveKing_checkPiece(checker, oldPosition, newPosition, defaultList, 0);
        if(pieceToTransform==NULL) return(0);

        if(pieceToTransform[0]<10 && pieceToTransform[0]>=0){
            checker[pieceToTransform[0]][pieceToTransform[1]] = ' ';
        }

        checker[newX][newY] = checker[x][y];
        checker[x][y] = ' ';
        return(1);
    }
    else{
        if (checker[x][y] == 'O'){ // going forward - White

            // If no direct diagonal piece -> go forward
            if ((newX == x+1 || newX == x-1) && newY == y+1){
                checker[newX][newY] = checker[x][y];
                checker[x][y] = ' ';
            }
            else if ((newX == x+2 || newX == x-2) && (newY == y+2 || newY == y-2)){
                if(checker[(x+newX)/2][(y+newX)/2] =='@' || checker[(x+newX)/2][(y+newX)/2] == 'B'){
                    checker[(x+newX)/2][(y+newX)/2] = ' ';
                    checker[newX][newY] = checker[x][y];
                    checker[x][y] = ' ';
                }
                else return(0);
            }
            else return(0);

            //transform into a queen
            if(newY==9) checker[newX][newY]='W';

            return(1);
        }
        else{ // going backward - Black

            // If no direct diagonal piece -> go forward
            if ((newX == x+1 || newX == x-1) && newY == y-1){
                checker[newX][newY] = checker[x][y];
                checker[x][y] = ' ';
            }
            else if ((newX == x+2 || newX == x-2) && (newY == y+2 || newY == y-2)){
                if(checker[(x+newX)/2][(y+newX)/2] =='O' || checker[(x+newX)/2][(y+newX)/2] == 'W'){
                    checker[(x+newX)/2][(y+newX)/2] = ' ';
                    checker[newX][newY] = checker[x][y];
                    checker[x][y] = ' ';
                }
                else return(0);
            }
            else return(0);

            //transform into a queen
            if(newY==0){
               checker[newX][newY]='B';
            }
            return(1);
        }
    }
}

int chooseMove(char** checker,char player){
    /*
    isMoveForced= getIfMoveForced(player)
    if(isMoveForced)movePawn(checker,...)
    else{
    */
    int isMoveLegal =- 1;

    while(isMoveLegal != 1){
        int playerCoord[2]={-1,-1};
        printf("Entrez la coordonnee horizontale de votre piece a jouer:\n");
        scanf("%d",&playerCoord[0]);
        printf("Entrez la coordonnee vericale de votre piece a jouer:\n");
        scanf("%d",&playerCoord[1]);
        if(playerCoord[0]<0 || playerCoord[0]>9 || playerCoord[1]<0 || playerCoord[1]>9){
            printf("L'une des coordonnees n'est pas sur le tableau, recommencez!\n\n");
        }else{
            if(checker[playerCoord[0]][playerCoord[1]] == ' '){
                isMoveLegal = 0;
            }if((checker[playerCoord[0]][playerCoord[1]] == 'O' || checker[playerCoord[0]][playerCoord[1]] == 'W') && player == '@'){
                isMoveLegal = 0;
            }
            if((checker[playerCoord[0]][playerCoord[1]] == '@' || checker[playerCoord[0]][playerCoord[1]] == 'B') && player == 'O'){
                isMoveLegal = 0;
            }
            if(isMoveLegal == 0){
                printf("Vous n'avez pas choisi l'une de vos pieces");
            }else{
                int cibleCoord[2]={-1,-1};
                printf("Entrez la coordonnee horizontale de :\n");
                scanf("%d",&cibleCoord[0]);
                printf("Entrez la coordonnee vericale de :\n");
                scanf("%d",&cibleCoord[1]);
                if(cibleCoord[0]<0||cibleCoord[0]>9 || cibleCoord[1]<0 || cibleCoord[1]>9){
                    printf("L'une des coordonnees n'est pas sur le tableau, recommencez!\n\n");
                }else{
                    isMoveLegal=movePawn(checker,playerCoord,cibleCoord);
                    if(isMoveLegal){
                        printf("Le mouvement est incorrect\n\n");
                    }
                }
            }
        }
    }
    return isMoveLegal;
}


void showChecker(char checker[10][10]){
    printf("    1   2   3   4   5   6   7   8   9   10\n");
    printf("  +---+---+---+---+---+---+---+---+---+---+\n");
    for(int i=0;i<10;i++){
        if(i<9){printf("%d ",i+1);} else{printf("%d",i+1);}
        for(int j=0;j<10;j++){
            printf("| %c ",checker[i][j]);
        }
        printf("|\n");
        printf("  +---+---+---+---+---+---+---+---+---+---+\n");
    }
}


int countPieces(char** checker,char side){
    if(side == '@' || side == 'B'){
        side = '@';
    }
    if(side == 'O' || side == 'W'){
        side = 'O';
    }
    int count = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if((checker[i][j] == '@' || checker[i][j] == 'B') && side == '@'){
                count++;
            }
            if((checker[i][j] == 'O' || checker[i][j] == 'W') && side == 'O'){
                count++;
            }
        }
    }
    return count;
}