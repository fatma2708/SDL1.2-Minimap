#include "enigme_fichier.h"
#include "zoom.h"


void init_ef(enigme_f * e) {
  char reponses[4][16];
  char question[32];
  char text[32];
  int a,b,type;
  a = rand()%20 - 10;
  b = rand()%20 - 10;
  type=rand()%3;
  if(type==0)
	{sprintf(question,"%d + %d",a,b);
	sprintf(reponses[0],"%d",a+b);}
  if(type==1)
  {sprintf(question,"%d - %d",a,b);
	sprintf(reponses[0],"%d",a-b);}
  if(type==2)
  {sprintf(question,"%d * %d",a,b);
	sprintf(reponses[0],"%d",a*b);
	sprintf(reponses[1],"%d",rand()%50);
	sprintf(reponses[2],"%d",rand()%200 -100);
	sprintf(reponses[3],"%d",rand()%200 -100);}
	else{
	sprintf(reponses[1],"%d",rand()%20 -10);
	sprintf(reponses[2],"%d",rand()%20 -10);
	sprintf(reponses[3],"%d",rand()%20 -10);}
	
  e -> bg = IMG_Load("bg.jpg");
  TTF_Font * font = TTF_OpenFont("Donalia.ttf", 60);
  SDL_Color color = {60,60,60};
  e -> question = TTF_RenderText_Blended(font, question, color);
  e -> corr = rand() % 4;
  sprintf(question, "%s", reponses[e -> corr]);
  sprintf(reponses[e -> corr], "%s", reponses[0]);
  sprintf(reponses[0], "%s", question);
  for (int i = 0; i < 4; i++) {
    sprintf(text, "%c %s", 65 + i, reponses[i]);
    e -> reponses[i] = TTF_RenderText_Solid(font, text, color);
    e -> pos[i].x = 100;
    e -> pos[i].y = 200 + 100 * i;
    e -> pos[i].w = e -> reponses[i] -> w;
    e -> pos[i].h = 20;
  }
}
void afficher_e(enigme_f e, SDL_Surface * screen) {
  SDL_Rect pos;
  pos.x = 100;
  pos.y = 100;
  SDL_BlitSurface(e.bg, NULL, screen, NULL);
  SDL_BlitSurface(e.question, NULL, screen, & pos);
  for (int i = 0; i < 4; i++) {
    SDL_BlitSurface(e.reponses[i], NULL, screen, & e.pos[i]);
  }
  e.pos[3].y += 100;
  SDL_Flip(screen);
}
int choix(enigme_f e) {
  Uint8 * keystate = SDL_GetKeyState(NULL);
  if (keystate[SDLK_ESCAPE]) return 5;
  if (keystate[SDLK_a]) return 0;
  if (keystate[SDLK_b]) return 1;
  if (keystate[SDLK_c]) return 2;
  if (keystate[SDLK_d]) return 3;
  int x, y;
  Uint32 buttons = SDL_GetMouseState( & x, & y);
  SDL_Rect pos;
  pos.w = 5;
  pos.h = 5;
  pos.x = x;
  pos.y = y;
  for (int i = 0; i < 4; i++) {
    e.pos[i].y += 50;
    if ((buttons & SDL_BUTTON_LMASK) != 0)
      if (collision(pos, e.pos[i]))
        return i;
  }
  return -1;
}

int enigme_genere(SDL_Surface * screen) {
screen =SDL_SetVideoMode(1000,765,32,SDL_SWSURFACE);
SDL_Delay(500);
  enigme_f e;
  init_ef( & e);
  int b = 0;
  while (b == 0) {
    SDL_PumpEvents();
    if (choix(e) == -1) {
      afficher_e(e, screen);
    } else {
      if (choix(e) == e.corr) {
	show_good(screen);
        SDL_Flip(screen);
        SDL_Delay(1500);
        return 1;
      } else rotate_hard_luck(screen);
      b = 1;
      SDL_Flip(screen);
      SDL_Delay(1500);
      return 0;
    }
  }
  return 0;
}
