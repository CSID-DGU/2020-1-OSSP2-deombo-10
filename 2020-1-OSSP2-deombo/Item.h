#pragma once

#include <string>
#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <vector>

#include "define.h"
#include "helpers.h"

using namespace std;

typedef struct items
{
public:
  items(int x, int y , int ply_x, int ply_y )
  {
    move_x = x;
    move_y = y;
    offset.x = ply_x;
    offset.y = ply_y;
  }

  int move_x, move_y;                     // item의 방향성
  SDL_Rect offset;                      // item의 위치
}items;

class Health_item
{
public:
  SDL_Surface *item;

  ~Health_item();
  void add_itm(int x, int y, int ply_x, int ply_y);                                      //x,y는 item 방향성, ply_x,y는 item의 현재 위치
  void item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip);  // item들 그리기
  void control_item();

  vector<items> itm;
};
