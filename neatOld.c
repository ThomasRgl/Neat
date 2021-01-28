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
double sigmoid(double x){
    return 1 / (1 + exp(-x) );
}

//
double d_sigmoid(double x){
    return x * (1 - x);
}

//
void allocatetab2D(int ***tab2D) {

    //
    *tab2D = (int **) malloc(5 * sizeof(int *));
    for( int i = 0; i != 5; i++) {
        (*tab2D)[i] = (int *) malloc(5 * sizeof(int *));
    }

    return;
}

//
void compute(NeuralNetwork * nn){

    double s = 0.0;

    layer = nn->firstLayer;
    while(layer){
        for (unsigned long long i = 1; i <= layer->length - 1; i++) {
            s = layer->w[i][0];
            for (unsigned long long j = 1; j < layer->previousLayerLength; j++ ){
                s += layer->w[i][j] * layer->neurons[i];
            }
        }

        //
        layer = layer->nextLayer;
    }

    // For each entry
    for(unsigned long long j = 1;  j <= n; j++)
        {
        //Building l1
        for(unsigned long long k = 1;  k <= n2; k++)
            {
            s = 0.0;
            //FMA
            for (unsigned long long l = 1; l <= n1; l++)
                s += I[j][l] * w1[l][k];
            //Update neuron value
            l1[j][k] = sigmoid(s);
            }
        }
}

//
void setInput(NeuralNetwork * nn, double * inputList){
    printf("%llu\n",nn->nbInput );
    for( unsigned long long i = 1; i < nn->nbInput - 1; i++ )
        (nn->input)[i] = inputList[i-1];

    //Test
    for( unsigned long long i = 1; i <= nn->nbInput - 1; i++ )
        printf("input num %llu : %lf\n", i, (nn->input)[i] );
}

//
void printNetwork(NeuralNetwork * nn){

    Layer * layer = NULL;

    //
    printf("\n\n---------------------\n\n     Length : \n\n" );
    layer = (*nn).firstLayer;
    while(layer){
        printf("taille %llu\n", layer->length );
        layer = layer->nextLayer;
    }

    //
    printf("---------------------\n\n     Weight : \n\n" );
    layer = (*nn).firstLayer;
    int numLayer = 1;
    while(layer){
        numLayer += 1;
        for (unsigned long long i = 1; i <= layer->length - 1; i++) {
            for (unsigned long long j = 0; j < layer->previousLayerLength; j++ ){
                printf("Layer %d to %d : neurons %llu to neurons %llu  = %lf\n", numLayer-1, numLayer, j, i, (layer->w)[i][j] );
            }
        }
        printf("\n");
        layer = layer->nextLayer;
    }

    return;
}

//
void initWeigth(NeuralNetwork * nn) {
    //
    srand(time(NULL));
    Layer * layer = NULL;
    layer = (*nn).firstLayer;

    //
    while(layer){
        for (unsigned long long i = 1; i <= layer->length - 1; i++) {
            for (unsigned long long j = 0; j < layer->previousLayerLength; j++ )
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
    new->length = length + 1 ;
    new->neurons = malloc(new->length * sizeof(double));

    //
    if(new->previousLayer) new->previousLayerLength = new->previousLayer->length;
    else new->previousLayerLength = nn->nbInput;

    new->w = (double **) malloc(new->length * sizeof(double *));
    for( unsigned long long i = 1; i < new->length; i++) {
        new->w[i] = (double *) malloc(new->previousLayerLength * sizeof(double *));
    }

    return ;
}

//
void initNeuralNetwork(NeuralNetwork * nn, unsigned long long nbInput, unsigned long long nbHiddenLayer, unsigned long long nbNeuronsHidden, unsigned long long nbNeuronsOutput ){
    nbInput += 1;
    nn->nbInput = nbInput;
    nn->input = malloc(nbInput * sizeof(double));

    //
    nn->firstLayer = NULL;
    nn->lastLayer = NULL;

    while (nbHiddenLayer > 0) {
        nbHiddenLayer -= 1;
        initLayer(nn, nbNeuronsHidden );
    }

    initLayer(nn, nbNeuronsOutput );

    //
    return;
}

//
