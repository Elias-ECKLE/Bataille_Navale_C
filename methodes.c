#include "define.h"
#include <windows.h> //biblio pr gotoxyd


// Fonction qui permet de placer le curseur à la position x,y
//GOTO
void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}




//AFFICHAGE____________________________________________________________________________
void affichMsg_DebutFin(int etat, state etatBase){

//BUT:Afficher  message accueil, message fin
//ENTREE:etatJeu à 0=début du jeu/ -1=fin
//SORTIE:rien

    if(etat==etatBase.debut){
        printf("Bienvenue dans le jeu de la bataille navale. On y joue a deux a tour de role en laissant chacun acceder au clavier\n ");
    }
    if(etat==etatBase.fin){
        printf("Le jeu touche a sa fin.\n");
    }

    getchar();
}



void maj_AffichMap(int grille[][TAILLE_Grille],chiffresCaracts_Map car_chiffres, char tab_lettres[],int etat,state etatBase){
//BUT:Afficher en caractères la map de la grille du joueur en question
//ENTREE:grille en question et état du jeu soit 1 pour placement des navires, soit 2 pour la phase d'attaque
//SORTIE:rien

    system("cls");
    int i;
    int j;

//afficher une graduation :
    //1à10
    for(i=0;i<TAILLE_Grille;i++){
        gotoxy(i+2,0);
        printf("%d",i+1);
    }
    //AàJ
    for(i=0;i<TAILLE_Grille;i++){
        gotoxy(0,i+1);
        printf("%c",tab_lettres[i]);
    }



//remplacer les chiffres par des caracts

 //deux possibilités : soit les caractères pour placer les navires,soit pour l'attque

    //caracts placement
    if(etat==etatBase.plcmt_Navires){
        for(i=0;i<TAILLE_Grille;i++){

            for(j=0;j<TAILLE_Grille;j++){

                if(grille[i][j]==car_chiffres.nbEau){
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carEau);
                }
                if(grille[i][j]==car_chiffres.nbBateau){
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carBateau);
                }
                if(grille[i][j]==car_chiffres.carBateauTouche){
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carBateauTouche);
                }
            }

        }
    }
    if(etat==etatBase.attq_Navires){
            //remplacer les chiffres par des caracts
        for(i=0;i<TAILLE_Grille;i++){

            for(j=0;j<TAILLE_Grille;j++){

                if(grille[i][j]==car_chiffres.nbBateauTouche){
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carBateauTouche);
                }
                else{
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carMasque);
                }

            }

        }
    }


}









//SAISIE_________________________________________________________________________________

void initMap(int grille[][TAILLE_Grille],int nbEau){
//BUT:initialiser la map d'un joueur
//ENTREE:tabMap du joueur et chiffre avec lequel initialiser
//SORTIE:tabMap

    int i;
    int j;

    for(i=0;i<TAILLE_Grille;i++){
        for(j=0;j<TAILLE_Grille;j++){

            grille[i][j]=nbEau;
        }
    }

}





