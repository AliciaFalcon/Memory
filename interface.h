#ifndef INTERFACE_H
#define INTERFACE_H
#define Seconde 1000000L

/*Structure "Image" : pour connaître la position x et y des cartes,
					  le nom/chemin avec une chaîne de caractère,
					  retourner : pour savoir si la carte est de dos ou de face ; 0 pour le dos et 1 pour la face,
					  trouver : pour savoir si la carte est trouvées (si on a retourné une paire) ; 0 pour quand elle ne sont pas trouvées et 1 quand elles le sont.
						*/

typedef struct Image {	
	int positionX;
	int positionY;
	int retourner;				
	int trouver;		
	char nom[30];
} Image ;

void Jeu();
void Victoire(Image *tab_img, int taille);
void Fenetre();
int CarteIndice(int taille);
void chargerUneImage(char* nom, int x, int y);
void Attente(int* tempo, unsigned long* tempsTempo, Image *tab_img, int* indice_un, int* indice_deux);
void AffichageCarte(Image *image, int taille, int indice);
int CarteIdentique(Image *tab_img, int taille, int indice, int indice_deux);
int ToutTrouver(Image *tab_img, int taille);
void InitTableauImage(Image *image, int taille);
void Tricheur(int taille, Image *tab_img);
void Aleatoire(int taille, Image *tab_img);
void Timer(unsigned long* suivant, unsigned long* temps);

#endif /* INTERFACE_H */