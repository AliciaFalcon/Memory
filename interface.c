#include<stdlib.h>
#include<graph.h>
#include<stdio.h> 
#include<string.h>
#include<time.h>
#include "interface.h"
#include "menu.h"

/*
Fonction qui ¨structure¨ le programme avec toutes les autres fonctions.
*/

void Jeu() {

	int taille_grille = Niveau();
	Image tab_img[40];	
	unsigned long suivant = Microsecondes()+Seconde;		/*DEFINE*/
	unsigned long temps=0;
	unsigned long tempsTempo=0;
	int indice = -1;									/*indice correspond au numéro de la carte sur laquelle on a cliqué*/
	int indice_un = -1;									/*indice_un correspond à la première carte sur laquelle on clique et indice_deux à la deuxième*/
	int indice_deux = -1;
	int tempo = 0;

	InitTableauImage(tab_img, taille_grille);
	Aleatoire(taille_grille, tab_img);
	Fenetre();								/*Fenetre du jeu*/
	AffichageCarte(tab_img, taille_grille, indice);
	while(ToutTrouver(tab_img, taille_grille) == 0) {						/*La boucle continue de s'exécuter tant que l'on n'a pas trouvé toutes les paires de cartes*/
		Timer(&suivant, &temps);											/*Affiche le temps en secondes écoulées depuis le début d'une partie*/
		Attente(&tempo, &tempsTempo, tab_img, &indice_un, &indice_deux);	/*La fonction Attente est appellé ici pour remettre à 0 le tempo qui permet de rester dans la boucle if, il est mit à 1 dès que des cartes différentes sont retournés*/
		if(tempo == 0) {
			Tricheur(taille_grille, tab_img);								/*Active le mode tricheur tant que la touche "T" est appuyé*/
			if(SourisCliquee()) {											/*Boucle qui s'exécute au moment où on clique*/
				indice = CarteIndice(taille_grille);
				if(indice != -1) {											/*On exécute cette boucle quand on clique sur une carte ; indice = -1 quand on ne clique sur aucune carte*/
					if(tab_img[indice].retourner == 0) {					/*Si les cartes sont de dos*/
						tab_img[indice].retourner = 1;						/*On les retourne*/
						AffichageCarte(tab_img, taille_grille, indice);		/*Et on affiche la face*/
						if (indice_un == -1){								
							indice_un = indice;
						} else {
							indice_deux = indice;
							if (CarteIdentique (tab_img, taille_grille, indice_un, indice_deux) == 1) {			/*Si les cartes ne sont pas identiques on attends 1 secondes*/
								tempo = 1;																		/*tempo prend la valeur 1 et donc on exécute plus le premier if*/
								tempsTempo = Microsecondes()+Seconde;											/*tempsTempo est égal aux miicrosecondes plus la seconde qu'on veut qu'il s'écoule*/
							} else {
								indice_un = -1;																/*On réinitialise les indices*/
								indice_deux = -1;
							}
						}
					}
				}
			}
		}
	}
	Victoire(tab_img, taille_grille);
}

/*Equivalent de la fonction "sleep", elle permet de faire s'écouler une seconde avant que deux cartes différentes se retournent*/

void Attente(int* tempo, unsigned long* tempsTempo, Image *tab_img, int* indice_un, int* indice_deux) {

	if(*tempo == 1) {
		if (Microsecondes() > *tempsTempo) {				/*tempsTempo sera supérieur à Microsecondes pendant une seconde*/
			tab_img[*indice_un].retourner = 0;				/*On remet les cartes qui ne sont pas identiques à la valeur quand elles sont de dos*/
			tab_img[*indice_deux].retourner = 0;
			chargerUneImage("./Images/CarteDos.png", tab_img[*indice_un].positionX, tab_img[*indice_un].positionY);					/*Et on charge leurs dos*/
			chargerUneImage("./Images/CarteDos.png", tab_img[*indice_deux].positionX, tab_img[*indice_deux].positionY);

			*indice_un = -1;								/*On réintialise les indices*/
			*indice_deux = -1;
			*tempo = 0;										/*Ainsi que le tempo pour pouvoir repasser dans la boucle if*/
			while(SourisCliquee()) {
				SourisPosition();				/*Permet de vider le buffer souris, pour ne pas que la fonction prenne en compte les cliques pendant son exécution*/
			}	
		}
	}	
}

void Fenetre() {	/*Charge le fond du jeu*/

    ChargerImageFond("./Images/Fondecran.jpg");
}

/* La focntion permet de connaître l'indice de chaque cartes de la grille en fonction de la ligne et de la colonne où elles se trouvent.*/

