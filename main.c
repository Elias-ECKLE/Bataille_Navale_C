
/*FEATURES :
- Message d'accueil
- demander au jouur 1 de placer chacun de ces navires sur sa map, à chaque bateau posé un slash vert s'affich
- demander au joueur 2 de placer ses navires sur sa map : il y a 5 navires soit 1 porte avion(5cases)/1croiseur(4cases)/1ontre-torpilleur(3cases)/1sous-marin(3cases),1torpilleur(2cases)
- Lancer la phase d'attaque, chacun à son tour va proposer une case à tirer dessus ::: avec une lettre et un chiffre
- Si touché alors, on écrit touché et on met une petite barre dans le tableau /Si dernier élément à être touché , alors on affiche Touché coulé et fin du jeu/Sinon on affiche raté
- on met à jour chaque map
- fin du jeu: on indique qui est le gagnant
*/

/*deux tableau : la grille du joueur 1 & joueur2 (0 pour l'eau, 1 pour un bateau, -1 bateau touché)
 1 affichage indépendant des tabs en cas parmi avec goto qui transforme les chiffres des tableaux en caractères soit :  -=0 / /=1   / -1=x   /  o=masqué
*/



#include "define.h"



int main()
{
    //init :------------------------------------------
        //JOUEUR J1 ET J2
    joueur J1;
    joueur J2;


    J1.navires.tailleTorpilleur=TAILLE_Torpilleur;
    J1.navires.taillePorteAvion=TAILLE_PorteAvion;
    J1.navires.tailleContreTorpilleur=TAILLE_ContreTorpilleur;
    J1.navires.tailleSousMarin=TAILLE_SousMarin;
    J1.navires.tailleCroiseur=TAILLE_Croiseur;

    strcpy(J1.navires.nomTorpilleur,NOM_Torpilleur);
    strcpy(J1.navires.nomPorteAvion,NOM_PorteAvion);
    strcpy(J1.navires.nomContreTorpilleur,NOM_ContreTorpilleur);
    strcpy(J1.navires.nomSousMarin,NOM_SousMarin);
    strcpy(J1.navires.nomCroiseur,NOM_Croiseur);
    strcpy(J1.nom,NOM_j1);

    J2.navires.tailleTorpilleur=TAILLE_Torpilleur;
    J2.navires.taillePorteAvion=TAILLE_PorteAvion;
    J2.navires.tailleContreTorpilleur=TAILLE_ContreTorpilleur;
    J2.navires.tailleSousMarin=TAILLE_SousMarin;
    J2.navires.tailleCroiseur=TAILLE_Croiseur;

    strcpy(J2.navires.nomTorpilleur,NOM_Torpilleur);
    strcpy(J2.navires.nomPorteAvion,NOM_PorteAvion);
    strcpy(J2.navires.nomContreTorpilleur,NOM_ContreTorpilleur);
    strcpy(J2.navires.nomSousMarin,NOM_SousMarin);
    strcpy(J2.navires.nomCroiseur,NOM_Croiseur);
    strcpy(J2.nom,NOM_j2);


        //ETAT possible lors du jeu
    state etatJeu;
    etatJeu.debut=NB_EtatDebut;
    etatJeu.fin=NB_EtatFin;
    etatJeu.plcmt_Navires=NB_EtatPlacement;
    etatJeu.attq_Navires=NB_EtatAttaque;


        //Chiffres et caractères pour remplir et afficher les tableaux
    chiffresCaracts_Map nbCar_map;
    nbCar_map.nbBateau=NB_Bateau;
    nbCar_map.nbEau=NB_Eau;
    nbCar_map.nbBateauTouche=NB_BateauTouche;
    nbCar_map.carBateau=CAR_Bateau;
    nbCar_map.carEau=CAR_Eau;
    nbCar_map.carBateauTouche=CAR_BateauTouche;
    nbCar_map.carMasque=CAR_Masque;


        //Init des deux grilles :
    initMap(J1.grille,nbCar_map.nbEau);
    initMap(J2.grille,nbCar_map.nbEau);


        //Init graduation :
    char tabGrad_Lettres[TAILLE_Grille];
    strcpy(tabGrad_Lettres,GRAD_lettres);





    //__________________________________________________________________________________
    //Affichage debut __________________________________________________________________
     affichMsg_DebutFin(etatJeu.debut,etatJeu);


    //----------------------------------------------------------------------------------
    //Placement des navires-------------------------------------------------------------

        //J1
     maj_AffichMap(J1.grille, nbCar_map, tabGrad_Lettres, etatJeu.plcmt_Navires, etatJeu);
     placementNavires(J1.grille,J1,nbCar_map,tabGrad_Lettres,etatJeu.plcmt_Navires,etatJeu,VERTICAL,HORIZONTAL);

        //J2
     maj_AffichMap(J2.grille, nbCar_map, tabGrad_Lettres, etatJeu.plcmt_Navires, etatJeu);
     placementNavires(J2.grille,J2,nbCar_map,tabGrad_Lettres,etatJeu.plcmt_Navires,etatJeu,VERTICAL,HORIZONTAL);
     printf("top la");







    return 0;
}