void saisirCoords(coords *pCoords1, coords *pCoords2){
//BUT: Saisir les coordoonéees et transformer la coord lettre en chiffre avec un cas parmi
//ENTREE:coords lettre et chiffre
//SORTIE:coord chiffre et chiffre


    char car_x1;
    char car_x2;

    printf("Veuillez saisir les premieres coordoonees (ex:A1, E6 etc...)\n\N");
    printf("Lettre: ");
    scanf("%c",&car_x1);
    getchar();
    printf("Chiffre: ");
    scanf("%d",&pCoords1->y);
    printf("Veuillez saisir les deuxiemes coordoonees (ex:A3, E9 etc...)\n");
    printf("Lettre: ");
    scanf("%c",&car_x2);
    getchar();
    printf("\nChiffre: ");
    scanf("%d",&pCoords2->y);

    system("cls");

    //on transforme les coords lettres en chiffres :

    //premiere coord
    switch(car_x1){
        case 'A':
            pCoords1->x=1;
        break;

        case 'B':
            pCoords1->x=2;
        break;

        case 'C':
            pCoords1->x=3;
        break;

        case 'D':
            pCoords1->x=4;
        break;
        case 'E':
            pCoords1->x=5;
        break;
        case 'F':
            pCoords1->x=6;
        break;
        case 'G':
            pCoords1->x=7;
        break;
        case 'H':
            pCoords1->x=8;
        break;
        case 'I':
            pCoords1->x=9;
        break;
        case 'J':
            pCoords1->x=10;
        break;

    }
          //premiere coord
    switch(car_x2){
        case 'A':
            pCoords2->x=1;
        break;

        case 'B':
            pCoords2->x=2;
        break;

        case 'C':
            pCoords2->x=3;
        break;

        case 'D':
            pCoords2->x=4;
        break;
        case 'E':
            pCoords2->x=5;
        break;
        case 'F':
            pCoords2->x=6;
        break;
        case 'G':
            pCoords2->x=7;
        break;
        case 'H':
            pCoords2->x=8;
        break;
        case 'I':
            pCoords2->x=9;
        break;
        case 'J':
            pCoords2->x=10;
        break;
    }
}

void poseNavire(int grille[][TAILLE_Grille], int tailleNavire, int nbPoseNavire,coords coords1,coords coords2,int carSens){
//BUT:Poser le navire sur la grille
//ENTREE:grille,navire en question, chiffre du navire
//SORTIE:navire sur la grille

    int i;
    int j;
    int x1=coords1.x;
    int x2=coords2.x;
    int y1=coords1.y;
    int y2=coords2.y;


    if(carSens==VERTICAL){
        for(i=x1;i<x2;i++){
            for(j=y1;j<y2;j++){

                grille[i][j]=nbPoseNavire;
            }
        }
    }
    if(carSens==HORIZONTAL){

        for(i=coords1.x;i<coords2.x;i++){
            for(j=coords1.y;j<coords2.y;j++){

                grille[j][i]=nbPoseNavire;
            }
        }
    }


}

void checkEmplacementNavire(){
}
void placementNavires(int grille[][TAILLE_Grille],joueur Joueur,chiffresCaracts_Map chiffre_car, char tab_lettres[],int etat, state etatBase){


    char car;

    coords coords1;
    coords coords2;

    //présentation
    printf("Voici votre map\n Pour commencer le placement des différents navires, veuillez appuyer sur entree");
    getchar();
    system("cls");

    //torpilleur
    maj_AffichMap(grille,chiffre_car,tab_lettres,etat,etatBase);
    printf("Le %s comprend %d cases.\n",Joueur.navires.nomTorpilleur,Joueur.navires.tailleTorpilleur);
    printf("Voulez-vous le placer verticalement ou horizontalement ? (v->vertical/h->horizontal)\n");
    scanf("%c",&car);
    saisirCoords(&coords1,&coords2);
    poseNavire(grille,Joueur.navires.tailleTorpilleur,chiffre_car.nbBateau,coords1,coords2,car);


    //porte avion
    maj_AffichMap(grille,chiffre_car,tab_lettres,etat,etatBase);
    printf("Le %s comprend %d cases.\n",Joueur.navires.nomPorteAvion,Joueur.navires.taillePorteAvion);
    printf("Voulez-vous le placer verticalement ou horizontalement ? (v->vertical/h->horizontal)\n");
    scanf("%c",&car);
    saisirCoords(&coords1,&coords2);
    poseNavire(grille,Joueur.navires.taillePorteAvion,chiffre_car.nbBateau,coords1,coords2,car);



    //contre torpilleur



    //sous marin


    //croiseur
}




void maj_Map(){
//BUT:mettre à jour l'emplacement des bateaux sur la grille
//ENTREE:map du joueur en question
//SORTIE: meme tableau
}




//CALCUL_________________________________________________________________________________
