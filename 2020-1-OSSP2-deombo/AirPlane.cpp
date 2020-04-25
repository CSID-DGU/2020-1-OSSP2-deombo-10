#include "AirPlane.h"

void Item::add_itm(int x, int y, int ply_x, int ply_y)
{
  item = load_image("assets/tem_li.png");
  SDL_SetColorKey(item, SDL_SRCCOLORKEY,SDL_MapRGB(item->format,0,0,0));
  items tmp(x,y,ply_x,ply_y);
  itm.push_back(tmp);
}

void Item::item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip)  // item들 그리기
{
  for(vector<items>::iterator iter = itm.begin(); iter!= itm.end(); iter++)
  {
    SDL_BlitSurface( item, clip, destination, &(*iter).item_pos);
  }
}

void Item::control_item()
{
  vector<items> temp;
  for(vector<items>::iterator iter = itm.begin(); iter != itm.end(); iter++)
  {
    items tmp((*iter).move_x,(*iter).move_y,(*iter).item_pos.x,(*iter).item_pos.y + 2);
    if( 0 < tmp.item_pos.x + 9 && tmp.item_pos.x< SCREEN_WIDTH && -5 <= tmp.item_pos.y  && tmp.item_pos.y < SCREEN_HEIGHT)
      temp.push_back(tmp);
  }

  itm = temp;
}

Item::~Item()
{
    SDL_FreeSurface(item);
}

void Item2::add_itm(int x, int y, int ply_x, int ply_y)
{
  item = load_image("assets/tem_sa.png");
  SDL_SetColorKey(item, SDL_SRCCOLORKEY,SDL_MapRGB(item->format,0,0,0));
  items tmp(x, y,ply_x,ply_y);
  itm.push_back(tmp);
}

void Item2::item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip)  // item들 그리기
{
  for(vector<items>::iterator iter = itm.begin(); iter!= itm.end(); iter++)
  {
    SDL_BlitSurface( item, clip, destination, &(*iter).item_pos);
  }
}

void Item2::control_item()
{
  vector<items> temp;
  for(vector<items>::iterator iter = itm.begin(); iter != itm.end(); iter++)
  {
    items tmp((*iter).move_x,(*iter).move_y,(*iter).item_pos.x,(*iter).item_pos.y + 2);
    if( 0 < tmp.item_pos.x + 9 && tmp.item_pos.x< SCREEN_WIDTH && -5 <= tmp.item_pos.y  && tmp.item_pos.y < SCREEN_HEIGHT)
      temp.push_back(tmp);
  }

  itm = temp;
}

Item2::~Item2()
{
    SDL_FreeSurface(item);
}

void Item3::add_itm(int x, int y, int ply_x, int ply_y)
{
  item = load_image("assets/tem_sh.png");
  SDL_SetColorKey(item, SDL_SRCCOLORKEY,SDL_MapRGB(item->format,0,0,0));
  items tmp(x,y,ply_x,ply_y);
  itm.push_back(tmp);
}

void Item3::item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip)  // item들 그리기
{
  for(vector<items>::iterator iter = itm.begin(); iter!= itm.end(); iter++)
  {
    SDL_BlitSurface( item, clip, destination, &(*iter).item_pos);
  }
}

void Item3::control_item()
{
  vector<items> temp;
  for(vector<items>::iterator iter = itm.begin(); iter != itm.end(); iter++)
  {
    items tmp((*iter).move_x,(*iter).move_y,(*iter).item_pos.x,(*iter).item_pos.y + 2);
    if( 0 < tmp.item_pos.x + 9 && tmp.item_pos.x< SCREEN_WIDTH && -5 <= tmp.item_pos.y  && tmp.item_pos.y < SCREEN_HEIGHT)
      temp.push_back(tmp);
  }

  itm = temp;
}

Item3::~Item3()
{
    SDL_FreeSurface(item);
}

AirPlane::AirPlane()
{
  pos_x = SCREEN_WIDTH / 2;//처음 시작 위치 지정
  pos_y = SCREEN_HEIGHT / 2;//처음 시작 위치 지정

  life = 3;
  SA_count = 3;
  invisible_mode = 0;
}
AirPlane::~AirPlane()
{

}

