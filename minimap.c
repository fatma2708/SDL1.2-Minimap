#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "minimap.h"
#include <math.h>


void init_map (minimap *m)
{ m -> map = IMG_Load("minimap.png");
  m-> miniperso = IMG_Load("miniperso.png");
  m->positionmap.x =230;
  m->positionmap.y =19;
  m->posminiperso.x =250;
  m->posminiperso.y =800;
}


void MAJMinimap(SDL_Rect posperso,  minimap * m, SDL_Rect camera, int redimensionnement)
{
  SDL_Rect pospersoABS;
  pospersoABS.x = 250;
  pospersoABS.y = 600;
  pospersoABS.x = posperso.x + camera.x;
  pospersoABS.y = posperso.y + camera.y;
    m->posminiperso.x = (pospersoABS.x * redimensionnement / 100)+239;
    m->posminiperso.y = (pospersoABS.y * redimensionnement / 100)+29;
}

void afficherminimap (minimap m, SDL_Surface * screen)
{
  SDL_BlitSurface(m.map,NULL,screen,&m.positionmap);
  SDL_BlitSurface(m.miniperso,NULL,screen,&m.posminiperso);
}
void animerminimap(minimap m, SDL_Surface *screen, int frame) 
{

    SDL_Color rougefonce = {255, 0, 0};
    SDL_Color rougeclair = {255, 100, 100};


    Uint8 alpha = (Uint8) (127 * (cos(frame * 0.05) + 1));  
    int dot_x = screen->w -1000; 
    int dot_y = 200;

    SDL_Surface* dot = SDL_CreateRGBSurface(0, 20, 20, 32, 0, 0, 0, 0);
    SDL_FillRect(dot, NULL, SDL_MapRGBA(screen->format, rougefonce.r, rougefonce.g, rougefonce.b, alpha));


    SDL_Rect inner_rect = {4, 4, 12, 12};
    SDL_FillRect(dot, &inner_rect, SDL_MapRGBA(screen->format, rougeclair.r, rougeclair.g, rougeclair.b, alpha));


    if ((frame / 30) % 2 == 0) {
        SDL_FillRect(dot, NULL, SDL_MapRGBA(screen->format, rougeclair.r, rougeclair.g, rougeclair.b, alpha));
    }

    SDL_BlitSurface(dot, NULL, screen, &(SDL_Rect){dot_x,dot_y, 0, 0});
    SDL_FreeSurface(dot);
}



void initialiser_temps(temps *t)
{
 t->texte = NULL; 
 t->position.x=100;
   t->position.y=10;
     t->police = NULL;
  t->police = TTF_OpenFont("police.TTF", 40);
    strcpy( t->entree,"");
(t->secondesEcoulees)=0;
time(&(t->t1)); 


}


void afficher_temps(temps *t,SDL_Surface *ecran)
{	
SDL_Color noir= {0, 0, 0};

    	time(&(t->t2));

		t->secondesEcoulees = t->t2 - t->t1;

        t->min=((t->secondesEcoulees/60)%60);
	t->sec= ((t->secondesEcoulees)%60);

	 sprintf(t->entree,"%02d:%02d",t->min,t->sec);
        t->texte = TTF_RenderUTF8_Solid(t->police, t->entree, noir);
      

SDL_BlitSurface(t->texte, NULL, ecran, &(t->position)); 

  


 
	
}

void free_temps(temps *t,SDL_Surface *ecran)
{
 SDL_FreeSurface(t->texte);
 TTF_CloseFont(t->police);
}




SDL_Color GetPixel(SDL_Surface *pSurface ,int x,int y)
{
    SDL_Color color;
    Uint32 col=0;
    char *pPosition = (char *) pSurface -> pixels;
    pPosition+=(pSurface->pitch *y);
    pPosition+=(pSurface ->format->BytesPerPixel *x);
    memcpy (&col,pPosition,pSurface ->format ->BytesPerPixel);

SDL_GetRGB(col,pSurface -> format,&color.r ,&color.g ,&color.b);
return (color);
}



int collision_pright(SDL_Surface *mask , SDL_Rect posperso)
{  
SDL_Color col,colp;
SDL_Rect pos[8];
int collision = 0;
int i,w,h;

col.r=0;
col.g=0;
col.b=0;

w=122;
h=225;


pos[5].x = posperso.x+w ;
pos[5].y = posperso.y;



pos[6].x = posperso.x +w;
pos[6].y = posperso.y+ h/2;



pos[7].x = posperso.x+w;
pos[7].y = posperso.y +h;



for (i =5;(i < 8)&&(collision == 0); i++)
{
    colp = GetPixel(mask,pos[i].x ,pos[i].y);
    if((col.r==colp.r) && (col.g == colp.g) && (col.b ==colp.b))
    collision = 1;
}


return (collision);
}



int collision_pleft(SDL_Surface *mask, SDL_Rect posperso)
{
SDL_Color col,colp;
SDL_Rect pos[8];
int collision = 0;
int i,w,h;
col.r=0;
col.g=0;
col.b=0;


w=122;
h=225;


pos[0].x = posperso.x;
pos[0].y = posperso.y;

pos[1].x = posperso.x;
pos[1].y = posperso.y + h /2;

pos[2].x = posperso.x;
pos[2].y = posperso.y + h;


for (i =0;(i < 3)&&(collision == 0); i++)
{
col = GetPixel(mask,pos[i].x ,pos[i].y);
if((col.r==colp.r) && (col.g == colp.g) && (col.b ==colp.b))
collision = 1;
}
    return (collision);
}


int collision_pup(SDL_Surface *mask, SDL_Rect posperso)
{
SDL_Color col,colp;
SDL_Rect pos;
int collision = 0;
int i,w,h;
col.r=0;
col.g=0;
col.b=0;


w=122;
h=225;



pos.x = posperso.x + w/2;
pos.y = posperso.y;

col = GetPixel(mask,pos.x ,pos.y);


if((col.r==colp.r) && (col.g == colp.g) && (col.b ==colp.b))   collision = 1;


return (collision);
}




int collision_pdown(SDL_Surface *mask, SDL_Rect posperso)
{
SDL_Color col,colp;
SDL_Rect pos;
int collision = 0;
int i,w,h;
col.r=0;
col.g=0;
col.b=0;


w=122;
h=225;


pos.x = posperso.x+ w /2;
pos.y = posperso.y +h;


col = GetPixel(mask,pos.x ,pos.y);
if (col.r == 0 && col.g == 0 && col.b == 0) { 
        collision = 1;
    }
 


return (collision);
}