int CarteIndice(int taille) {														/*Donne l'indice/numéro de la carte en fonction de la ligne et des colonnes*/
	int colonne, ligne, position_x = -1, position_y = -1 , indice = -1;
	SourisPosition();

	for(ligne=0 ; ligne<4 ; ligne++) {
		if(_Y >= (45 + ligne*115) &&  _Y < (145 + ligne*115) ) {	/* ligne 1 ---> y=45+115*ligne / x=50+80*colonne */
			position_y = ligne;
			break;
		}
	}

	for(colonne=0 ; colonne<taille ; colonne++) {
		if(_X >= (50 + 80*colonne) &&  _X < (115 + 80*colonne) ) {			/*on prend 50 pour le x de la première carte + la largeur de la carte et la distance entre deux cartes (80) * la colonne, et 115 pour la hauteur plus la distance entre les cartes*/
			position_x = colonne;
			break;
		}
	}

	if(position_x != -1 && position_y != -1) {							/*Si les positions n'ont pas changé de valeur c'est que le clic n'étaient pas sur les cartes, il vaut -1 comme indice*/
		indice = position_y*taille + position_x;
	}
	return indice;
}

void chargerUneImage(char* nom, int x, int y) {
	ChargerImage(nom, x, y,0,0,65,100);
}

/*Affiche les images des cartes si leurs valeurs est à 1 pour retourner, sinon on charge le dos*/

void AffichageCarte(Image *tab_img, int taille, int indice) {

	int compteur;

	for(compteur=0 ; compteur<taille*4 ; compteur++) {
		if(tab_img[compteur].trouver == 0) {
			if(tab_img[compteur].retourner == 1) {									/*retourner = 1 : la carte est de face*/
				chargerUneImage(tab_img[indice].nom, tab_img[indice].positionX, tab_img[indice].positionY);
			} else {
				chargerUneImage("./Images/CarteDos.png", tab_img[compteur].positionX, tab_img[compteur].positionY);
			}
		}
	}	
}	

int ToutTrouver(Image *tab_img, int taille) {					/*Pour quand toutes les cartes sont trouvées, le jeu est gagné*/
	int compteur, trouver=0;

	for(compteur=0 ; compteur<taille*4 ; compteur++) {			/*Nombre les cartes trouvées*/
		if(tab_img[compteur].trouver == 1) {
			trouver++;
		}
	}
	if(trouver == taille*4) {						/*Toutes les cartes sont trouvées, on fait taille*4 vu que taille correspond aux colonnes et qu'il y a toujours 4 lignes*/
		return 1;
	}
	return 0;
}


void Victoire(Image *tab_img, int taille) {							/*Charge le fond et l'image si toutes les cartes sont trouvées*/

	if(ToutTrouver(tab_img, taille) == 1) {
		ChargerImageFond("./Images/Fondecran.jpg");
    	ChargerImage("./Images/victoire.png",120,60,0,0,650,450);
    }	

}

int CarteIdentique(Image *tab_img, int taille, int indice_un, int indice_deux) {	/*Renvoie 0 quand les deux cartes retournées sont les mêmes (=leurs noms sont identiques) sinon 1*/
	int retour = 1;

		if(strcmp(tab_img[indice_un].nom, tab_img[indice_deux].nom) == 0) {							/*Compare les deux chaînes de caractères*/
			tab_img[indice_un].trouver = 1;														/*Affecte la valeur 1 à trouver pour les deux cartes identiques*/
			tab_img[indice_deux].trouver = 1;	
			retour = 0; 

		}
		return retour;
}

void InitTableauImage(Image *tab_img, int taille) {				/*Initialise un tableau de la structure Image pour mettre toutes les cartes*/
 
	int compteur, ligne, position_x, position_y, j=0;

	for(ligne=0 ; ligne<4 ; ligne++) {
		for(compteur=0 ; compteur<taille ; compteur++) {
			position_x=80;
			position_y=115;
			position_x=position_x*compteur;
			position_y=position_y*ligne;

			tab_img[j].positionX = position_x+50; 
			tab_img[j].positionY = position_y+45;
			tab_img[j].retourner = 0;									/*Initialisation par défaut de retourner et trouver à 0*/
			tab_img[j].trouver = 0;

			j=j+1;
		}	
	}	

	strcpy(tab_img[0].nom, "./Images/image0.png");			/*[Numéro carte]==[Numéro case de tableau]*/
	strcpy(tab_img[1].nom, "./Images/image0.png");
	strcpy(tab_img[2].nom, "./Images/image1.png");
	strcpy(tab_img[3].nom, "./Images/image1.png");
	strcpy(tab_img[4].nom, "./Images/image2.png");
	strcpy(tab_img[5].nom, "./Images/image2.png");
	strcpy(tab_img[6].nom, "./Images/image3.png");
	strcpy(tab_img[7].nom, "./Images/image3.png");
	strcpy(tab_img[8].nom, "./Images/image4.png");
	strcpy(tab_img[9].nom, "./Images/image4.png");
	strcpy(tab_img[10].nom, "./Images/image5.png");
	strcpy(tab_img[11].nom, "./Images/image5.png");
	strcpy(tab_img[12].nom, "./Images/image6.png");
	strcpy(tab_img[13].nom, "./Images/image6.png");
	strcpy(tab_img[14].nom, "./Images/image7.png");
	strcpy(tab_img[15].nom, "./Images/image7.png");
	strcpy((tab_img[16]).nom, "./Images/image8.png");
	strcpy((tab_img[17]).nom, "./Images/image8.png");
	strcpy((tab_img[18]).nom, "./Images/image9.png");
	strcpy((tab_img[19]).nom, "./Images/image9.png");
	strcpy((tab_img[20]).nom, "./Images/image10.png");
	strcpy((tab_img[21]).nom, "./Images/image10.png");
	strcpy((tab_img[22]).nom, "./Images/image11.png");
	strcpy((tab_img[23]).nom, "./Images/image11.png");
	strcpy((tab_img[24]).nom, "./Images/image12.png");
	strcpy((tab_img[25]).nom, "./Images/image12.png");
	strcpy((tab_img[26]).nom, "./Images/image13.png");
	strcpy((tab_img[27]).nom, "./Images/image13.png");
	strcpy((tab_img[28]).nom, "./Images/image14.png");
	strcpy((tab_img[29]).nom, "./Images/image14.png");
	strcpy((tab_img[30]).nom, "./Images/image15.png");
	strcpy((tab_img[31]).nom, "./Images/image15.png");
	strcpy((tab_img[32]).nom, "./Images/image16.png");
	strcpy((tab_img[33]).nom, "./Images/image16.png");
	strcpy((tab_img[34]).nom, "./Images/image17.png");
	strcpy((tab_img[35]).nom, "./Images/image17.png");
	strcpy((tab_img[36]).nom, "./Images/image18.png");
	strcpy((tab_img[37]).nom, "./Images/image18.png");
	strcpy((tab_img[38]).nom, "./Images/image19.png");
	strcpy((tab_img[39]).nom, "./Images/image19.png");
}