void AirPlane::shooting(_bullets &player_bullets)
{
  player_bullets.add_blt( 0, -10,pos_x,pos_y - 15);
}

void AirPlane::plane_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface( source, clip, destination, &offset );
}
void AirPlane::control_plane(int x, int y)
{
  if( pos_x + x >= 0 && (pos_x + PLAYER_WIDTH + x) <= SCREEN_WIDTH &&
      pos_y + y >= 0 && (pos_y + PLAYER_HEIGHT + y) < SCREEN_HEIGHT-6)//화면 범위 안
  {
    pos_x += x;
    pos_y += y;
  }
}
void AirPlane::invisible(SDL_Surface *plane)
{
  static int count = 0;                               //투명화 지속 시간
  static int i =0;                                    //투명도

  if(count++ != 60)
  {
    if( count <= 10)
    {
      i += 25;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
    }
    else if( 10 < count && count <= 20)
    {
      i -= 25;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
    }
    else if( 20 < count && count <= 30)
    {
      i += 25;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
    }
    else if( 30 < count && count <= 40)
    {
      i -= 25;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
    }
    else if( 40 < count && count <= 50)
    {
      i += 25;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
    }
    else
    {
      i -= 25;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
    }
  }

  else                                               //불투명화,count 초기화
  {
    count = 0;
    this->invisible_mode = 0;
    SDL_SetAlpha(plane,SDL_SRCALPHA,255);
  }
}

SDL_Rect AirPlane::Get_plane()
{
  return offset;
}

bool AirPlane::Got_shot(_bullets &A,_bullets &B,_bullets &C)
{
  vector<bullets>::iterator iter;
  vector<bullets> tmp;
  vector<bullets> tmp2;
  vector<bullets> tmp3;

  bool flag = false;

  for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
  {
    if((pos_x + 18 < (*iter).bullet_pos.x || pos_y + 20 < (*iter).bullet_pos.y + 5) ||
    ((*iter).bullet_pos.x + 15 < pos_x + 9 || (*iter).bullet_pos.y + 10 < pos_y + 10))//안 맞았을 때
      tmp.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }
  A.blt = tmp;

  if(flag ==true) return flag;

  for(iter = B.blt.begin(); iter != B.blt.end(); iter++)
  {
    if((pos_x + 18 < (*iter).bullet_pos.x || pos_y + 20 < (*iter).bullet_pos.y + 5) ||
    ((*iter).bullet_pos.x + 15 < pos_x + 9 || (*iter).bullet_pos.y + 10 < pos_y + 10))//안 맞았을 때
      tmp2.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }
  B.blt = tmp2;

  if(flag == true) return flag;

  for(iter = C.blt.begin(); iter != C.blt.end(); iter++)
  {
    if((pos_x + 18 < (*iter).bullet_pos.x || pos_y + 20 < (*iter).bullet_pos.y + 5) ||
    ((*iter).bullet_pos.x + 15 < pos_x + 9 || (*iter).bullet_pos.y + 10 < pos_y + 10))//안 맞았을 때
      tmp3.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }
  C.blt = tmp3;
  return flag;
}

bool AirPlane::Got_item(vector<items> I)
{
  vector<items>::iterator iter;
  bool flag = false;

  for(iter = I.begin(); iter != I.end(); iter++)
  {
    if((pos_x + 18 < (*iter).item_pos.x + 9 || pos_y + 20 < (*iter).item_pos.y + 5) ||
    ((*iter).item_pos.x + 18 < pos_x + 9 || (*iter).item_pos.y + 10 < pos_y + 10));//안 맞았을 때
    else                                                                           //맞았을때
    {
      flag = true;
      break;
    }
  }

  return flag;
}

void AirPlane::increaseLife()
{
  life++;
}

void AirPlane::increaseSA()
{
  SA_count++;
}

void AirPlane::Got_shiled(SDL_Surface *plane)
{
  static int count = 0;                               //투명화 지속 시간
  static int i =0;                                    //투명도

  if(count++ != 120)
  {
      i -= 50;
      SDL_SetAlpha(plane,SDL_SRCALPHA,i);
  }
  else                                               //불투명화,count 초기화
  {
    count = 0;
    this->invisible_mode = 0;
    SDL_SetAlpha(plane,SDL_SRCALPHA,255);
  }
}

