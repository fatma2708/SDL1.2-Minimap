#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <ctype.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
#include "Personne.h"
#include "minimap.h"
#include "ES.h"
#include "bounding_box.h"
#include "fonctions.h"
#include "enigme_fichier.h"

int main(int argc, char const *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	srand(time(NULL));//random fl enigmes
//-----------partie declaration-------//
    int continuer=1;
    background b;
    int direction=0,vitesse=0,direction2=0,vitesse2=0;
    SDL_Surface *screen,*mask;
    SDL_Event event;
    int resx=1366,resy=610;
    int np=2;
    //perso
	Personne p,p1;
	initPerso(&p);
	initPerso(&p1);
	p1.position.x=650;
	int up=0, up1=0,acceleration=0,deceleration=0,acceleration1=0,deceleration1=0;
	Uint32 t_prev,t_fin , dt ;
	//minimap
	temps t;
	minimap m;
	initialiser_temps(&t);
	init_map(&m);
	int frame;
	mask=IMG_Load("mask.bmp");
	int collision_bg_p2=0;
	//entite
	ES es1;
	init_es(&es1);
	int collision_entite=0;
//----------partie initialisation------//
    screen=SDL_SetVideoMode (resx,resy,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1) printf("%s",Mix_GetError());
    SDL_WM_SetCaption("background\t1",NULL);
    initBack(&b,resx,resy);
    //SDL_EnableKeyRepeat(30,30);

while (continuer) // ------boucle de jeu --------//
{
t_prev = SDL_GetTicks();
//------partie input--------//
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_KEYDOWN:    
            switch (event.key.keysym.sym)
            {
                case SDLK_RIGHT:
                if (collision_pright(mask,p.position)==0){
					p.direction=0;
					p.vitesse=2;
                    direction='R';
                    vitesse++;}
                    break;
                case SDLK_LEFT:
                if (collision_pleft(mask,p.position)==0)   {
                	p.direction=1;
        			p.vitesse=2;
                    direction='L';
                    vitesse++;}
                    break;
                case SDLK_UP:
                	up=1;
                    direction='U';
                    vitesse++;
                    break;
                case SDLK_DOWN:
                    direction='D';
                    vitesse++;
                    break;  
                case SDLK_d:
                if (collision_pright(mask,p1.position)==0)   {
					p1.direction=0;
					p1.vitesse=2;
                    direction2='R';
                    vitesse2++;}
                    break;
                case SDLK_q:
                if (collision_pleft(mask,p1.position)==0)   {
					p1.direction=1;
					p1.vitesse=2;
                    direction2='L';
                    vitesse2++;}
                    break;
                case SDLK_z:
                	up1=1;
                    direction2='U';
                    vitesse2++;
                    break;
                case SDLK_s:
                    direction2='D';
                    vitesse2++;
                    break;
                case SDLK_p:
					acceleration=1;
					break;
				case SDLK_o:
					deceleration=1;
					break;
				    case SDLK_f:
					acceleration1=1;
					break;
				case SDLK_g:
					deceleration1=1;
					break;
            }
        break;
        
        case SDL_KEYUP:
			switch (event.key.keysym.sym)//lbouton appuyé?
				{
				case  SDLK_RIGHT:
						  p.vitesse=0;
					break;

				case  SDLK_LEFT:        
					p.vitesse=0;
					break; 

				case SDLK_UP:
					up=0;
					break; 

				case SDLK_p:
					acceleration=0;
				break;

				case SDLK_o:
					deceleration=0;
					break; 



					case  SDLK_d:
						  p1.vitesse=0;
					break;

				case  SDLK_q:        
					p1.vitesse=0;
					break; 

				case SDLK_z:
					up1=0;
					break; 

				case SDLK_f:
					acceleration1=0;
				break;

				case SDLK_g:
					deceleration1=0;
					break;             
				
				}
            if ((event.key.keysym.sym==SDLK_RIGHT) || (event.key.keysym.sym==SDLK_LEFT) || (event.key.keysym.sym==SDLK_UP) || (event.key.keysym.sym==SDLK_DOWN))
            {
            vitesse=0;
            }else
            vitesse2=0;
        break;
        }
    }

//------partie update------//
if( np == 1)
scrollingsolo(&b,direction,vitesse);
animer_background(&b,screen);
if ( np == 2){
partage_ecran(&b,direction,vitesse);  
partage_ecran2(&b,direction2,vitesse2);
animer_background(&b,screen);
animer_background2(&b,screen);

//------perso------//
t_fin=SDL_GetTicks();
dt=t_fin - t_prev ;

deplacerPerso(&p,dt);
animerPerso(&p);

deplacerPerso(&p1,dt);
animerPerso(&p1);

if (up==1) saut(&p);
p.position.y = p.position.y   + p.vitesse_saut ;
p.vitesse_saut = p.vitesse_saut + 10 ;
if (p.position.y>=300)
{   
    p.position.y=300;
    p.vitesse_saut=0;
}

if (up1==1) saut(&p1);
p1.position.y = p1.position.y   + p1.vitesse_saut ;
p1.vitesse_saut = p1.vitesse_saut + 10 ;
if (p1.position.y>=300)
{   
    p1.position.y=300;
    p1.vitesse_saut=0;
}

}

if(p.position.x<0) p.position.x=0;
if(p1.position.x<650) p1.position.x=650;
if(p.position.x>450) p.position.x=450;
if(p1.position.x>1150) p1.position.x=1150;
//minimap
MAJMinimap(p.position,&m,b.camera,40);
frame = SDL_GetTicks();
animerminimap(m, screen, frame);
//enigmes
p.position.x+=30;
if(collision_entite==0)
	if(collision(es1.pos,p.position)==1)
		{enigme_fichier(screen);
		screen=SDL_SetVideoMode (resx,resy,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
		collision_entite=1;}
if(collision_bg_p2==0)
	if(collision_pright(mask,p1.position)==1)
		{enigme_genere(screen);
		screen=SDL_SetVideoMode (resx,resy,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
		collision_bg_p2=1;}



p.position.x-=30;
//------partie affichage------//
aficherBack(b,screen,resx,resy,np);
afficherminimap(m,screen);
afficher_temps(&t,screen);
afficher_es(es1,screen);
animer_es(&es1);
change_state_es(&es1,p.position,1);

afficherPerso(p,screen);
afficherPerso(p1,screen);
SDL_Flip(screen);
SDL_Delay(40);
}

    return 0;
}
