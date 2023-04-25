#include <SDL/SDL.h>
#include "zoom.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>


void show_good(SDL_Surface *screen) {
    float zoom = 0.05;
    SDL_Rect pos;
    SDL_Surface *surface;
	SDL_Surface *bg;
	bg = IMG_Load("bg.jpg");
    TTF_Font * font = TTF_OpenFont("Donalia.ttf", 200);
	SDL_Color color = {60,60,60};
    for (int i = 0; i < 20; i++) {
        zoom += 0.05;
        
		surface = TTF_RenderText_Blended(font, "GOOD", color);
		surface = zoomSurface(surface,zoom,zoom,1);
		pos.x = screen->w/2 - surface->w/2;
		pos.y = screen->h/2 - surface->h/2;
		SDL_BlitSurface(bg, NULL, screen, NULL);
		SDL_BlitSurface(surface, NULL, screen, &pos);
        SDL_FreeSurface(surface);
        SDL_Flip(screen);
        SDL_Delay(10);
    }
}

void rotate_hard_luck(SDL_Surface *screen) {
    
    float angle = 0;
    SDL_Rect pos;
    SDL_Surface *surface;
	SDL_Surface *bg;
	bg = IMG_Load("bg.jpg");
    TTF_Font * font = TTF_OpenFont("Donalia.ttf", 150);
	SDL_Color color = {60,60,60};
    while (angle<360) {
        angle+=6;
        
		surface = TTF_RenderText_Blended(font, "Hard Luck", color);
		surface = rotozoomSurface(surface,angle,1,1);
		pos.x = screen->w/2 - surface->w/2;
		pos.y = screen->h/2 - surface->h/2;
		SDL_BlitSurface(bg, NULL, screen, NULL);
		SDL_BlitSurface(surface, NULL, screen, &pos);
        SDL_FreeSurface(surface);
        SDL_Flip(screen);
        SDL_Delay(10);
    }
}


