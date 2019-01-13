#include<stdlib.h>
#include<graph.h>
#include<stdio.h> 
#include "interface.h"
#include "menu.h"

int main() {

AffichageMenu();		/*Affichage du menu avec les tailles de grille différentes*/
Jeu();					/*Fonction qui gère tout le fonctionnement du jeu*/

Touche();				/*Il y a Touche ici pour empêcher le programme de se fermer dès que le jeu est fini, il faut alors appuyer sur une touche ou fermer la fenêtre pour quitter le jeu*/
FermerGraphique();

 return EXIT_SUCCESS;

}	