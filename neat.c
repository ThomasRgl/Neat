#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "neat.h"




//typedef struct Layer Layer;
//typedef struct NeatLayer NeatLayer;

//typedef struct NeuralNetwork NeuralNetwork;
//typedef struct NeatNeuralNetwork NeatNeuralNetwork;



//
/*
struct NeatNeuralNetwork
{
    double * input;
    Layer * firstLayer;
};*/

//
void initGlobalVar(){
    if( NB_HIDDEN_LAYER == 0 ){
        TOTAL_WEIGHT = ( NB_INPUT + 1 ) * NB_NEURONS_OUTPUT;
    }
    else{
        TOTAL_WEIGHT = ( NB_INPUT + 1 ) * NB_NEURONS_HIDDEN;
        for ( int i = 1; i < NB_NEURONS_HIDDEN; i ++)
            TOTAL_WEIGHT =  ( NB_NEURONS_HIDDEN + 1 ) * NB_NEURONS_HIDDEN;
        TOTAL_WEIGHT += ( NB_NEURONS_HIDDEN + 1 ) * NB_NEURONS_OUTPUT;

    }

    TAILLE_CROSSOVER_MAX = (TOTAL_WEIGHT * CROSSOVER_PERCENT ) / 100;

    printf("tailleCrossover : %d \n", TAILLE_CROSSOVER_MAX );
    printf("total_weight : %d \n", TOTAL_WEIGHT );

}

//
double sigmoid(double x){
    return 1 / (1 + exp(-x) );
}

//
double d_sigmoid(double x){
    return x * (1 - x);
}

//
double rand_gen() {
   // return a uniformly distributed random value
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}

//
double normalRandom() {
   // return a normally distributed random value
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}
/*
//
exemple() {
   double sigma = 82.0;
   double Mi = 40.0;
   for(int i=0;i<20;i++) {
      double x = normalRandom()*sigma+Mi;
      cout << " x = " << x << endl;
   }
}
*/

//
void allocatetab2D(int ***tab2D) {

    //
    *tab2D = (int **) malloc(5 * sizeof(int *));
    for( int i = 0; i != 5; i++) {
        (*tab2D)[i] = (int *) malloc(5 * sizeof(int *));
    }

    return;
}

unsigned long long result( NeuralNetwork * nn ){
    Layer * layer = NULL;
    layer = nn->lastLayer;

    //
    unsigned long long index;
    double max = 0;
    for(unsigned long long  i = 0; i < layer->length; i++){
        if(max <= layer->neurons[i]){
            max = layer->neurons[i];
            index = i;
        }
    }

    return index;

}

//
void compute(NeuralNetwork * nn){

    double s = 0.0;
    Layer * layer = NULL;
    layer = nn->firstLayer;
    layer = layer->nextLayer;


    while(layer){
        for (unsigned long long i = 0; i < layer->length ; i++) {
            s = (layer->bias)[i];
            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ ){
                s += (layer->w)[i][j] * layer->neurons[i];
            }
            (layer->neurons)[i] = sigmoid(s);
        }

        //
        layer = layer->nextLayer;
    }
}

//
void setInput(NeuralNetwork * nn, double * inputList){

    Layer * layer = NULL;
    layer = nn->firstLayer;

    //printf("%llu\n",layer->length );
    for( unsigned long long i = 0; i < layer->length; i++ )
        (layer->neurons)[i] = inputList[i];

    //Test
    //for( unsigned long long i = 0; i < layer->length; i++ )
    //    printf("input num %llu : %lf\n", i, (layer->neurons)[i]);

    free(inputList);
}

