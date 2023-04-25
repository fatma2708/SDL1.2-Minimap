#ifndef perso_H_INCLUDED
#define perso_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/** 
* @struct Personne 
* @brief struct pour personne 
*/ 


typedef struct Personne
{
	SDL_Surface *images[2][4]; /*!< matrices contenant les 24 frames*/
	SDL_Rect position;
	int direction;
	int nbr_frame;
	/*
		0:droite
		1:gauche
	*/
	double vitesse,acceleration,vitesse_saut;

}Personne;

/** 
* @brief initialiser le perso . 
* @param p le perso   
* @return Nothing 
*/ 

void initPerso(Personne *p);
/** 
* @brief afficher le personnage . 
* @param p le perso 
* @param screen le fentre  
* @return Nothing 
*/ 

void afficherPerso(Personne p, SDL_Surface * screen);
/** 
* @brief deplacer le personnage . 
* @param p perso 
* @param dt durée du temps entre le debut el fin de boucle  
* @return Nothing 
*/ 

void deplacerPerso (Personne *p,int dt);

/** 
* @brief animation du personnage . 
* @param p perso  
* @return Nothing 
*/ 

void animerPerso (Personne* p);

/** 
* @brief saut du personnage . 
* @param p perso 
* @return Nothing 
*/ 

void saut (Personne* p) ;


 #endif
