#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <ctype.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Personne.h"
/** 
* @file Personne.c 
* @brief tache personne source. 
* @author Zeineb Ben khalifa
* @version 0.3 
* @date Apr 01, 2021 
* 
* Testing program for perso * 
*/



void initPerso(Personne *p){
	int i,j;
    char nom_image[30];
    p->acceleration=0;
    p->direction=0;
    p->nbr_frame=0;

    p->position.x=50;
    p->position.y=300;

    p->vitesse=0;
    p->vitesse_saut=0;

 
    for ( i = 0; i < 2; i++)
    {
        for ( j = 0; j < 4; j++)
        {   
            sprintf(nom_image,"animation/%d/%d.png",i,j);
            p->images[i][j]=IMG_Load(nom_image);
        }
        
    }
    
	p->position.w=p->images[0][0]->w-100;
	p->position.h=p->images[0][0]->h-100;
}


void afficherPerso(Personne p, SDL_Surface * screen){
    SDL_BlitSurface(p.images[p.direction][p.nbr_frame],NULL,screen,&p.position);
}



void animerPerso (Personne* p){
    
  p->nbr_frame++;
    if (p->nbr_frame >= 4)
 p->nbr_frame=0;
if ((p->vitesse==0) && ((p->direction == 0) || (p->direction == 1)))
{
p->nbr_frame= 0;
}
}

void deplacerPerso (Personne *p,int dt){

double dx;
dx = 0.5 * p->acceleration * dt * dt + p->vitesse * dt ;
    if (p->direction==0)//mvt droite
    {
        p->position.x = p->position.x + dx ;        
    }else if (p->direction==1)
    {
        p->position.x = p->position.x - dx;
    }
    
}

void saut (Personne* p) {
    if (p->position.y == 300)
    {
       p->vitesse_saut=-50;
    }
    
}














