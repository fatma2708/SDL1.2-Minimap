#include "ES.h"

#include "bounding_box.h"

void init_es(ES * p) //initialisation de tout les attributs
{
  ( * p).d = 0;
  ( * p).vie = 100;
  ( * p).pos.x = 500;
  ( * p).pos.y = 340;
  ( * p).sprite.x = 0;
  ( * p).sprite.y = 0;
  ( * p).state = 0;
  ( * p).sprite_n = 0;
  ( * p).speed = 10;
  ( * p).image = IMG_Load("spritesheet.png");
  ( * p).pos.w = ( * p).image -> w/4;
  ( * p).pos.h = ( * p).image -> h/2;
}
void afficher_es(ES p, SDL_Surface * screen) {
    SDL_BlitSurface(p.image, & p.sprite, screen, & p.pos);
}
void animer_es(ES * p) //change l image à afficher
{
	( * p).sprite.w = ( * p).image-> w/4;
    ( * p).sprite.h = ( * p).image-> h/2;
    ( * p).sprite_n++;
    if (( * p).sprite_n >= 3) {
      ( * p).sprite_n = 0;}
    ( * p).sprite.x = ( * p).sprite.w * ( * p).sprite_n;
    ( * p).sprite.y = ( * p).sprite.h * ( * p).d;
}
void mouvement_aleatoire(ES *p)
{
if (( * p).pos.x % 50<5) ( * p).d=rand()%2;
if(( * p).pos.x<50) ( * p).d=1;
if(( * p).pos.x>600) ( * p).d=0;
if (( * p).d==0) ( * p).pos.x-=10;
else ( * p).pos.x+=10;
}
int change_state_es(ES *p, SDL_Rect pos,int h)
{    
if ((*p).vie <= 0) {
        (*p).state = 3;
    }
   
	if ((*p).state != 3) {
        if ((*p).state == 1) {
            if ((*p).pos.x > pos.x) {
                (*p).pos.x -= 20; 
            }
            else {
                (*p).pos.x += 20; 
            }
        }
        else if ((*p).state == 0) {
            if (rand() % 10 == 1) {
                (*p).d = rand() % 2;
            }
            if ((*p).d == 1) {
                (*p).pos.x += 5; 
            }
            else {
                (*p).pos.x -= 5; 
            }
            if ((*p).pos.x < 50) {
                (*p).d = 1;
            }
            if ((*p).pos.x > 700) {
                (*p).d = 0;
            }
        }

if(h<=0) 
(*p).state = 0; 
	else{
        if (abs((*p).pos.x - pos.x - pos.w) < 200 && (*p).pos.x > pos.x) {
            (*p).state = 1;
            (*p).d = 0;
        }
        else if (abs(pos.x - (*p).pos.x - (*p).pos.w) < 200 && (*p).pos.x < pos.x) {
            (*p).state = 1;
            (*p).d = 1;
        }
        else {
            (*p).state = 0;
        }
        if (abs((*p).pos.x - pos.x - pos.w) < 50 && (*p).pos.x > pos.x) {
            (*p).state = 2;
            (*p).d = 0;
			return 1;
        }
        else if (abs(pos.x - (*p).pos.x - (*p).pos.w) < 50 && (*p).pos.x < pos.x) {
            (*p).state = 2;
            (*p).d = 1;
			return 1;
        }
		}
	}


return 0;
}
   