Enemy_standard_2::Enemy_standard_2(int mode)
{
  enemy = load_image("assets/3.gif");// 비행기 이미지
  //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
  SDL_SetColorKey(enemy, SDL_SRCCOLORKEY,SDL_MapRGB(enemy->format,255,255,255));

  this->mode = mode;
  int y = rand()%100 + 10;
  if(mode == 0) pos_x = -ENEMY_WIDTH;//처음 시작 위치 지정
  else pos_x = SCREEN_WIDTH+ENEMY_WIDTH;
  pos_y = y;//처음 시작 위치 지정
  life = 1;
  count = 0;
}

Enemy_standard_2::~Enemy_standard_2()
{
}

bool Enemy_standard_2::Got_shot(_bullets &A)
{
  vector<bullets>::iterator iter;
  vector<bullets> tmp;

  bool flag = false;

  for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
  {
    if((pos_x + 25 < (*iter).bullet_pos.x + 3 || pos_y + 32 < (*iter).bullet_pos.y) ||
    ((*iter).bullet_pos.x + 13 < pos_x + 10 || (*iter).bullet_pos.y + 32 < pos_y))//안 맞았을 때
      tmp.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }

  A.blt = tmp;

  return flag;
}

bool Enemy_standard_2:: eliminate(int y){
    if(pos_y+32 > y) return true;
    else return false;
}

void Enemy_standard_2::shooting(_bullets &A)
{
  A.add_blt( 0, 5,pos_x + 2,pos_y + 15);
}

void Enemy_standard_2::enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip )
{
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface(enemy, clip, destination, &offset );
}

void Enemy_standard_2::control_plane(_bullets &A)
{
  if(first_exe==true){
    pos = rand()%75+75;
    first_exe=false;
  }
  if(count % 30 == 0 ) this->shooting(A);
  if(count < pos){
      if(mode == 0) pos_x += 3;
      else pos_x -= 3;
  }
  else {
      if(mode == 0){
          pos_x -= 3;
          pos_y += 3;
      }
      else {
          pos_x += 3;
          pos_y += 3;
      }
  }
  count++;
}

SDL_Rect Enemy_standard_2::Get_plane()
{
  offset.x = pos_x;
  offset.y = pos_y;

  return offset;
}

Enemy_standard::Enemy_standard(int mode)
{
  int x = rand()%200+80;
  int y = rand()%200+400;
  this->mode = mode;// 이동경로 mode
  if( mode == 0)
    pos_x = x;// 처음 시작 위치 지정
  else if(mode == 1)
    pos_x = y;
  pos_y = -ENEMY_HEIGHT;//처음 시작 위치 지정
  life = 1;
}

Enemy_standard::~Enemy_standard()
{
}

bool Enemy_standard::Got_shot(_bullets &A)
{
  vector<bullets>::iterator iter;
  vector<bullets> tmp;

  bool flag = false;

  for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
  {
      if((pos_x + 22 < (*iter).bullet_pos.x + 3 || pos_y + 32 < (*iter).bullet_pos.y) ||
      ((*iter).bullet_pos.x + 13 < pos_x + 10 || (*iter).bullet_pos.y + 32 < pos_y))//안 맞았을 때
      tmp.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }

  A.blt = tmp;

  return flag;
}

bool Enemy_standard:: eliminate(int y){
    if(pos_y+32 > y) return true;
    else return false;
}

void Enemy_standard::shooting(_bullets &A)
{
  A.add_blt( 0, 5,pos_x + 2,pos_y + 15);
}

void Enemy_standard::enemy_apply_surface(SDL_Surface* source[], SDL_Surface* destination, SDL_Rect* clip )
{
  int i = count % 4;
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface(source[i], clip, destination, &offset );
}

void Enemy_standard::control_plane(_bullets &enemy)
{//y= 3일 때 속도가 적당.
  if(first_exe == true){
    pos = rand()%75+75;
    first_exe=false;
  }
  if(count % 30 == 0) this->shooting(enemy);
  if(count<pos) pos_y += 3;
  else{
      if(this->mode == 0){
          pos_x+=3;
          pos_y+=3;
      }
      else{
          pos_x-=3;
          pos_y+=3;
      }
  }
  ++count;
}

SDL_Rect Enemy_standard::Get_plane()
{
  offset.x = pos_x;
  offset.y = pos_y;
  return offset;
}