//
void printNetwork(NeuralNetwork * nn){

    Layer * layer = NULL;
    printf("---------------------\n\n     data : \n\n" );
    printf("score %lf\n", nn->score );
    printf("fitness %lf\n", nn->fitness );
    printf("id %d\n", nn->id );

    //
    printf("\n\n---------------------\n\n     Length : \n\n" );
    layer = (nn->firstLayer)->nextLayer;
    while(layer){
        printf("taille %llu\n", layer->length );
        layer = layer->nextLayer;
    }

    //
    printf("---------------------\n\n     Weight : \n\n" );
    layer = (nn->firstLayer)->nextLayer;
    int numLayer = 1;
    while(layer){
        numLayer += 1;
        for (unsigned long long i = 0; i < layer->length; i++) {
            printf("Layer %d to %d : Bias  to neurons %llu  = %lf\n", numLayer-1, numLayer,  i, (layer->bias)[i] );
            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ ){
                printf("Layer %d to %d : neurons %llu to neurons %llu  = %lf\n", numLayer-1, numLayer, j, i, (layer->w)[i][j] );
                //printf("Layer %d to %d : neurons %llu to neurons %llu  = %lf\n", numLayer-1, numLayer, j, i, (layer->w)[i][j] );

                //printf("%lf\n", (layer->w)[i][j]  );
            }
        }
        printf("\n");
        layer = layer->nextLayer;
    }

    //
    printf("---------------------\n\n     Neurons : \n\n" );
    layer = (nn->firstLayer);
    numLayer = 0;
    while(layer){
        numLayer += 1;
        for (unsigned long long i = 0; i < layer->length; i++) {
            printf("Layer %d , neurons %llu : %lf\n", numLayer, i, (layer->neurons)[i] );
        }
        printf("\n");
        layer = layer->nextLayer;
    }

    return;
}

//
void printPopulaton(NeuralNetwork ** population){
    for( int i = 0; i < TAILLE_POPULATION; i++){
        printNetwork(population[i]);
    }
}

//
void initWeigth(NeuralNetwork * nn) {

    //
    Layer * layer = NULL;
    layer = nn->firstLayer;
    layer = layer->nextLayer;
    //
    while(layer){
        for (unsigned long long i = 0; i < layer->length ; i++) {
            (layer->bias)[i] = (double)rand() / (double)RAND_MAX;
            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ )
                (layer->w)[i][j] = (double)rand() / (double)RAND_MAX;
        }
        layer = layer->nextLayer;
    }
}

//
void initLayer(NeuralNetwork * nn, unsigned long long length ){

    // construction of the previous and next layer
    Layer * new = malloc(sizeof(Layer));
    if(!new) exit(EXIT_FAILURE);
    new->previousLayer = nn->lastLayer;
    new->nextLayer = NULL;
    if(nn->lastLayer) nn->lastLayer->nextLayer = new;
    else nn->firstLayer = new;
    nn->lastLayer = new;

    //
    new->length = length;

    new->neurons = malloc(new->length * sizeof(double));
    for( unsigned long long i = 0; i < new->length; i++) {
        new->neurons[i] = 0;
        }

    //
    if(! new->previousLayer)
        return;

    unsigned long long previousLayerLength = new->previousLayer->length;
    //else new->previousLayerLength = nn->nbInput;

    new->bias = malloc(new->length * sizeof(double));
    for( unsigned long long i = 0; i < new->length; i++) {
        new->bias[i] = 0;
        }

    new->w = (double **) malloc(new->length * sizeof(double *));
    for( unsigned long long i = 0; i < new->length; i++) {
        new->w[i] = (double *) malloc(previousLayerLength * sizeof(double *));
        for( unsigned long long j = 0; j < previousLayerLength; j++) {
            new->w[i][j] = 0;
            }
        }

    return ;
}

//
void initNeuralNetwork(NeuralNetwork * nn, unsigned long long nbInput, unsigned long long nbHiddenLayer, unsigned long long nbNeuronsHidden, unsigned long long nbNeuronsOutput ){

    //
    nn->firstLayer = NULL;
    nn->lastLayer = NULL;

    //
    initLayer(nn, nbInput );

    while (nbHiddenLayer > 0) {
        nbHiddenLayer -= 1;
        initLayer(nn, nbNeuronsHidden );
    }

    initLayer(nn, nbNeuronsOutput );

    nn->score = 1;
    nn->fitness = 1;
    //
    return;
}

