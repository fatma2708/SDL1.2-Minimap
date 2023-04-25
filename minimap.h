#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>

typedef struct temps
{
SDL_Surface *texte;
 SDL_Rect position;

    TTF_Font *police ;

 char entree[100];
 int secondesEcoulees; 
SDL_Color noir;
time_t t1,t2; 
int min, sec;
}temps;

void initialiser_temps(temps *t);
void afficher_temps(temps *t, SDL_Surface *ecran);
void free_temps(temps *t,SDL_Surface *ecran);

typedef struct
{SDL_Surface *map;
SDL_Surface  *miniperso;
SDL_Rect positionmap;
SDL_Rect posperso;
SDL_Rect posminiperso;
}minimap;

void init_map (minimap *m); 
void MAJMinimap(SDL_Rect posperso,  minimap * m, SDL_Rect camera, int redimensionnement); 
void afficherminimap (minimap m, SDL_Surface * screen);
void animerminimap(minimap m, SDL_Surface *screen, int frame);
SDL_Color GetPixel(SDL_Surface *pSurface , int x,int y); 
int collision_pright(SDL_Surface *mask , SDL_Rect posperso ); 
int collision_pleft(SDL_Surface *mask , SDL_Rect posperso ); 
int collision_pup(SDL_Surface *mask , SDL_Rect posperso );
int collision_pdown(SDL_Surface *mask , SDL_Rect posperso );
#endif // MINIMAP_H_INCLUDED