Mini_Boss::Mini_Boss(){
    mini_boss = load_image("assets/boss2.png");// 비행기 이미지
    //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
    SDL_SetColorKey(mini_boss, SDL_SRCCOLORKEY,SDL_MapRGB(mini_boss->format,0,0,0));
    pos_x = 320;// 처음 시작 위치 지정
    pos_y = -MINI_BOSS_HEIGHT;//처음 시작 위치 지정
    life = 30;//has to be changed later (at least 70)
    count = 0;
}

Mini_Boss::~Mini_Boss(){
    this->amount--;
    delete this->mini_boss;
};

bool Mini_Boss::Got_shot(_bullets &A, int &x){
    vector<bullets>::iterator iter;
    vector<bullets> tmp;

    bool flag = false;

    for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
    {
      if((pos_x + 240 < (*iter).bullet_pos.x + 9 || pos_y + 82 < (*iter).bullet_pos.y + 5) ||
      ((*iter).bullet_pos.x + 9 < pos_x + 9 || (*iter).bullet_pos.y + 5 < pos_y + 10))//안 맞았을 때
        tmp.push_back(*iter);
      else//맞았을때
      {
        if((*iter).bullet_pos.x <= pos_x + MINI_BOSS_WIDTH / 5)
          x = 0;
        else if((*iter).bullet_pos.x <= pos_x + (MINI_BOSS_WIDTH / 5) * 2)
          x = 1;
        else if((*iter).bullet_pos.x <= pos_x + (MINI_BOSS_WIDTH / 5) * 3)
          x = 2;
        else if((*iter).bullet_pos.x <= pos_x + (MINI_BOSS_WIDTH / 5) * 4)
          x = 3;
        else
          x = 4;
        flag = true;
      }
    }

    A.blt = tmp;

    return flag;
};
void Mini_Boss::shooting(_bullets &A){
    A.add_blt( 0, 5,pos_x + 125,pos_y + 82);
    A.add_blt( 3, 5,pos_x + 125,pos_y + 82);
    A.add_blt( -3, 5,pos_x + 125,pos_y + 82);
    A.add_blt( -6, 4,pos_x + 125,pos_y + 82);
    A.add_blt( 6, 4,pos_x + 125,pos_y + 82);
};

void Mini_Boss::enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip){
    SDL_Rect offset;
    offset.y = pos_y;
    offset.x = pos_x;
    SDL_BlitSurface(mini_boss, clip, destination, &offset );
};
void Mini_Boss::control_plane(_bullets &A){
    if(cont_shoot>=1 && cont_shoot <= 30) {this->cont_shoot ++; if(cont_shoot%6==0)this->shooting(A);} // TO make gap between each bullets in one cycle
    if(cont_shoot > 30) {if(cont_shoot>=50)cont_shoot = 0;else cont_shoot++;} // To make gap between each cycles
    if(count % 30 == 0 ) {this->shooting(A); this->cont_shoot ++;}
    if(count < 50){
        pos_y += 3;
    }
    else
    {
        if(direction == 0){
            if(this->pos_x>550) direction =1;
            this->pos_x += 2;
        }
        else{
            if(this->pos_x<90) direction = 0;
            this->pos_x -= 2;
        }
    }
    count++;
};

SDL_Rect Mini_Boss::Get_plane()
{
  offset.x = pos_x;
  offset.y = pos_y;

  return offset;
}

void Mini_Boss::loss_life(int& score)
{
    this->life--;
    score +=50;
    if( this->life == 0) {
      this->~Mini_Boss();
      score+=1000;
   }
}

Boss::Boss(){
    mini_boss = load_image("assets/boss4.png");// 비행기 이미지
    //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
    pos_x = 280;// 처음 시작 위치 지정
    SDL_SetColorKey(mini_boss, SDL_SRCCOLORKEY,SDL_MapRGB(mini_boss->format,255,255,255));
    pos_y = -MINI_BOSS_HEIGHT;//처음 시작 위치 지정
    life = 60;//has to be changed later (at least 70)
}

Boss::~Boss(){
    this->amount--;
    delete this->mini_boss;
};

