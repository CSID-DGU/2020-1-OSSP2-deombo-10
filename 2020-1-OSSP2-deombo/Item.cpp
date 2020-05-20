#include "Item.h"

void Item::add_itm(int x, int y, int ply_x, int ply_y)
{
  item = load_image("assets/tem_li.png");
  items tmp(x,y,ply_x,ply_y);
  itm.push_back(tmp);
}

void Item::item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip)  // item들 그리기
{
  for(vector<items>::iterator iter = itm.begin(); iter!= itm.end(); iter++)
  {
    SDL_BlitSurface( item, clip, destination, &(*iter).offset);
  }
}

void Item::control_item()
{
  vector<items> temp;
  for(vector<items>::iterator iter = itm.begin(); iter != itm.end(); iter++)
  {
    items tmp((*iter).move_x,(*iter).move_y,(*iter).offset.x,(*iter).offset.y + 2);
    if( 0 < tmp.offset.x + 9 && tmp.offset.x< SCREEN_WIDTH && -5 <= tmp.offset.y  && tmp.offset.y < SCREEN_HEIGHT)
      temp.push_back(tmp);
  }

  itm = temp;
}

Item::~Item()
{
    SDL_FreeSurface(item);
}