//
NeuralNetwork ** fuck(NeuralNetwork ** population){

    NeuralNetwork ** newPopulation = malloc(TAILLE_POPULATION * sizeof(NeuralNetwork));

    NeuralNetwork * a;
    NeuralNetwork * b;

    for( int i = 0; i < TAILLE_POPULATION; i++){

        a = pickOne(population);
        b = pickOne(population);
        newPopulation[i] = crossover(a, b);
        mutate(newPopulation[i]);
        //newPopulation[i] = malloc( sizeof(NeuralNetwork));
        //newPopulation[i] = malloc( sizeof(NeuralNetwork));
        //newPopulation[i] = pickOne(population);

    }
    destroyPopulation(population);
    return newPopulation;
}
/*
//
NeuralNetwork * pickOne(NeuralNetwork ** population){

    int index = 0;
    double r = (double) rand()/ (double) RAND_MAX;
    while ( r > 0) {
        r = r - (population[index])->fitness;

        index += 1;
    }

    index -= 1;
    //printf("the choosed is : %lf\n", (population[index])->fitness);
    NeuralNetwork * nn = malloc(sizeof(NeuralNetwork));
    copy( nn, population[index] );
    mutate(nn);
    nn->id = population[index]->id;
    return nn;

}*/
//
NeuralNetwork * pickOne(NeuralNetwork ** population){

    int index = 0;
    double r = (double) rand()/ (double) RAND_MAX;
    while ( r > 0) {
        r = r - (population[index])->fitness;

        index += 1;
    }

    index -= 1;
    return population[index] ;
}
//
NeuralNetwork * crossover(NeuralNetwork * a, NeuralNetwork * b){

    int remainingToLocation = ((double) rand()/ (double) RAND_MAX )*(TOTAL_WEIGHT-TAILLE_CROSSOVER_MAX);
    int crossoverRemaining = TAILLE_CROSSOVER_MAX;

    NeuralNetwork * nn = malloc( sizeof(NeuralNetwork) );

    if(! nn) exit(EXIT_FAILURE);

    initNeuralNetwork(nn, NB_INPUT, NB_HIDDEN_LAYER, NB_NEURONS_HIDDEN, NB_NEURONS_OUTPUT);

    Layer * layerA = a->firstLayer->nextLayer;
    Layer * layerB = b->firstLayer->nextLayer;
    Layer * layer = nn->firstLayer->nextLayer;

    while(layer){
        for (unsigned long long i = 0; i < layer->length ; i++) {
            if( crossoverRemaining == 0 || remainingToLocation != 0){
                (layer->bias)[i] = (layerA->bias)[i];
                remainingToLocation -= 1;
            }
            else {
                (layer->bias)[i] = (layerB->bias)[i];
                crossoverRemaining -= 1;
            }

            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ ){

                if( crossoverRemaining == 0 || remainingToLocation != 0){
                    (layer->w)[i][j] = (layerA->w)[i][j];
                    remainingToLocation -= 1;
                }
                else {
                    (layer->w)[i][j] = (layerB->w)[i][j];
                    crossoverRemaining -= 1;
                }
            }
        }
        layer = layer->nextLayer;
        layerA = layerA->nextLayer;
        layerB = layerB->nextLayer;

    }
    nn->id = a->id;
    return nn;
}

//
void copy( NeuralNetwork * newNn, NeuralNetwork * nn ){

    //NeuralNetwork * newNn = malloc( sizeof(NeuralNetwork) );

    if(! newNn) exit(EXIT_FAILURE);

    initNeuralNetwork(newNn, NB_INPUT, NB_HIDDEN_LAYER, NB_NEURONS_HIDDEN, NB_NEURONS_OUTPUT);
    //printf("ccc\n" );
    //printNetwork(newNn);
    //printf("ccc\n" );

    //
    Layer * layer = NULL;
    layer = nn->firstLayer;//ERROR SEGFAULT
    layer = layer->nextLayer;

    //
    Layer * newlayer = NULL;
    newlayer = newNn->firstLayer;
    newlayer = newlayer->nextLayer;

    //double nul;
    //
    while(layer){
        for (unsigned long long i = 0; i < layer->length ; i++) {
            (newlayer->bias)[i] = (layer->bias)[i];
            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ ){
                (newlayer->w)[i][j] = (layer->w)[i][j];
            }
        }
        layer = layer->nextLayer;
        newlayer = newlayer->nextLayer;
    }

    //printNetwork(nn);
    //printf("aaa\n" );
    //printNetwork(newNn);
    //printf("bbb\n" );
    //return newNn;


}

