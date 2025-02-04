#ifndef NEAT_H
    #define NEAT_H

    #define TAILLE_POPULATION 1000
    //#define CROSSOVER_NUMBER 100
    #define NB_INPUT 8
    #define NB_HIDDEN_LAYER 1
    #define NB_NEURONS_HIDDEN 8
    #define NB_NEURONS_OUTPUT 4
    #define MUTATION_RATE 0.3
    #define SIGMA_MUTATION 0.15
    //#define SIGMA_CROSSOVER 1
    #define CROSSOVER_PERCENT 30

    int TAILLE_CROSSOVER_MAX ;//10 //= (TAILLE_POPULATION * CROSSOVER_PERCENT ) / 100;
    int TOTAL_WEIGHT ; //40
    //

    char *inputChar[20];// = {"haut","bas","gauche","droite"};
    char *outputChar[4];

    FILE* fileScore;
    FILE* fileId;
    FILE* fileFruit;

    typedef struct Layer
    {
        double * neurons;
        //double * derivative;

        double ** w;
        double * bias;
        //int id ;
        unsigned long long length;
        //unsigned long long previousLayerLength;
        //int numLayer;

        struct Layer * nextLayer;
        struct Layer * previousLayer;
    }Layer;

    //
    typedef struct NeuralNetwork
    {
        //double * input;
        //unsigned long long nbInput;
        //double * expectedOutput;
        double score;
        double rawScore;
        double nbFruit;
        double fitness;
        int id;
        struct Layer * firstLayer;
        struct Layer * lastLayer;
    }NeuralNetwork;

    /*prototype*/
    void initGlobalVar();
    double sigmoid(double x);
    double newSigmoid(double x);
    double newSigmoid2(double x);
    double d_sigmoid(double x);
    double rand_gen();
    double normalRandom();
    void allocatetab2D(int ***tab2D);
    unsigned long long result( NeuralNetwork * nn );
    void compute(NeuralNetwork * nn);
    void setInput(NeuralNetwork * nn, double * inputList);
    void printNetwork(NeuralNetwork * nn);
    void printPopulaton(NeuralNetwork ** population);
    void afficherData(NeuralNetwork * nn);
    void initWeigth(NeuralNetwork * nn);
    //void initEmptyWeigth(NeuralNetwork * nn);
    void initLayer(NeuralNetwork * nn, unsigned long long taille );
    //void initOutputLayer(NeuralNetwork * nn, unsigned long long taille );
    void initNeuralNetwork(NeuralNetwork * nn, unsigned long long nbInput, unsigned long long nbHiddenLayer, unsigned long long nbNeuronsHidden, unsigned long long nbNeuronsOutput );
    //NeuralNetwork * initNeuralNetworkV2( unsigned long long nbInput, unsigned long long nbHiddenLayer, unsigned long long nbNeuronsHidden, unsigned long long nbNeuronsOutput );
    void copy(NeuralNetwork * NewNn,  NeuralNetwork * nn );
    NeuralNetwork ** fuck(NeuralNetwork ** population);
    NeuralNetwork *  pickOne(NeuralNetwork ** population);
    NeuralNetwork * crossover(NeuralNetwork * a, NeuralNetwork * b);
    void calculateFitness(NeuralNetwork ** population);
    //void copy( NeuralNetwork * nn );
    void mutate( NeuralNetwork * nn );
    NeuralNetwork * bestElement(NeuralNetwork ** population);
    void setScore(NeuralNetwork * nn, double score, double nbFruit);
    void destroyPopulation(NeuralNetwork ** population);
    void destroyNetwork(NeuralNetwork * nn);
    void destroyLayer(Layer * layer);

    FILE* openLog( char *fileName );
    void writeLogScore ( FILE* fichier,  NeuralNetwork ** population );
    void writeLogId ( FILE* fichier,  NeuralNetwork ** population );
    void writeLogFruit( FILE* fichier,  NeuralNetwork ** population );
    void closeLog( FILE* fichier);
#endif
