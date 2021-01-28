#ifndef _MORPION_H_
    #define _MORPION_H_

    #define NB_LIG 3
    #define NB_COL 3

    typedef enum {VIDE, ROND, CROIX} ValeurGrille;
    typedef enum {FALSE, TRUE} Boolean;
    static ValeurGrille grille[NB_LIG][NB_COL]; /* grille du morpion valeurs possibles VIDE, ROND ou CROIX */

    /* indique quel sera le prochain joueur a mettre un pion dans la grille ie soit ROND soit CROIX */
    static int prochainJoueur = ROND;

    double * getInput();
    void initialiseGrille();
    void afficheGrille();
    void setInput();
    Boolean metUnPionSurLaGrille();
    Boolean testeFinJeu();


#endif
