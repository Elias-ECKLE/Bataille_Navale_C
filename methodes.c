#include "define.h"



// Fonction qui permet de placer le curseur à la position x,y
//GOTO
void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}

//color :
/*
0 : Noir
1 : Bleu foncé
2 : Vert foncé
3 : Turquoise
4 : Rouge foncé
5 : Violet
6 : Vert caca d'oie
7 : Gris clair
8 : Gris foncé
9 : Bleu fluo
10 : Vert fluo
11 : Turquoise
12 : Rouge fluo
13 : Violet 2
14 : Jaune
15 : Blanc
*/
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
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
    Color(14,0);
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
                    Color(9,0);
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carEau);
                }
                if(grille[i][j]==car_chiffres.nbBateau){
                    Color(2,0);
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carBateau);
                }
            }

        }
    }
    if(etat==etatBase.attq_Navires){
            //remplacer les chiffres par des caracts
        for(i=0;i<TAILLE_Grille;i++){

            for(j=0;j<TAILLE_Grille;j++){

                if(grille[i][j]==car_chiffres.nbBateauTouche){
                    Color(4,0);
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carBateauTouche);
                }
                else{
                    Color(7,0);
                    gotoxy(i+2,j+1);
                    printf("%c",car_chiffres.carMasque);
                }

            }

        }
    }

    Color(15,0); //on remet par defaut la couleur


}









//INIT GRILLE DEBUT_________________________________________________________________________________

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

