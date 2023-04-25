#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#define SCREEN_H 825
#define SCREEN_W 1670
typedef struct{
	char url[20];
	SDL_Rect pos_img_affiche;
	SDL_Rect pos_img_ecran;
	SDL_Surface *img;
}image;
typedef struct
{
	SDL_Surface *txt;
	SDL_Rect pos_txt;
	SDL_Colour color_txt;
	TTF_Font *police;
}texte;
typedef struct{
	image te[9];
	texte t,t1,t2,t3;
	char ch[300],ch1[20],ch2[20],ch3[20],ch4[20];
	int r,pos,quit;
}enigme;
void initialiser_enigme(enigme *e,char *nomfichier);
void afficher_enigme(SDL_Surface *screen,enigme e);
void liberer_enigme(enigme e);
void animer_enigme(enigme *e);
int enigme_fichier (SDL_Surface *screen);


#endif
