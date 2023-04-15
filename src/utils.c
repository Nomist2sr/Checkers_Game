#include "utils.h"
#include "checker.c"

//Add the pawns and kings(by default if no saves)
//BLACK ON TOP and WHITE ON BOTTOM
//return char[10][10]
void initChecker(char checker[10][10],char * saving){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            checker[i][j]=' ';
        }
    }
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
int * recurciveKing_checkPiece(char checker[10][10],int* kingPosition,int* targetPosition,int* foundPiece, int nbLoop){
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
                printf("Vous ne pouvez pas prendre plusieurs pieces\n");
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


//Function that add all the possible move of a piece
//posPiece is the actual position of the piece, in the case of a recursive use where the piece would move several times
//firstMove is the original position of the piece, and is the value to be returned regarding the piece position
void getForcedMoveFromPiece(char checker[10][10], next_move *all_next_move, char piece, int posPiece[2],int nbMoves, int* firstMove){
    //int end=0;
    int x=posPiece[0];
    int y=posPiece[1];

    if(piece=='O'){
        if(x-2>=0&&y+2<10){
            if((checker[x-1][y+1]=='@'||checker[x-1][y+1]=='B')&&checker[x-2][y+2]==' '){
                //getForcedMoveFromPiece(checker,piece,{x-2,y+2},nbMoves++,firstMove);
                AddNextMove(all_next_move, firstMove,(int[2]){x-2,y+2} ,nbMoves);
            }
        }
        if(x-2>=0&&y-2>=0){
            if((checker[x-1][y-1]=='@'||checker[x-1][y-1]=='B')&&checker[x-2][y-2]==' '){
                //getForcedMoveFromPiece(checker,piece,{x-2,y-2},nbMoves++);
                AddNextMove(all_next_move, firstMove,(int[2]){x-2,y-2} ,nbMoves);
            }
        }
    }
    if(piece=='@'){
        if(x+2<10&&y+2<10){
            if((checker[x+1][y+1]=='O'||checker[x+1][y+1]=='W')&&checker[x+2][y+2]==' '){
                //getForcedMoveFromPiece(checker,piece,{x+2,y+2},nbMoves++);
                AddNextMove(all_next_move, firstMove,(int[2]){x+2,y+2} ,nbMoves);
            }
        }
        if(x+2<10&&y-2>=0){
            if((checker[x+1][y-1]=='O'||checker[x+1][y-1]=='W')&&checker[x+2][y-2]==' '){
                //getForcedMoveFromPiece(checker,piece,{x+2,y-2},nbMoves++);
                AddNextMove(all_next_move, firstMove,(int[2]){x+2,y-2} ,nbMoves);
            }
        }
    }

    if(piece=='W'||piece=='B'){
        int defaultList[2] = {10,10};
        int checkPos[2] = {10,10};
        for(int i=1;i<10;i++){

            checkPos[0]=posPiece[0]+i;
            checkPos[1]=posPiece[1]+i;
            //Vers en bas a droite
            if(checkPos[0]>=0&&checkPos[0]<10&&checkPos[1]>=0&&checkPos[1]<10&&checker[checkPos[0]][checkPos[1]]==' '){
                int * resultRecusiveKing= recurciveKing_checkPiece(checker,posPiece,checkPos,defaultList, 0);
                if(resultRecusiveKing[0]>=0&&resultRecusiveKing[1]>=0&&resultRecusiveKing[0]<10&&resultRecusiveKing[1]<10){
                    AddNextMove(all_next_move, firstMove,checkPos ,nbMoves);
                }
            }
            //Vers en bas a gauche
            checkPos[1]=posPiece[1]-i;
            if(checkPos[0]>=0&&checkPos[0]<10&&checkPos[1]>=0&&checkPos[1]<10&&checker[checkPos[0]][checkPos[1]]==' '){
                int * resultRecusiveKing= recurciveKing_checkPiece(checker,posPiece,checkPos,defaultList, 0);
                if(resultRecusiveKing[0]>=0&&resultRecusiveKing[1]>=0&&resultRecusiveKing[0]<10&&resultRecusiveKing[1]<10){
                    AddNextMove(all_next_move, firstMove,checkPos ,nbMoves);
                }
            }
            //Vers en haut a gauche
            checkPos[0]=posPiece[0]-i;
            if(checkPos[0]>=0&&checkPos[0]<10&&checkPos[1]>=0&&checkPos[1]<10&&checker[checkPos[0]][checkPos[1]]==' '){
                int * resultRecusiveKing= recurciveKing_checkPiece(checker,posPiece,checkPos,defaultList, 0);
                if(resultRecusiveKing[0]>=0&&resultRecusiveKing[1]>=0&&resultRecusiveKing[0]<10&&resultRecusiveKing[1]<10){
                    AddNextMove(all_next_move, firstMove,checkPos ,nbMoves);
                }
            }
            //Vers en haut a droite
            checkPos[1]=posPiece[1]+i;
            if(checkPos[0]>=0&&checkPos[0]<10&&checkPos[1]>=0&&checkPos[1]<10&&checker[checkPos[0]][checkPos[1]]==' '){
                int * resultRecusiveKing= recurciveKing_checkPiece(checker,posPiece,checkPos,defaultList, 0);
                if(resultRecusiveKing[0]>=0&&resultRecusiveKing[1]>=0&&resultRecusiveKing[0]<10&&resultRecusiveKing[1]<10){
                    AddNextMove(all_next_move, firstMove,checkPos ,nbMoves);
                }
            }
        }
    }
}


next_move * getNextForcedMoves(char checker[10][10], char side){
    int returnList[2] = {10,10};
    next_move *all_next_move = malloc(sizeof(next_move));
    initStructureNextMove(all_next_move,(int[2]){-1,-1},(int[2]){-1,-1},0);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            returnList[0] = i;
            returnList[1] = j;
            if((checker[i][j] == '@' || checker[i][j] == 'B') && side == '@'){
                getForcedMoveFromPiece(checker,all_next_move,checker[i][j],returnList,0,returnList);
            }
            if((checker[i][j] == 'O' || checker[i][j] == 'W') && side == 'O'){
                getForcedMoveFromPiece(checker,all_next_move,checker[i][j],returnList,0,returnList);
            }
        }
    }
    next_move * result=deleteFirstMove(all_next_move);
    if(result==NULL){
        return NULL;
    }else{
        return result;
    }
}


