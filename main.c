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

//
NeuralNetwork ** play( NeuralNetwork ** population ){
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
        while (end == FALSE) {
            setInput(population[i], getInput(snake, NB_INPUT));
            compute(population[i]);
            resultat = result(population[i]);
            //afficherJeu(resultat);

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
                    break;
                    //printf("fin du jeu\n" );
                    end = TRUE;
                    break;
            }
        }
        setScore(population[i], getScore(snake));
        destroySnake(snake);
    }

    calculateFitness(population);

    //printPopulaton(population);
    afficherInfo( population);
    printf(">\n");
    getchar();
    population = fuck(population);

    return population;
    //printPopulaton(population);
}

//
int main() {

    initGlobalVar();

    srand(time(NULL));

    FILE* fileScore = openLog("score/score.csv");
    FILE* fileId = openLog("score/id.csv");

    //Init nn
    NeuralNetwork ** population = malloc(TAILLE_POPULATION * sizeof(NeuralNetwork));
    double * data = malloc(TAILLE_POPULATION * sizeof(double)); //data
    double * fitnessClassement = malloc(TAILLE_POPULATION * sizeof(double)); //data

    initGame(population, data, fitnessClassement );

    for( int j = 0; j < 1000; j++){
        population = play(  population );
        //writeLogScore(fileScore, population);
        //writeLogId(fileId, population);
    }


    //destruction
    destroyPopulation(population);
    free(data);
    free(fitnessClassement);
    fclose(fileScore);
    fclose(fileId);
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
