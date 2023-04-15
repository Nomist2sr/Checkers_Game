#include "game.h" 


int nextMove(int tour, char checker[10][10]) {

    printf("===================================\ntour %d :\n", tour);
    printf("C'est au joueur blanc de jouer :\n");
    chooseMove(checker,'O');
    showChecker(checker);
    printf("C'est au joueur noir de jouer :\n");
    chooseMove(checker,'@');
    showChecker(checker); 

    printf("\nVoulez-vous enregistrer la partie actuelle ? o/n\n");
    int out = 1; 
    char answer;
    while (out){ 
        scanf("%c", &answer);
        printf("%c\n", answer);
        switch (answer){
        case 'o':
            printf("Enregistremment ...\n");
            // appel fonction enregistrement
            return (0);
            break;
        case 'n':
            return(1);
            break;
        default:
            printf("Vous devez entrer O ou N\n");
            break;
        }
    }
    return (1);
}

void initGame(){
    char checker[10][10];

    initChecker(checker, NULL);
    showChecker(checker);
    int stop = 2;
    int tour = 1;
    while(stop !=1 || stop != 0) {
        stop = nextMove(tour, checker);
        tour++;
        if(countPieces(checker,'O')==0){
            printf("\nLe joueur noir a gagne !!!\n");
            stop=1;
        }
        if(countPieces(checker,'@')==0){
            printf("\nLe joueur blanc a gagne !!!\n");
            stop=1;
        }
    }
    //printf("test je suis bien sortie :) ");
}



