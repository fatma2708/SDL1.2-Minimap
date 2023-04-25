#include "bounding_box.h"

int in_bounds(SDL_Rect x1,SDL_Rect x2)//testi ken x1 f west x2
{
return(x1.x>=x2.x)&&(x1.x<=x2.x+x2.w)&&((x1.y>=x2.y)&&(x1.y<=x2.y+x2.h)||((x1.y<=x2.y)&&(x1.y+x2.h>=x2.y)));
}
int collision(SDL_Rect x1,SDL_Rect x2)//testi ken bin x1 w x2 fama collision wale
{
return in_bounds(x1,x2)||in_bounds(x2,x1);
}
