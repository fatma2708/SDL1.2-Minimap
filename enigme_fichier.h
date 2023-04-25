#ifndef _ENIGME_FICHIER_H_
#define _ENIGME_FICHIER_H_
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "bounding_box.h"
#include <time.h>

typedef struct{
SDL_Surface *bg;
SDL_Surface *question;
SDL_Surface *reponses[4];
SDL_Rect pos[4];
int corr;//réponse correcte
SDL_Surface *won;
SDL_Surface *lost;
}enigme_f;


int enigme_genere(SDL_Surface *screen);

#endif
