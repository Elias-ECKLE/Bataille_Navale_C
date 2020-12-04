#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_CAR 21
#define TAILLE_Grille 10

#define TAILLE_Torpilleur 2
#define TAILLE_PorteAvion 5
#define TAILLE_ContreTorpilleur 3
#define TAILLE_SousMarin 3
#define TAILLE_Croiseur 4

#define NOM_Torpilleur "torpilleur"
#define NOM_PorteAvion "porte-avion"
#define NOM_ContreTorpilleur "contre torpilleur"
#define NOM_SousMarin "sous marin"
#define NOM_Croiseur "croiseur"
#define NOM_j1 "J1"
#define NOM_j2 "J2"


#define NB_EtatDebut 0
#define NB_EtatFin -1
#define NB_EtatPlacement 1
#define NB_EtatAttaque 2
#define NB_Victore 1
#define NB_Defaite 0


#define NB_Eau 0
#define NB_BateauTouche -1
#define NB_Bateau 1
#define CAR_Eau '-'
#define CAR_BateauTouche 'x'
#define CAR_Bateau '/'
#define CAR_Masque 'o'

//Graduation :
//Les chiffres dépendent de TAILLE_Grille
//Les lettres d'ici
#define GRAD_lettres "ABCDEFGHIJ"


#define VERTICAL 'v'
#define HORIZONTAL 'h'


typedef struct state{

    int fin;
    int debut;
    int plcmt_Navires;
    int attq_Navires;
}state;



typedef struct chiffresCaracts_Map{

    int nbBateauTouche;
    int nbEau;
    int nbBateau;
    char carBateauTouche;
    char carEau;
    char carBateau;
    char carMasque;
}chiffresCaracts_Map;


typedef struct coords{

    int x;
    int y;
}coords;



typedef struct bateaux{

    int tailleTorpilleur;
    int taillePorteAvion;
    int tailleContreTorpilleur;
    int tailleSousMarin;
    int tailleCroiseur;

    char nomTorpilleur[TAILLE_CAR];
    char nomPorteAvion[TAILLE_CAR];
    char nomContreTorpilleur[TAILLE_CAR];
    char nomSousMarin[TAILLE_CAR];
    char nomCroiseur[TAILLE_CAR];

}bateaux;



typedef struct joueur{

    char nom[TAILLE_CAR];
    int grille[TAILLE_Grille][TAILLE_Grille];//10 par 10
    bateaux navires;
    int victoire;



}joueur;





extern void affichMsg_DebutFin(int etat, state etatBase);
extern void initMap(int grille[][TAILLE_Grille],int nbEau);
extern void maj_AffichMap(int grille[][TAILLE_Grille],chiffresCaracts_Map car_chiffres, char tab_lettres[],int etat,state etatBase);
extern void poseNavire(int grille[][TAILLE_Grille], int tailleNavire, int nbPoseNavire,coords coords1,coords coords2,int carSens, char vertical, char horizontal);
extern void placementNavires(int grille[][TAILLE_Grille],joueur Joueur,chiffresCaracts_Map chiffre_car, char tab_lettres[],int etat, state etatBase,char vertical, char horizontal);
extern void choisirPlcmt_Navires(int grille[][TAILLE_Grille],char nomNavire[], int tailleNavire,chiffresCaracts_Map chiffre_car, char tab_lettres[],int etat, state etatBase,char vertical, char horizontal);
extern int checkEmplacementNavire(int grille[][TAILLE_Grille], chiffresCaracts_Map chiffre_car,coords coords1, coords coords2, int tailleNavire, char sensPosition, char vertical, char horizontal);

#endif // DEFINE_H_INCLUDED
