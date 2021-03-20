#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "neat.h"
//#include "morpion.h"
#include "snake.h"

//
void initGame(NeuralNetwork ** population, double * data, double * fitnessClassement ){

    for( int i = 0; i < TAILLE_POPULATION; i++){
        population[i] = malloc( sizeof(NeuralNetwork));
        initNeuralNetwork(population[i], NB_INPUT, NB_HIDDEN_LAYER, NB_NEURONS_HIDDEN, NB_NEURONS_OUTPUT);
        initWeigth(population[i]);
        data[i] = 0;
        fitnessClassement[i] = 0;
        population[i]->id = i;
        //printNetwork(population[i]);
    }
}

//
void afficherJeu(int resultat ){
    afficheGrille();
    switch (resultat) {
        case 0:
            printf(">haut\n" );
            break;
        case 1:
            printf(">Bas\n" );
            break;
        case 2:
            printf(">gauche\n" );
            break;
        case 3:
            printf(">droite\n" );
            break;
        default:
            break;
        }
}

//
void afficherInfo(NeuralNetwork ** population ){
    for( int i = 0; i < TAILLE_POPULATION; i++){
        printf("id: %d - score: %lf - fitness: %lf\n", population[i]->id, population[i]->rawScore, population[i]->fitness );
        //printf("fitness n %d : %lf\n",i,population[i]->fitness );
        //printf("id : %d \n",population[i]->id);
        //printNetwork(population[i]);
    }
}

void jump(int a){
    for( int i = 0; i < a; i++){
        printf("\n");
    }

}

//
void playBest( NeuralNetwork ** population ){
    NeuralNetwork * nn;
    nn = bestElement( population );

    Snake * snake ;

    int resultat = 4;
    Boolean end = FALSE;
    jump(10);
    printf("score : %lf\n", nn->rawScore );
    printf("pomme : %lf\n", nn->nbFruit );
    printf("fitness : %lf\n", nn->fitness );
    jump(10);


    // Init snake
    end = FALSE;
    initialiseGrille();
    snake = malloc(sizeof(Snake));
    initSnake(snake);
    //
    while (end == FALSE && snake->health != 0 ) {
        setInput(nn, getInput(snake, NB_INPUT));
        compute(nn);
        resultat = result(nn);

        //                      Affichage
        jump(10);
        printNetwork(nn);
        afficherData(nn);
        afficherJeu(resultat);
        printf(">\n");
        getchar();

        switch (resultat) {
            case 0:
                end = move(snake, -1, 0);
                break;
            case 1:
                end = move(snake, 1, 0);
                break;
            case 2:
                end = move(snake, 0, -1);
                break;
            case 3:
                end = move(snake, 0, 1);
                break;
            default:
                //break;
                //printf("fin du jeu\n" );
                printf("%d\n", resultat );
                exit(0);
                end = TRUE;
                break;
        }

    }

}

//
NeuralNetwork ** play( NeuralNetwork ** population , int printBest ){
    Snake * snake ;

    int resultat = 4;
    Boolean end = FALSE;

    for( int i = 0; i < TAILLE_POPULATION; i++){

        // Init snake
        end = FALSE;
        initialiseGrille();
        snake = malloc(sizeof(Snake));
        initSnake(snake);
        //
        while (end == FALSE && snake->health != 0) {
            setInput(population[i], getInput(snake, NB_INPUT));
            compute(population[i]);
            resultat = result(population[i]);

            //                      Affichage
            // jump(10);
            // printNetwork(population[i]);
            // afficherData(population[i]);
            // afficherJeu(resultat);
            // printf(">\n");
            // getchar();

            switch (resultat) {
                case 0:
                    end = move(snake, -1, 0);
                    break;
                case 1:
                    end = move(snake, 1, 0);
                    break;
                case 2:
                    end = move(snake, 0, -1);
                    break;
                case 3:
                    end = move(snake, 0, 1);
                    break;
                default:
                    //break;
                    //printf("fin du jeu\n" );
                    printf("%d\n", resultat );
                    exit(0);
                    end = TRUE;
                    break;
            }
        }
        setScore(population[i], getScore(snake), getFruit(snake));
        destroySnake(snake);
    }

    calculateFitness(population);


    //                                  Log
    writeLogScore(fileScore, population); // log score
    writeLogId(fileId, population);
    writeLogFruit(fileFruit, population);


    //                                  Affichage
    // printPopulaton(population);
    // afficherInfo( population);
    // printf(">\n");
    // getchar();

    if(printBest == 1)
        playBest(population);


    population = fuck(population);

    return population;
}

//
int main() {

    initGlobalVar();

    srand(time(NULL));
    // double sum = 0;
    // double r;
    // for(int i = 0; i<1000;i++){
    //     r = normalRandom()*0.05;
    //     sum += r;
    //     printf("%lf\n",r );
    // }
    // printf("sum : %lf\n", sum);
    //
    // exit(0);
    fileScore = openLog("score/score.csv");
    fileId = openLog("score/id.csv");
    fileFruit = openLog("score/fruit.csv");

    //Init nn
    NeuralNetwork ** population = malloc(TAILLE_POPULATION * sizeof(NeuralNetwork));
    double * data = malloc(TAILLE_POPULATION * sizeof(double)); //data
    double * fitnessClassement = malloc(TAILLE_POPULATION * sizeof(double)); //data

    initGame(population, data, fitnessClassement );

    for( int j = 0; j < 2001; j++){

        if(j%500 == 0)
            population = play(  population, 1 );
        else
            population = play(  population, 0 );

        if(j%10 == 0){
            printf("gen: %d\n", j );
        }


    }


    //destruction
    destroyPopulation(population);
    free(data);
    free(fitnessClassement);
    fclose(fileScore);
    fclose(fileId);
    fclose(fileFruit);
    return 0;
}



    //printf("--\n" );
    //getchar();
    //choice = getchar();
    /*Body * body = snake->head;
    printf("head");
    while (body) {
        printf("\nligne: %d\ncolonne: %d\n\n\n",body->ligne, body->colonne  );
        body = body->previous;
    }*/