void saisirCoords_Init(coords *pCoords1, coords *pCoords2, char tabLettres[]){
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

        for(i=x1-1;i<x2;i++){

            grille[y1-1][i]=nbPoseNavire;
        }
    }
    if(carSens==horizontal){

        for(i=y1-1;i<y2;i++){

            grille[i][x1-1]=nbPoseNavire;


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
        saisirCoords_Init(&coords1,&coords2,tab_lettres);
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

}




//PHASE ATTAQUE_________________________________________________________________________________

void saisirCoords_Attack(coords *pCoords, char tabLettres[]){

    char car_x1;
    int test_y1;



    //coords 1--------------------------------------------------------------------
            //coord x

            getchar();

    printf("\n\nVeuillez saisir la coordoonee que vous souhaitez attaquer (ex:A1, E6 etc...)\n\n");
    do{
        printf("Lettre comprise entre A et J: ");
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



    //on recupere tout dans les pointeurs pCoords associés-----------------------------------------


        //on recupere les y :
    pCoords->y=test_y1;


        //premiere coord x
    switch(car_x1){
        case 'A':
            pCoords->x=1;
        break;

        case 'B':
            pCoords->x=2;
        break;

        case 'C':
            pCoords->x=3;
        break;

        case 'D':
            pCoords->x=4;
        break;
        case 'E':
            pCoords->x=5;
        break;
        case 'F':
            pCoords->x=6;
        break;
        case 'G':
            pCoords->x=7;
        break;
        case 'H':
            pCoords->x=8;
        break;
        case 'I':
            pCoords->x=9;
        break;
        case 'J':
            pCoords->x=10;
        break;

    }

}

void checkBateaux_Restants(int grille[][TAILLE_Grille],chiffresCaracts_Map chiffre_car,state etatPossible, int *etat){
//BUT : vérifier le nb de bateaux qui restent sur la map, si plus aucuns, fin de la partie

    int i;
    int j;

    *etat=etatPossible.fin;

    for(i=0;i<TAILLE_Grille;i++){
        for(j=0;j<TAILLE_Grille;j++){

            if(grille[i][j]==chiffre_car.nbBateau){

                *etat=etatPossible.attq_Navires;
            }
        }
    }


}

void checkCase_Attaque(int grille[][TAILLE_Grille],coords coords1, chiffresCaracts_Map chiffre_car, char tab_Lettres[],int etatJeu, state etatPossible){
//BUT : checker si la case sur laquelle on attaque a bien un bateau : 3cas->rien du coup on affiche raté, un nbbateau du coup "touché", un nbBateau et plus aucuns autour du coup "touché coulé"


    int x=coords1.x-1;
    int y=coords1.y-1;




    //les si suivants prennent en compte toutes les possibilites de plantage. En effet, pour differencier le "touché" qui donc signifie que le bateau n'est pas totalement detruit du "touche coule"
    //ou il ne reste plus rien du bateau, je verifie que les quatres cases entourant la position tirée sont egales a '1' ou non et en fct de cela j'en deduit si le bateau est entierement aneanti ou non
    if(grille[y][x]==chiffre_car.nbBateau){


        if ((x>1) || (x<TAILLE_Grille)){

            //or comme certaines positions ne disposent pas de quatres cases les entourant (les coins par exemple), il faut en tenir compte lors de la verification des
            // 'X' voisins et ainsi eviter le plantage du prog en placant des condtions
                if ((y>1) || (y<TAILLE_Grille)){

                    if((grille[y-1][x]==chiffre_car.nbBateau)||(grille[y+1][x]==chiffre_car.nbBateau) || (grille[y][x-1]==chiffre_car.nbBateau) || (grille[y][x+1]==chiffre_car.nbBateau)){

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche");
                    }
                    else{


                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche...coule !");
                    }
                }
                else if(y==1){

                    if ((grille[y+1][x]==chiffre_car.nbBateau) || (grille[y][x-1]==chiffre_car.nbBateau) || (grille[y][x+1]==chiffre_car.nbBateau)){

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche");
                    }
                    else{

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche...coule !");
                    }
                }
                else if (y==TAILLE_Grille){

                    if ((grille[y-1][x]==chiffre_car.nbBateau) || (grille[y][x-1]==chiffre_car.nbBateau) || (grille[y][x+1]==chiffre_car.nbBateau)){

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche");
                    }
                    else{

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche...coule !");
                    }
                }
        }



        else if (x==1){

                if ((y>1) || (y<TAILLE_Grille)){

                     if  ((grille[y-1][x]==chiffre_car.nbBateau) || (grille[y+1][x]==chiffre_car.nbBateau) || (grille[y][x+1]==chiffre_car.nbBateau)){

                           grille[y][x]=chiffre_car.nbBateauTouche;
                           maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                           printf("\nTouche");
                     }
                     else{

                           grille[y][x]=chiffre_car.nbBateauTouche;
                           maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                           printf("\nTouche...coule !");
                     }
                }

                else if(y==1){

                      if ((grille[y+1][x]==chiffre_car.nbBateau) || (grille[y][x+1]==chiffre_car.nbBateau)){

                            grille[y][x]=chiffre_car.nbBateauTouche;
                            maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                            printf("\nTouche");
                      }
                      else{

                            grille[y][x]=chiffre_car.nbBateauTouche;
                            maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                            printf("\nTouche...coule !");
                      }
                }

                else if (y==TAILLE_Grille){

                      if  ((grille[y-1][x]==chiffre_car.nbBateau) || (grille[y][x+1]==chiffre_car.nbBateau)){

                            grille[y][x]=chiffre_car.nbBateauTouche;
                            maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                            printf("\nTouche");
                      }
                     else{
                            grille[y][x]=chiffre_car.nbBateauTouche;
                            maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                            printf("\nTouche...coule !");
                     }
                }


            }

         else if (x==TAILLE_Grille){

              if ((y>1) || (y<TAILLE_Grille)){
                     if  ((grille[y-1][x]==chiffre_car.nbBateau) || (grille[y+1][x]==chiffre_car.nbBateau) || (grille[y][x-1]==chiffre_car.nbBateau)){

                         grille[y][x]=chiffre_car.nbBateauTouche;
                         maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                         printf("\nTouche");
                     }
                     else{

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche...coule !");
                     }
              }
              else if (y==1){

                     if  ((grille[y+1][x]==chiffre_car.nbBateau) || (grille[y][x-1]==chiffre_car.nbBateau)){

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche");
                     }
                     else{

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche...coule !");
                     }
              }
              else if (y==TAILLE_Grille){

                     if  ((grille[y-1][x]==chiffre_car.nbBateau) || (grille[y][x-1]==chiffre_car.nbBateau)){

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche");
                     }
                     else{

                        grille[y][x]=chiffre_car.nbBateauTouche;
                        maj_AffichMap(grille,chiffre_car,tab_Lettres,etatJeu,etatPossible);
                        printf("\nTouche...coule !");
                     }
              }

         }

    }
    //si la position tiree ne correspond pas a un emplacement ou se trouve un 'X' et donc un bateau, alors on affiche raté au joueur
    else{
        printf("\nRate");
    }



}

void attaqueBateau(int grille[][TAILLE_Grille],joueur Joueur,char tab_Lettres[], chiffresCaracts_Map chiffres_Car, int etatJeu,int *pEtatJeu, state etatPossible){

    coords coord;


    //on affiche la map cachée de l'adversaire
    maj_AffichMap(grille,chiffres_Car,tab_Lettres,etatJeu,etatPossible);

    printf("\n\n%s c'est l'heure d'attaquer",Joueur.nom);



    //saisir coordoonée qu'on veut attaquer
    saisirCoords_Attack(&coord,tab_Lettres);

    //on check si la coord touche un bateau ou non
    checkCase_Attaque(grille,coord,chiffres_Car,tab_Lettres,etatJeu,etatPossible);

    //et enfin on check s'il reste des bateaux à détruire ou non
    checkBateaux_Restants(grille,chiffres_Car,etatPossible,&etatJeu);


    *pEtatJeu=etatJeu;

}


