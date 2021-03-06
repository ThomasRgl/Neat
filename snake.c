
#include <stdio.h>
#include <stdlib.h>
#include "snake.h"


/* grille du morpion valeurs possibles VIDE, ROND ou CROIX */


double * getInput( Snake * snake, int nbInput) {
    // double * inputList = malloc(nbInput * sizeof(double)) ;
    //
    // int ligneHead = snake->head->ligne;
    // int colonneHead = snake->head->colonne;
    //
    // int ligneFruit = snake->fruit->ligne;
    // int colonneFruit = snake->fruit->colonne;
    //
    // inputList[0] = ligneFruit - ligneHead;
    // inputList[1] = colonneFruit - colonneHead ;
    //
    // //case dispo haut
    // int index = 1;
    // while( (ligneHead - index)>=0 && grille[ligneHead - index][colonneHead] != SNAKE ){
    //     index+=1;
    // }
    // inputList[2] = index-1;
    //
    // //case dispo bas
    // index = 1;
    // while( (ligneHead + index) < NB_LIG && grille[ligneHead + index][colonneHead] != SNAKE ){
    //     index+=1;
    // }
    // inputList[3] =  index-1;
    //
    // //case dispo gauche
    // index = 1;
    // while( (colonneHead - index)>=0 && grille[ligneHead][colonneHead - index] != SNAKE ){
    //     index+=1;
    // }
    // inputList[4] = index-1;
    //
    // //case dispo droite
    // index = 1;
    // while( (colonneHead + index) < NB_COL && grille[ligneHead][colonneHead + index] != SNAKE ){
    //     index+=1;
    // }
    // inputList[5] =  index-1;
    //
    // return inputList;

    // input v2 : 8 input
    double * inputList = malloc(nbInput * sizeof(double)) ;

    int ligneHead = snake->head->ligne;
    int colonneHead = snake->head->colonne;

    inputList[0] = 0 ; //Danger haut
    inputList[1] = 0 ; //Danger bas
    inputList[2] = 0 ; //Danger droite
    inputList[3] = 0 ; //Danger gauche

    if( !(ligneHead-1 >= 0) || grille[ligneHead-1][colonneHead] == SNAKE  )
        inputList[0] = 1;

    if( !(ligneHead+1 < NB_LIG) || grille[ligneHead+1][colonneHead] == SNAKE  )
        inputList[1] = 1;

    if( !(colonneHead+1 < NB_COL) || grille[ligneHead][colonneHead+1] == SNAKE  )
        inputList[2] = 1;

    if( !(colonneHead-1 >= 0)  || grille[ligneHead][colonneHead-1] == SNAKE  )
        inputList[3] = 1;


    //
    int ligneFruit = snake->fruit->ligne;
    int colonneFruit = snake->fruit->colonne;

    inputList[4] = 0 ; //fruit haut
    inputList[5] = 0 ; //fruit bas
    inputList[6] = 0 ; //fruit droite
    inputList[7] = 0 ; //fruit gauche

    if(ligneFruit < ligneHead)
        inputList[4] = 1 ;
    else if (ligneFruit > ligneHead)
        inputList[5] = 1 ;

    if(colonneFruit > colonneHead)
        inputList[6] = 1 ;
    else if (colonneFruit < colonneHead)
        inputList[7] = 1 ;


    return inputList;

}
/*
 * Initiliase la grille du morpion a vide
 */
void initialiseGrille() {
  int i, j;
  for (i=0; i<NB_LIG; i++) {
    for (j=0; j<NB_COL; j++) {
      grille[i][j] = VIDE;
    }
  }
}

/*
  Affiche la grille du morpion
  _ indique case vide, O pion joueur 1 et X pion jour 2
 */
void afficheGrille() {
    int i, j;
    //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
    for (i=0; i<NB_LIG; i++) {
        for (j=0; j<NB_COL; j++) {
            switch (grille[i][j]) {
                case VIDE:
                    printf("_");
                    break;
                case SNAKE:
                    printf("O");
                    break;
                case FRUIT:
                    printf("X");
                    break;
            }
        }
        printf("\n"); /* fin de la ligne */
    }
}