bool Boss::Got_shot(_bullets &A, int &x){
    vector<bullets>::iterator iter;
    vector<bullets> tmp;

    bool flag = false;

    for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
    {
      if((pos_x + 135 < (*iter).bullet_pos.x + 9 || pos_y + 85 < (*iter).bullet_pos.y + 5) ||
      ((*iter).bullet_pos.x + 9 < pos_x + 9 || (*iter).bullet_pos.y + 5 < pos_y + 10))//안 맞았을 때
        tmp.push_back(*iter);
      else//맞았을때
      {
        if((*iter).bullet_pos.x <= pos_x + BOSS_WIDTH / 5)
          x = 0;
        else if((*iter).bullet_pos.x <= pos_x + (BOSS_WIDTH / 5) * 2)
          x = 1;
        else if((*iter).bullet_pos.x <= pos_x + (BOSS_WIDTH / 5) * 3)
          x = 2;
        else if((*iter).bullet_pos.x <= pos_x + (BOSS_WIDTH / 5) * 4)
          x = 3;
        else
          x = 4;

        flag = true;
      }
    }

    A.blt = tmp;

    return flag;
};
void Boss::shooting(_bullets &A){

    //rhombus
    A.add_blt( 0, 5,pos_x + 75,pos_y + 50);
    A.add_blt( 1, 4,pos_x + 75,pos_y + 50);
    A.add_blt( -1, 4,pos_x + 75,pos_y + 50);
    A.add_blt( -2, 3,pos_x + 75,pos_y + 50);
    A.add_blt( 2, 3,pos_x + 75,pos_y + 50);
    A.add_blt( 3, 2,pos_x + 75,pos_y + 50);
    A.add_blt( -3, 2,pos_x + 75,pos_y + 50);
    A.add_blt( 4, 1,pos_x + 75,pos_y + 50);
    A.add_blt( -4, 1,pos_x + 75,pos_y + 50);
    A.add_blt( 5, 0,pos_x + 75,pos_y + 50);
    A.add_blt( -5, 0,pos_x + 75,pos_y + 50);
    A.add_blt( -4, -1,pos_x + 75,pos_y + 50);
    A.add_blt( 4, -1,pos_x + 75,pos_y + 50);
    A.add_blt( -3, -2,pos_x + 75,pos_y + 50);
    A.add_blt( 3, -2,pos_x + 75,pos_y + 50);
    A.add_blt( -2, -3,pos_x + 75,pos_y + 50);
    A.add_blt( 2, -3,pos_x + 75,pos_y + 50);
    A.add_blt( -1, -4,pos_x + 75,pos_y + 50);
    A.add_blt( 1, -4,pos_x + 75,pos_y + 50);
    A.add_blt( 0, -5,pos_x + 75,pos_y + 50);

    //cross
    /*A.add_blt( 3, 0,pos_x + 75,pos_y + 50);
    A.add_blt( 4, 0,pos_x + 75,pos_y + 50);
    A.add_blt( -3, 0,pos_x + 75,pos_y + 50);
    A.add_blt( -4, 0,pos_x + 75,pos_y + 50);*/

    //A.add_blt( 10, 0,pos_x + 35,pos_y + 50);
    //A.add_blt( -10, 0,pos_x + 35,pos_y + 50);
};
void Boss::enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip){
    SDL_Rect offset;
    offset.y = pos_y;
    offset.x = pos_x;
    SDL_BlitSurface(mini_boss, clip, destination, &offset );
};
void Boss::control_plane(_bullets &A){
    if(cont_shoot>=1 && cont_shoot <15) {this->cont_shoot ++; if(cont_shoot%3==0)this->shooting(A);}
    if(cont_shoot >=15) cont_shoot = 0;
    if(count % 30 == 0 ) {this->shooting(A); this->cont_shoot ++;}
    if(count < 50){
        pos_y += 3;
    }
    else
    {
        if(direction == 0){
            if(this->pos_x>550) direction =1;
            this->pos_x += 2;
        }
        else{
            if(this->pos_x<90) direction = 0;
            this->pos_x -= 2;
        }
    }
    count++;
};

SDL_Rect Boss::Get_plane()
{
  offset.x = pos_x;
  offset.y = pos_y;

  return offset;
}
void Boss::loss_life(int& score)
{
    this->life--;
    score += 50;
    if( this->life == 0) {
      this->~Boss();
      score+=3000;
  }
}
