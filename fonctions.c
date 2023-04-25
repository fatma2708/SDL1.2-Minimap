#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "fonctions.h"


void initialiser_enigme(enigme *e,char *nomfichier)
{
	int i=0,q;
	FILE* f;
	q=rand()%4; 
	f=fopen(nomfichier,"r");
	if(f==NULL)
		printf("Erreur d ouvrir fichier d enigme\n");
	else
	{
		while(i<=q)
		{
		fgets(e->ch,300,f);
		fscanf(f,"%s %s %s %s\n",e->ch1,e->ch2,e->ch3,e->ch4);
		i++;
		}
		fclose(f);
	}
	for(i=0;i<9;i++)
	{
		sprintf(e->te[i].url,"e/eni%d.png",i+1);
		e->te[i].img=IMG_Load(e->te[i].url);
		if (e->te[i].img == NULL)
		{
			printf("unable to load enigme image%d %s \n",i+1,SDL_GetError());
			return ;
		}
		e->te[i].pos_img_ecran.x=0;
		e->te[i].pos_img_ecran.y=0;
		e->te[i].pos_img_affiche.x=0;
		e->te[i].pos_img_affiche.y=0;
		e->te[i].pos_img_affiche.h=825;
		e->te[i].pos_img_affiche.w=1670;
	}
	e->t.police=TTF_OpenFont("Ubuntu-B.ttf",30);
	e->t.color_txt.r=255;
	e->t.color_txt.g=239;
	e->t.color_txt.b=97;
	e->t.txt=TTF_RenderText_Blended(e->t.police,e->ch,e->t.color_txt);
	e->t.pos_txt.x=(1670-e->t.txt->w)/2;
	e->t.pos_txt.y=200;
	e->t1.police=TTF_OpenFont("Ubuntu-B.ttf",20);
	e->t1.color_txt.r=0;
	e->t1.color_txt.g=0;
	e->t1.color_txt.b=0;
	e->t1.txt=TTF_RenderText_Blended(e->t1.police,e->ch1,e->t1.color_txt);
	e->t1.pos_txt.x=(1670-e->t1.txt->w)/2-20;
	e->t1.pos_txt.y=440;
	e->t2.police=TTF_OpenFont("Ubuntu-B.ttf",20);
	e->t2.color_txt.r=0;
	e->t2.color_txt.g=0;
	e->t2.color_txt.b=0;
	e->t2.txt=TTF_RenderText_Blended(e->t2.police,e->ch2,e->t2.color_txt);
	e->t2.pos_txt.x=(1670-e->t2.txt->w)/2-20;
	e->t2.pos_txt.y=560;
	e->t3.police=TTF_OpenFont("Ubuntu-B.ttf",20);
	e->t3.color_txt.r=0;
	e->t3.color_txt.g=0;
	e->t3.color_txt.b=0;
	e->t3.txt=TTF_RenderText_Blended(e->t3.police,e->ch3,e->t3.color_txt);
	e->t3.pos_txt.x=(1670-e->t3.txt->w)/2-20;
	e->t3.pos_txt.y=680;
	e->r=-999;
	e->pos=0;
	e->quit=0;
}

void afficher_enigme(SDL_Surface *screen,enigme e)
{
	SDL_BlitSurface(e.te[e.pos].img, &e.te[e.pos].pos_img_affiche, screen, &e.te[e.pos].pos_img_ecran);
	SDL_BlitSurface(e.t.txt,NULL,screen,&e.t.pos_txt);
	SDL_BlitSurface(e.t1.txt,NULL,screen,&e.t1.pos_txt);
	SDL_BlitSurface(e.t2.txt,NULL,screen,&e.t2.pos_txt);
	SDL_BlitSurface(e.t3.txt,NULL,screen,&e.t3.pos_txt);
}

void liberer_enigme(enigme e)
{
	int i;
	for(i=0;i<9;i++)
		SDL_FreeSurface(e.te[i].img);
	TTF_CloseFont(e.t.police);
	TTF_CloseFont(e.t1.police);
	TTF_CloseFont(e.t2.police);
	TTF_CloseFont(e.t3.police);
}
void animer_enigme(enigme *e)
{
	if(e->r!=-999)
	{
		e->quit=1;
		if(e->r==0)
			e->pos+=6;
		else
			e->pos+=3;
	}
}
int enigme_fichier (SDL_Surface *screen)
{
	int boucle=1,input=-1;
	SDL_Event event;
	enigme e;
	 
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE| SDL_DOUBLEBUF);
	initialiser_enigme(&e,"enigme.txt");
	while(boucle)
	{
		
				
					if(e.quit)
					{
						SDL_Delay(300);
						boucle=0;
					}
					else
					{
                                           animer_enigme(&e);	
                                            afficher_enigme(screen,e);
                                        }
					
		
		 while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT: 
				boucle=0;
			break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					boucle=0;break;
					case SDLK_RETURN:
					input=1;break;
					case SDLK_DOWN:
					input=3;break;
					case SDLK_UP:
					input=2;break;
					case SDLK_a:
					input=10;break;
					case SDLK_b:
					input=11;break;
					case SDLK_c:
					input=12;break;
				}
			break;
			case SDL_MOUSEMOTION: 
				if(event.motion.y<=490 && event.motion.y>=412 && event.motion.x<=1136 && event.motion.x>=506 )
						input=41; 
				if(event.motion.y<=610 && event.motion.y>=532 && event.motion.x<=1136 && event.motion.x>=506 )
						input=42; 
				if(event.motion.y<=730 && event.motion.y>=652 && event.motion.x<=1136 && event.motion.x>=506 )
						input=43;
			break;
			case SDL_MOUSEBUTTONDOWN: 
				
				if(event.button.button==SDL_BUTTON_LEFT && event.motion.y<=490 && event.motion.y>=412 && event.motion.x<=1136 && event.motion.x>=506)
						input=10; 
				if(event.button.button==SDL_BUTTON_LEFT && event.motion.y<=610 && event.motion.y>=532 && event.motion.x<=1136 && event.motion.x>=506)
						input=11; 
				if(event.button.button==SDL_BUTTON_LEFT && event.motion.y<=730 && event.motion.y>=652 && event.motion.x<=1136 && event.motion.x>=506)
						input=12;
				
			break;
			}
		}
		
		
		
			switch(input)
			{
				case 1:
				switch(e.pos)
				{
					case 0:
						e.r=strcmp(e.ch1,e.ch4);
					break;
					case 1:
						e.r=strcmp(e.ch2,e.ch4);
					break;
					case 2:
						e.r=strcmp(e.ch3,e.ch4);
					break;
				}
				break;
				case 2:
				if(e.pos>0)
					e.pos--;
				else
					e.pos=2;
				break;
				case 3:
				if(e.pos<2)
					e.pos++;
				else
					e.pos=0;
				break;
				case 10:
				e.r=strcmp(e.ch1,e.ch4);
				e.pos=0;
				break;
				case 11:
				e.r=strcmp(e.ch2,e.ch4);
				e.pos=1;
				break;
				case 12:
				e.r=strcmp(e.ch3,e.ch4);
				e.pos=2;
				break;
				case 41:
				e.pos=0;
				break;
				case 42:
				e.pos=1;
				break;
				case 43:
				e.pos=2;
				break;
			}
		
		input=-1;
		SDL_Flip(screen);
	}
	liberer_enigme(e);
	return 0;
}

