#ifndef _ES_H_
#define _ES_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>


enum state_es{move,run,attack,dying,dead};
typedef struct
{
enum state_es state;
SDL_Rect pos;
SDL_Rect sprite;
int vie;
SDL_Surface *image;
int sprite_count[4];
int sprite_n;//current sprite
int d;//direction
int speed;
}ES;

void init_es(ES *p);
void afficher_es(ES p,SDL_Surface *screen);
void animer_es(ES *p);
void mouvement_aleatoire(ES *p);
int change_state_es(ES *p, SDL_Rect pos,int h);

#endif