void calculateFitness(NeuralNetwork ** population){
    double sum = 0;
    for( int i = 0; i < TAILLE_POPULATION; i++){
        sum +=(population[i])->score;
    }

    for( int i = 0; i < TAILLE_POPULATION; i++){
        (population[i])->fitness = ((population[i])->score ) / sum ;
    }

}

//
void mutate( NeuralNetwork * nn ){


    Layer * layer = NULL;
    layer = nn->firstLayer;
    //printNetwork(nn);

    layer = layer->nextLayer;
    //
    while(layer){
        for (unsigned long long i = 0; i < layer->length ; i++) {
            /*
            if( MUTATION_RATE > (double) rand()/RAND_MAX){ (layer->bias)[i] += normalRandom()*0.2;}

            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ ){
                if( MUTATION_RATE > (double) rand()/RAND_MAX){ (layer->w)[i][j] += normalRandom()*0.2;}
            }*/

            if( MUTATION_RATE > (double) rand()/RAND_MAX){ (layer->bias)[i] = (double) rand()/RAND_MAX;}

            for (unsigned long long j = 0; j < layer->previousLayer->length; j++ ){
                if( MUTATION_RATE > (double) rand()/RAND_MAX){ (layer->w)[i][j] = (double) rand()/RAND_MAX;}
            }
        }
        layer = layer->nextLayer;
    }

    return;
}

void setScore(NeuralNetwork * nn, double score){
    //nn->score = score;
    nn->score = exp(score);
    nn->rawScore = score;
    return;
}

void destroyPopulation( NeuralNetwork ** population ){
    for( int i = 0; i < TAILLE_POPULATION; i++){
        destroyNetwork( population[i]);
    }
    free(population);
    return;
}

void destroyNetwork(NeuralNetwork * nn){


    Layer * layer = NULL;
    layer = nn->lastLayer;

    Layer * previousLayer = NULL;


    while(layer){
        previousLayer = layer->previousLayer;
        destroyLayer(layer);
        layer = previousLayer;
    }
    free(nn);

    return;
}

void destroyLayer(Layer * layer){


    free(layer->neurons);


    if(layer->previousLayer){
        free(layer->bias);
        for( unsigned long long i = 0; i < layer->length; i++) {
            free(layer->w[i]);
        }
        free(layer->w);
    }


    free(layer);
    return ;
}

FILE* openLog( char *fileName ){
    FILE* file = NULL ;
    file = fopen(fileName, "r");

    if( file != NULL){
        fseek(file, 0, SEEK_END);
        //printf("%ld\n", ftell(file) );

        if( ftell(file) != 0 ){
            printf("le fichier n'est pas vide !\n" );
            fclose( file );
            exit(1);
        }
        fclose( file );
    }
    file = fopen( fileName, "w");
    return file;
}

void writeLogScore ( FILE* file,  NeuralNetwork ** population ){

    for( int i = 0; i < TAILLE_POPULATION; i++){

        fprintf( file, "%lf,",population[i]->rawScore);
        //fprintf( file, "%lf,",population[i]->score);
        //fprintf( file, "%lf,",population[i]->fitness);
    }
    fputc('\n', file);
}

void writeLogId ( FILE* file,  NeuralNetwork ** population ){

    for( int i = 0; i < TAILLE_POPULATION; i++){

        fprintf( file, "%d,",population[i]->id);
    }
    fputc('\n', file);
}

void closeLog( FILE* file){
    fclose( file );
}