void Aleatoire(int taille, Image *tab_img) {				/*Fonction qui mélange les cartes*/

	int A_MIN = 0;
	int A_MAX = taille;
	int nombre_aleatoire, compteur;
	char chaine[30];

	srand(time(NULL));											/*On génère un nombre aléatoire toutes les secondes*/

	for(compteur=0 ; compteur<taille*4 ; compteur++) {
		nombre_aleatoire = A_MIN + rand()% (A_MAX-A_MIN +1);			/*un nombre alétoire entre 0 et la taille (nombre de colonnes)*/
		strcpy(chaine, tab_img[compteur].nom);							/*On copie les nom un par un du tableau dans une chaîne de caractère pour le ¨sauvegarder¨*/		
		strcpy(tab_img[compteur].nom, tab_img[nombre_aleatoire].nom);	/*La case désigné par le nombre aléatoire copie le nom de la case du tableau égal au compteur*/
		strcpy(tab_img[nombre_aleatoire].nom, chaine);					/*Et la case du nombre aléatoire reçoit la chaîne de caractères de celui-ci*/
																		/*Il échangent leur noms*/
	}

}

void Tricheur(int taille, Image *tab_img) {				/*Fonction qui gère le mode tricheur avec la touche t*/

	int compteur;

	if(ToucheEnAttente() == 1) {				/*On attend une touche, la touche t*/
		if(Touche() == XK_t) {
			for(compteur=0 ; compteur<taille*4 ; compteur++) {
				if(tab_img[compteur].retourner == 0) {				/*Une fois après avoir appuyé sur la touche t, les cartes pas retournées se retournent*/
					chargerUneImage(tab_img[compteur].nom, tab_img[compteur].positionX, tab_img[compteur].positionY);
				}
			}

			while (Touche() != XK_t) {		/*Sortie du mode tricheur, le temps arrête de s'afficher toutes les secondes, car le programme est ¨bloqué¨ dans cette boucle*/
			}
				for(compteur=0 ; compteur<taille*4 ; compteur++) {
					if(tab_img[compteur].trouver == 0 && tab_img[compteur].retourner == 0) {		/*Les cartes trouvées et retournées sont laissées telles quelles*/
						chargerUneImage("./Images/CarteDos.png", tab_img[compteur].positionX, tab_img[compteur].positionY);
					}
				}	
				while(SourisCliquee()) {
					SourisPosition();				/*Vider le buffer souris, pour ne pas prendre en compte les clics de la souris pendant le mode triche*/
				}		
			
		}
	}
}		

void Timer(unsigned long* suivant, unsigned long* temps) {			/*Affiche le temps*/

char tab[100] = {0};

		if (Microsecondes()>*suivant) {
			*suivant = Microsecondes()+Seconde;	
			*temps=*temps+1;					/*temps = secondes écoulées depuis le début du programme*/
			sprintf(tab,"Temps : %05ld",*temps);		/*On copie la variable temps dans un tableau*/
			CopierZone(0,0,200,515,140,30,380,575);		/*Pour ¨rafraîchir¨, sinon le temps se superpose et devient illisible*/
			EcrireTexte(385,590,tab,1);					/*On écrit la valeur du temps*/
		}
}	