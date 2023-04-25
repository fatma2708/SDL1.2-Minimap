#include "background.h"

void initBack(background * b,int x,int y){
    b->image=IMG_Load("backg.png");
    
    b->camerasolo.x=0;
    b->camerasolo.y=0;
    b->camerasolo.w=x;
    b->camerasolo.h=y;

    b->camera.x=0;
    b->camera.y=0;
    b->camera.h=y;
    b->camera.w=x/2;

    b->camera2.x=x/2;
    b->camera2.y=0;
    b->camera2.h=y;
    b->camera2.w=x/2;

    
    b->music=Mix_LoadMUS("background resources/music.mp3");
    Mix_PlayMusic(b->music, -1);

}


void aficherBack(background b, SDL_Surface * screen,int x,int y,int np){
    if (np == 1)
    {
        SDL_BlitSurface(b.image,&(b.camerasolo),screen,NULL);
    }
    if (np == 2){
    SDL_Rect pos={x/2,0,x/2,y};
    SDL_Surface *trait;
    trait=IMG_Load("background resources/trait.png");
    SDL_BlitSurface(b.image , &b.camera, screen  , NULL);
    SDL_BlitSurface(b.image,&b.camera2,screen, &pos);
    SDL_BlitSurface(trait,NULL,screen, &pos);
}

}

void scrollingsolo (background * b, int direction, int pasAvancement){
  
       switch (direction)
    {
    case 'R':
        if (b->camerasolo.x <= 4252-(1366)) b->camerasolo.x += pasAvancement ;
        break;
    
    case 'L':
        if (b->camerasolo.x >= 1366/2) b->camerasolo.x -= pasAvancement;
        break;      
    } 
}
void partage_ecran (background * b, int direction, int pasAvancement){
  
       switch (direction)
    {
    case 'R':
        if (b->camera.x <= 4252-(1366/2)) b->camera.x += pasAvancement ;
        break;
    
    case 'L':
        if (b->camera.x >= 1366/2) b->camera.x -= pasAvancement;
        break;    
    } 
}

void partage_ecran2 (background * b, int direction, int pasAvancement){
   
       switch (direction)
    {
    case 'R':
        if (b->camera2.x <= 4252-(1366/2)) b->camera2.x += pasAvancement ;
        break;
    
    case 'L':
        if (b->camera2.x >= 1366/2) b->camera2.x -= pasAvancement;
        break;     
    } 

}
void animer_background(background * b,SDL_Surface * screen)
{
SDL_Surface* spriteSheet =IMG_Load("background resources/aa.png");
    int spriteWidth = 200;
    int spriteHeight = 200;
    int numFrames = 9;
    int frameRate = 1000;  
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    SDL_Rect spriteRect = {0, 0, spriteWidth, spriteHeight};
    int spriteVelX = 1;
    int spriteVelY = 1;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > lastFrameTime + frameRate) {
            currentFrame = (currentFrame + 1) % numFrames;
            lastFrameTime = currentTime;
        }
        spriteRect.x += spriteVelX;
        spriteRect.y += spriteVelY;
        if (spriteRect.x < 0 || spriteRect.x > 2208 - spriteWidth) {
            spriteVelX = -spriteVelX;
        }
        if (spriteRect.y < 0 || spriteRect.y >800- spriteHeight) {
            spriteVelY = -spriteVelY;
        }
        SDL_Rect srcRect = {currentFrame * spriteWidth, 0, spriteWidth, spriteHeight};
        SDL_BlitSurface(spriteSheet, &srcRect, screen, &spriteRect);
        SDL_Flip(screen);
}
void animer_background2(background * b,SDL_Surface * screen)
{
SDL_Surface* spriteSheet =IMG_Load("background resources/aa.png");
    int spriteWidth = 200;
    int spriteHeight = 200;
    int numFrames = 9;
    int frameRate = 1000;  
    int currentFrame = 0;
    Uint32 lastFrameTime = 0;
    SDL_Rect spriteRect = {683, 0, spriteWidth, spriteHeight};
    int spriteVelX = 1;
    int spriteVelY = 1;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime > lastFrameTime + frameRate) {
            currentFrame = (currentFrame + 1) % numFrames;
            lastFrameTime = currentTime;
        }
        spriteRect.x += spriteVelX;
        spriteRect.y += spriteVelY;
        if (spriteRect.x < 0 || spriteRect.x > 2208 - spriteWidth) {
            spriteVelX = -spriteVelX;
        }
        if (spriteRect.y < 0 || spriteRect.y >800- spriteHeight) {
            spriteVelY = -spriteVelY;
        }
        SDL_Rect srcRect = {currentFrame * spriteWidth, 0, spriteWidth, spriteHeight};
        SDL_BlitSurface(spriteSheet, &srcRect, screen, &spriteRect);
        SDL_Flip(screen);
}
