#include<stdlib.h>
#include<graph.h>
#include<stdio.h>
#include "menu.h"
#include "interface.h"

/*Fichier menu qui contient les fonctions en rapport avec celui-ci :

Niveau : Permet de renvoyer le niveau (=taille de la grille) choisie.
La grille de jeu possède toujours 4 lignes, il y a seulement les colonnes qui changent variant de 4 à 10.
*/

int Niveau() {     

    int taille=0, flag=0;

    while(flag==0) {
        if(SourisCliquee()) {                                      /*Pour détecter quand on clique sur l'une des trois images correspondant aux 3 niveaux de difficultés :*/
            if((_Y>240 && _Y<290) && (_X>90 && _X<220)) {          /*Facile : 16 cartes*/
                taille=4;
                flag=1;                                             
            }
            if((_Y>310 && _Y<360) && (_X>90 && _X<220)) {          /*Intermédiaire : 28 cartes*/
                taille=7;
                flag=1; 
            }
            if((_Y>380 && _Y<430) && (_X>90 && _X<220)) {         /*Difficile : 40 cartes*/
                taille=10;
                flag=1;
            }        
        }
    }    
    return taille;                                                  /*On renvoie la taille par rapport aux coordoonées du clique de la souris*/
}    

/*AffichageMenu : Affiche le menu avec le fond et les images*/

void AffichageMenu() {                        
/*int flag;*/

	InitialiserGraphique();
    CreerFenetre(0,0,900,600);
    ChargerImageFond("./Images/fondbonbis.png");
    ChargerImage("./Images/easy.png",90,240,0,0,130,50);
    ChargerImage("./Images/medium.png",90,310,0,0,130,50);
    ChargerImage("./Images/hard.png",90,380,0,0,130,50);
}