int movePawn(char checker[10][10], int* oldPosition, int* newPosition){
    int x = oldPosition[0];
    int y = oldPosition[1];
    int newX = newPosition[0];
    int newY = newPosition[1];
    int *pieceToTransform;
    int defaultList[2] = {10,10};

    if ( checker[newX][newY] != ' '){
        printf("La coordonnee cible tombe sur un %c et non sur un espace vide\n\n",checker[newX][newY]);
        return (0);
    }
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
            if ((newY == y+1 || newY == y-1) && newX == x-1){
                checker[newX][newY] = checker[x][y];
                checker[x][y] = ' ';
            }
            else if ((newX == x+2 || newX == x-2) && (newY == y+2 || newY == y-2)){
                if(checker[(x+newX)/2][(y+newY)/2] =='@' || checker[(x+newX)/2][(y+newY)/2] == 'B'){
                    checker[(x+newX)/2][(y+newY)/2] = ' ';
                    checker[newX][newY] = checker[x][y];
                    checker[x][y] = ' ';
                }
                else {
                    printf("La case est trop loin et aucun pion adverse n'est sur le chemin\n\n");
                    return(0);
                }
            }
            else {
                printf("La coordonnee indiquee est invalide (trop loin ou pas en diagonale ou mauvais sens)\n\n");
                return(0);
            }

            //transform into a queen
            if(newX==0) checker[newX][newY]='W';

            return(1);
        }
        else{ // going backward - Black

            // If no direct diagonal piece -> go forward
            if ((newY == y+1 || newY == y-1) && newX == x+1){
                checker[newX][newY] = checker[x][y];
                checker[x][y] = ' ';
            }
            else if ((newX == x+2 || newX == x-2) && (newY == y+2 || newY == y-2)){
                if(checker[(x+newX)/2][(y+newY)/2] =='O' || checker[(x+newX)/2][(y+newY)/2] == 'W'){
                    checker[(x+newX)/2][(y+newY)/2] = ' ';
                    checker[newX][newY] = checker[x][y];
                    checker[x][y] = ' ';
                }
                else {
                    printf("La case est trop loin et aucun pion adverse n'est sur le chemin\n\n");
                    return(0);
                }
            }
            else {
                printf("La coordonnee indiquee est invalide (trop loin ou pas en diagonale ou mauvais sens)\n\n");
                return(0);
            }

            //transform into a queen
            if(newX==9){
               checker[newX][newY]='B';
            }
            return(1);
        }
    }
}

int chooseMove(char checker[10][10],char player){
    /*
    isMoveForced= getIfMoveForced(player)
    if(isMoveForced)movePawn(checker,...)
    else{
    */
    int isMoveLegal =- 1;

    next_move * allNextMoves=getNextForcedMoves(checker,player);
    printAllForcedMoves(allNextMoves);


    while(isMoveLegal != 1){
        isMoveLegal = -1;
        int playerCoord[2]={-1,-1};
        printf("Entrez la coordonnee horizontale de votre piece a jouer:\n");
        scanf("%d",&playerCoord[0]);
        printf("Entrez la coordonnee vericale de votre piece a jouer:\n");
        scanf("%d",&playerCoord[1]);

        //decalage
        playerCoord[0]=playerCoord[0]-1;
        playerCoord[1]=playerCoord[1]-1;

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
                printf("Vous n'avez pas choisi l'une de vos pieces\n\n");
            }else{
                int cibleCoord[2]={-1,-1};
                printf("Entrez la coordonnee horizontale de la position ciblee:\n");
                scanf("%d",&cibleCoord[0]);
                printf("Entrez la coordonnee vericale de la position ciblee:\n");
                scanf("%d",&cibleCoord[1]);

                //decalage
                cibleCoord[0]=cibleCoord[0]-1;
                cibleCoord[1]=cibleCoord[1]-1;

                if(cibleCoord[0]<0||cibleCoord[0]>9 || cibleCoord[1]<0 || cibleCoord[1]>9){
                    printf("L'une des coordonnees n'est pas sur le tableau, recommencez!\n\n");
                }else{
                    int isMoveInForced=getIfMoveIsLegalForced(allNextMoves,(int[2]){playerCoord[0],playerCoord[1]},(int[2]){cibleCoord[0],cibleCoord[1]});
                    if(isMoveInForced==0){
                        printf("Vous ne pouvez faire ce mouvement car vous avez des mouvements obligatoires\n\n");
                        printAllForcedMoves(allNextMoves);
                    }else{
                        isMoveLegal=movePawn(checker,playerCoord,cibleCoord);
                        if(isMoveLegal!=1){
                            printf("Le mouvement est incorrect\n\n");
                        }else{
                            deleteAllMoves(allNextMoves);
                        }
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


int countPieces(char checker[10][10],char side){
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

