#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "neat.h"
//#include "morpion.h"
#include "snake.h"


int main2() {

    srand(time(NULL));


    //Snake init
    Snake * snake ;
    int resultat = 4;
    Boolean end = FALSE;
    //

    //Init nn
    NeuralNetwork ** population = malloc(TAILLE_POPULATION * sizeof(NeuralNetwork));
    double * data = malloc(TAILLE_POPULATION * sizeof(double)); //data
    double * fitnessClassement = malloc(TAILLE_POPULATION * sizeof(double)); //data

    for( int i = 0; i < TAILLE_POPULATION; i++){
        population[i] = malloc( sizeof(NeuralNetwork));
        initNeuralNetwork(population[i], NB_INPUT, NB_HIDDEN_LAYER, NB_NEURONS_HIDDEN, NB_NEURONS_OUTPUT);
        initWeigth(population[i]);
        data[i] = 0;
        fitnessClassement[i] = 0;
        population[i]->id = i;
    }

    //data

    for( int j = 0; j < 4; j++){
        for( int i = 0; i < TAILLE_POPULATION; i++){

            // Init snake
            end = FALSE;
            initialiseGrille();
            snake = malloc(sizeof(Snake));
            initSnake(snake);
            //
            //printf("--------------------------------------------\nNeuralNetwork num: %d",i );
            while (end == FALSE) {

                afficheGrille();
                setInput(population[i], getInput(snake, NB_INPUT));
                compute(population[i]);
                resultat = result(population[i]);
                //printNetwork(population[i]);

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
                        printf("fin du jeu\n" );
                        end = TRUE;
                        break;
                }


            }
            setScore(population[i], getScore(snake));
            data[i] = getScore(snake);
            destroySnake(snake);
        }
        calculateFitness(population);

        /*
        for( int i = 0; i < TAILLE_POPULATION; i++){
            printNetwork(population[i]);
        }
        */
        //printf("\n\n\n\n%d\n",j );

        /*
        for( int i = 0; i < TAILLE_POPULATION; i++){
            //printNetwork(population[i]);
            fitnessClassement[i] = population[i]->fitness;

            printf("score n %d : %lf\n",i,data[i] );
            printf("fitness n %d : %lf\n",i,fitnessClassement[i] );
            printf("id : %d \n",population[i]->id);
            //printNetwork(population[i]);
        }
        */
        /*
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
        */


        population = fuck(population);


        //for( int i = 0; i < TAILLE_POPULATION; i++){
            //printNetwork(population[i]);
        //}
        //getchar();



    }
    /*
    for( int i = 0; i < TAILLE_POPULATION; i++){
        printNetwork(population[i]);
    }*/
/*
    for( int i = 0; i < TAILLE_POPULATION; i++){
        printf("score nn %d : %lf\n",i, (population[i])->score);

    }
*/
    destroyPopulation(population);
    free(data);
    free(fitnessClassement);

    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(/*int argc, char *argv[]*/) {

    initGlobalVar();

/*    if(argc < 2 ){
        printf("nb arg: %d\n", argc );
        printf("Veuillez mettre le nom du fichier de log\n");
        exit(1);
        printf("%s\n",argv[1] );
    }*/
    srand(time(NULL));

    FILE* fileScore = openLog("score/score.csv");
    FILE* fileId = openLog("score/id.csv");

    /*
    // création de la population
    NeuralNetwork ** population = malloc(TAILLE_POPULATION * sizeof(NeuralNetwork));
    for( int i = 0; i < TAILLE_POPULATION; i++){
        population[i] = malloc( sizeof(NeuralNetwork));
        initNeuralNetwork(population[i], NB_INPUT, NB_HIDDEN_LAYER, NB_NEURONS_HIDDEN, NB_NEURONS_OUTPUT);
        initWeigth(population[i]);
    }

    double gen = 0;
    while(gen != 100){
        for( int i = 0; i < TAILLE_POPULATION; i++){
        }
        gen+=1;


    }

    calculateFitness(population);
    destroyPopulation(population);
    return 0;*/
    /*
    NeuralNetwork nn;

    //nbInput, nbHiddenLayer, nbNeuronsHidden, nbNeuronsOutput
    //initNeuralNetwork(&nn, 10, 2, 9, 9);
        initWeigth(&nn);
    compute(&nn);
    printNetwork(&nn);
    unsigned long long resultat = result(&nn);
    printf("%llu\n", resultat );
*/

    //Snake init
    Snake * snake ;
    int resultat = 4;
    Boolean end = FALSE;
    //

    //Init nn
    NeuralNetwork ** population = malloc(TAILLE_POPULATION * sizeof(NeuralNetwork));
    double * data = malloc(TAILLE_POPULATION * sizeof(double)); //data
    double * fitnessClassement = malloc(TAILLE_POPULATION * sizeof(double)); //data

    for( int i = 0; i < TAILLE_POPULATION; i++){
        population[i] = malloc( sizeof(NeuralNetwork));
        initNeuralNetwork(population[i], NB_INPUT, NB_HIDDEN_LAYER, NB_NEURONS_HIDDEN, NB_NEURONS_OUTPUT);
        initWeigth(population[i]);
        data[i] = 0;
        fitnessClassement[i] = 0;
        population[i]->id = i;
        printNetwork(population[i]);
    }

    //data
    for(int k = 0; k < 1; k++){
        for( int j = 0; j < 1; j++){
            //printf("%d\n",j );
            for( int i = 0; i < TAILLE_POPULATION; i++){
                //population[i]

                // Init snake
                end = FALSE;
                initialiseGrille();
                snake = malloc(sizeof(Snake));
                initSnake(snake);
                //
                //printf("--------------------------------------------\nNeuralNetwork num: %d",i );
                while (end == FALSE) {

                    //afficheGrille();
                    setInput(population[i], getInput(snake, NB_INPUT));
                    compute(population[i]);
                    resultat = result(population[i]);
                    //printNetwork(population[i]);
                    /*
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
                    */
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
                            printf("fin du jeu\n" );
                            end = TRUE;
                            break;
                    }


                }
                setScore(population[i], getScore(snake));
                data[i] = getScore(snake);
                destroySnake(snake);
            }
            calculateFitness(population);


            for( int i = 0; i < TAILLE_POPULATION; i++){
                //printNetwork(population[i]);
            }

            //printf("\n\n\n\n%d\n",j );

            /*
            for( int i = 0; i < TAILLE_POPULATION; i++){
                //printNetwork(population[i]);
                fitnessClassement[i] = population[i]->fitness;

                printf("score n %d : %lf\n",i,data[i] );
                printf("fitness n %d : %lf\n",i,fitnessClassement[i] );
                printf("id : %d \n",population[i]->id);
                //printNetwork(population[i]);
            }
            */

            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );




            if(j != 49)
                population = fuck(population);


            for( int i = 0; i < TAILLE_POPULATION; i++){
                printNetwork(population[i]);
            }
            //getchar();

        }
        //writeLogScore(fileScore, population);
        //writeLogId(fileId, population);
        printf("%dk\n",k );
        population = fuck(population);
    }
    //printNetwork(nn);
/*
    for( int i = 0; i < TAILLE_POPULATION; i++){
        printf("score nn %d : %lf\n",i, (population[i])->score);

    }
*/
    destroyPopulation(population);
    free(data);
    free(fitnessClassement);
    fclose(fileScore);
    fclose(fileId);
    //free(file);
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
