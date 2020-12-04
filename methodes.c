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
        gotoxy(i+1,0);
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
                    gotoxy(i+1,j+1);
                    printf("%c",car_chiffres.carEau);
                }
                if(grille[i][j]==car_chiffres.nbBateau){
                    gotoxy(i,j);
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



//INIT POSE DES NAVIRES_________________________________________________________________


void saisirCoords(coords *pCoords1, coords *pCoords2, char tabLettres[]){
//BUT: Saisir les coordoonéees et transformer la coord lettre en chiffre avec un cas parmi
//ENTREE:coords lettre et chiffre
//SORTIE:coord chiffre et chiffre


    char car_x1;
    char car_x2;
    int test_y1;
    int test_y2;


    //coords 1--------------------------------------------------------------------
            //coord x

    printf("\n\nVeuillez saisir les premieres coordoonees (ex:A1, E6 etc...)\n\n");
    do{
        printf("Lettre comprise entre A et J: ");
        getchar();
        scanf("%c",&car_x1);
        if((car_x1<tabLettres[0])||(car_x1>tabLettres[TAILLE_Grille-1])){
           printf("Erreur, mauvaise lettre ou caractere. Veuillez reessayer\n ");
        }
    }while((car_x1<tabLettres[0])||(car_x1>tabLettres[TAILLE_Grille-1]));

    getchar();

            //coord y
    do{
        printf("Chiffre compris entre 1 et 10: ");
        scanf("%d",&test_y1);
        if((test_y1<1)||(test_y1>TAILLE_Grille)){
           printf("Erreur, mauvaise chiffre ou caractere. Veuillez reessayer\n ");
        }
    }while((test_y1<1)||(test_y1>TAILLE_Grille));





    //coords2 -----------------------------------------------------------------------
    printf("\n\nVeuillez saisir les deuxiemes coordoonees (ex:A3, E9 etc...)\n");
    do{
        printf("Lettre comprise entre A et J: ");
        getchar();
        scanf("%c",&car_x2);
        if((car_x2<tabLettres[0])||(car_x2>tabLettres[TAILLE_Grille-1])){
           printf("Erreur, mauvaise lettre ou caractere. Veuillez reessayer\n ");
        }
    }while((car_x2<tabLettres[0])||(car_x2>tabLettres[TAILLE_Grille-1]));

    getchar();

            //coord y
    do{
        printf("Chiffre compris entre 1 et 10: ");
        scanf("%d",&test_y2);
        if((test_y2<1)||(test_y2>TAILLE_Grille)){
           printf("Erreur, mauvaise chiffre ou caractere. Veuillez reessayer\n ");
        }
    }while((test_y2<1)||(test_y2>TAILLE_Grille));




    //on recupere tout dans les pointeurs pCoords associés-----------------------------------------
    system("cls");

        //on recupere les y :
    pCoords1->y=test_y1;
    pCoords2->y=test_y2;
        //on transforme les coords lettres en chiffres :

        //premiere coord x
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
          //deuxieme coord x

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

void poseNavire(int grille[][TAILLE_Grille], int tailleNavire, int nbPoseNavire,coords coords1,coords coords2,int carSens, char vertical, char horizontal){
//BUT:Poser le navire sur la grille
//ENTREE:grille,navire en question, chiffre du navire
//SORTIE:navire sur la grille

    int i;
    int j;
    int x1=coords1.x;
    int x2=coords2.x;
    int y1=coords1.y;
    int y2=coords2.y;


    if(carSens==vertical){

        for(i=x1;i<x2+1;i++){

            grille[y1][i]=nbPoseNavire;
        }
    }
    if(carSens==horizontal){

        for(i=y1;i<y2+1;i++){

            grille[i][x1]=nbPoseNavire;


        }
    }


}

int checkEmplacementNavire(int grille[][TAILLE_Grille], chiffresCaracts_Map chiffre_car,coords coords1, coords coords2, int tailleNavire, char sensPosition, char vertical, char horizontal){
//BUT:vérifier si les coordoonees entrées correspondent à la taille du navire en question
//ENTREE: taille du navires, coords, sens


    int i;
    int j;
    int espaceLibre;
    int x1=coords1.x;
    int x2=coords2.x;
    int y1=coords1.y;
    int y2=coords2.y;
    int empltVide=1;

    //on regarde si les coordoonées prises collent à la place qu'il faut pour le bateau
    if((sensPosition==vertical)){
        espaceLibre=(x2-x1)+1;

    }
    if(sensPosition==horizontal){
        espaceLibre=(y2-y1)+1;

    }


    //on regarde si chacune de ces cases sont bien vides et qu'il n'y a pas un bateau dessus
    if(sensPosition==vertical){
        for(i=x1;i<x2+1;i++){

            if(grille[y1][i]==chiffre_car.nbBateau){
                empltVide=0;
            }
        }
    }
    if(sensPosition==horizontal){
        for(i=y1;i<y2+1;i++){

            if(grille[i][x1]==chiffre_car.nbBateau){
                empltVide=0;
            }
        }
    }


    //on retourne le feu vert ou rouge de la pose
    if((espaceLibre==tailleNavire)&&(empltVide==1)){
        return 1;
    }
    else{
        return 0;
    }


}


void choisirPlcmt_Navires(int grille[][TAILLE_Grille],char nomNavire[], int tailleNavire,chiffresCaracts_Map chiffre_car, char tab_lettres[],int etat, state etatBase,char vertical, char horizontal){

    char car;
    coords coords1;
    coords coords2;
    int emplmtNavire_valid=0;

    //navire---------------------------------------
    do{
        maj_AffichMap(grille,chiffre_car,tab_lettres,etat,etatBase);
        printf("\n\n Le %s comprend %d cases.\n",nomNavire,tailleNavire);
        printf("Voulez-vous le placer verticalement ou horizontalement ? (v->vertical/h->horizontal)\n");
        scanf("%c",&car);
        while((car!=vertical)&&(car!=horizontal)){
            printf("Erreur, veuillez reessayer : \n");
            //getchar();
            scanf("%c",&car);
        }
        saisirCoords(&coords1,&coords2,tab_lettres);
        emplmtNavire_valid=checkEmplacementNavire(grille, chiffre_car, coords1,coords2,tailleNavire,car,vertical,horizontal);
        system("cls");
    }while(emplmtNavire_valid==0);

    poseNavire(grille,tailleNavire,chiffre_car.nbBateau,coords1,coords2,car,vertical,horizontal);


}

void placementNavires(int grille[][TAILLE_Grille],joueur Joueur,chiffresCaracts_Map chiffre_car, char tab_lettres[],int etat, state etatBase,char vertical, char horizontal){




    //présentation-------------------------------------
    printf("%s voici votre map\n Pour commencer le placement des différents navires, veuillez appuyer sur entree",Joueur.nom);
    getchar();
    system("cls");


    //torpilleur---------------------------------------
    choisirPlcmt_Navires(grille,Joueur.navires.nomTorpilleur, Joueur.navires.tailleTorpilleur, chiffre_car, tab_lettres, etat, etatBase,vertical,horizontal);


    //porte avion
    choisirPlcmt_Navires(grille,Joueur.navires.nomPorteAvion, Joueur.navires.taillePorteAvion, chiffre_car, tab_lettres, etat, etatBase,vertical,horizontal);

    //contre-torpilleur
    choisirPlcmt_Navires(grille,Joueur.navires.nomContreTorpilleur, Joueur.navires.tailleContreTorpilleur, chiffre_car, tab_lettres, etat, etatBase,vertical,horizontal);

    //Sous-marin
    choisirPlcmt_Navires(grille,Joueur.navires.nomSousMarin, Joueur.navires.tailleSousMarin, chiffre_car, tab_lettres, etat, etatBase,vertical,horizontal);

    //croiseur
    choisirPlcmt_Navires(grille,Joueur.navires.nomCroiseur, Joueur.navires.tailleCroiseur, chiffre_car, tab_lettres, etat, etatBase,vertical,horizontal);
    getchar();

}


/*
//Phase d'attaque_________________________________________________________________________________
void attaqueBateau(){

    printf("Veuillez saisir un"):
    //saisir coordoonée qu'on veut attaquer

}

*/




void maj_Map(){
//BUT:mettre à jour l'emplacement des bateaux sur la grille
//ENTREE:map du joueur en question
//SORTIE: meme tableau
}