//
void initSnake( Snake * snake){
    /*snake->head = NULL;
    snake->queue = NULL;*/
    snake->length = 0;
    snake->head = NULL;
    snake->queue = NULL;

    addHead( snake, 0, 0);
    snake->queue = snake->head;
    addHead( snake, 0, 1);

    snake->fruit = malloc(sizeof(Fruit));
    generateFruit(snake);

    snake->score = 1;
    snake->nbFruit = 0;
}

//
void generateFruit(Snake * snake){


    int ligne, colonne;
    do {
        ligne = rand()%NB_LIG;
        colonne = rand()%NB_COL;
    } while( grille[ligne][colonne] != VIDE );
    snake->fruit->ligne = ligne;
    snake->fruit->colonne = colonne;

    grille[ligne][colonne] = FRUIT;

}

//
void deleteQueue(Snake * snake){
    //return;
    Body * old = snake->queue;
    if(! old || !old->next)
        return;
    snake->queue = old->next;
    grille[old->ligne][old->colonne] = VIDE;

    old->next->previous = NULL;
    old->next = NULL;
    free(old);
    return;
}
//
void addHead(Snake * snake, int ligne, int colonne){
    //if( ligne <= NB_LIG)

    //printf("ligne : %d\n colonne : %d\n", ligne, colonne );
    //
    Body * new = malloc(sizeof(Body));

    if(!new)
        exit(EXIT_FAILURE);
    if(snake->head)
        snake->head->next = new;
    new->previous = snake->head;
    new->next = NULL;
    snake->head = new;

    //
    new->ligne = ligne;
    new->colonne = colonne;
    grille[ligne][colonne] = SNAKE;

    snake->length += 1;

    return ;
}

Boolean move(Snake * snake, int i, int j){

    if((snake->head->ligne + i >= NB_LIG) || (snake->head->colonne + j >= NB_COL) || (snake->head->ligne + i < 0 ) || (snake->head->colonne + j < 0) ){
        //printf("tu sorts du cadre\n" );
        return TRUE;}

    ValeurGrille val = grille[snake->head->ligne + i ][snake->head->colonne + j];

    if( val == SNAKE){;
        //printf("tu as touché le serpent\n" );
        return TRUE;}

    addHead( snake, snake->head->ligne + i, snake->head->colonne + j);

    //snake->score -= 1;

    if( val == FRUIT){
        generateFruit(snake);
        snake->score += 10;
        snake->nbFruit += 1;
    }


    if(val == VIDE)
        deleteQueue(snake);



    //printf("ccc\n" );
    return FALSE;
}

void destroySnake( Snake * snake ){
    Body * body = snake->head;
    //body->previous;

    Body * bodyTemp;

    while(body){
        bodyTemp = body->previous;
        free(body);
        body = bodyTemp;
    }

    free(snake->fruit);
    free(snake);
}

double getScore(Snake * snake){
    return snake->score;
}

double getFruit(Snake * snake){
    return snake->nbFruit;
}
/*
int main(int argc, char const *argv[]) {

    srand(time(NULL));

    Snake * snake = malloc(sizeof(Snake));

    initialiseGrille();
    initSnake(snake);
    char choice = 0;
    Boolean end = FALSE;

    while (end == FALSE) {
        afficheGrille();
        printf("\n\n>");
        scanf("%c",&choice );
        getchar();
        switch (choice) {
            case 'z':
                end = move(snake, -1, 0);
                break;
            case 's':
                end = move(snake, 1, 0);
                break;
            case 'q':
                end = move(snake, 0, -1);
                break;
            case 'd':
                end = move(snake, 0, 1);
                break;
            default:
                break;
                printf("fin du jeu\n" );
                end = TRUE;
                break;
        }


    }

    destroySnake(snake);
    return 0;

}
*/
