#include "helpers.h"

class BOOM
{
private:
  typedef struct bomb
  {
    SDL_Rect SDL_b;
    int count = 0;
  }bomb;
public:
  bomb b;
  int three;    //boss 맞았을 때 위치 정할 변수
  BOOM(SDL_Rect offset)
  {
     b.SDL_b = offset;
  };
  void set_bomb(SDL_Rect boss)
  {
    b.SDL_b = boss;
  }
  void boom_apply_surface(SDL_Surface* boom[], SDL_Surface* destination, SDL_Rect* clip,Mix_Chunk *sound)
  {//적 비행기가 격추됬을 때의 좌표에 폭발 스프라이트 이미지 출력
      Mix_VolumeChunk(sound,68);
      Mix_PlayChannel(-1,sound,0);//폭팔 사운드 출력
    	SDL_BlitSurface( boom[b.count++], clip, destination, &(b.SDL_b));
  };
};

typedef struct bullets
{
public:
  bullets(int x, int y , int ply_x, int ply_y )
  {
    move_x = x;
    move_y = y;
    offset.x = ply_x;
    offset.y = ply_y;
    angle=0;
  }
  bullets(int x, int y , int ply_x, int ply_y,double a )//angle을 줘서 총알 스프라이트의 모양을 회전시킬수 있다.
  {
    move_x = x;
    move_y = y;
    offset.x = ply_x;
    offset.y = ply_y;
    angle = a;
  }
  int move_x, move_y;//총알들의 방향성
  double angle;
  SDL_Rect offset;//총알들의 위치
}bullets;

typedef struct laser_bullet{
  bool env;
  SDL_Rect offset;
}laser_bullet;

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

class Special_item
{
public:
  SDL_Surface *item;

  ~Special_item();
  void add_itm(int x, int y, int ply_x, int ply_y);                                      //x,y는 item 방향성, ply_x,y는 item의 현재 위치
  void item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip);  // item들 그리기
  void control_item();

  vector<items> itm;
};

class Upgrade_item1//3방향 발사
{
public:
  SDL_Surface *item;

  ~Upgrade_item1();
  void add_itm(int x, int y, int ply_x, int ply_y);                                      //x,y는 item 방향성, ply_x,y는 item의 현재 위치
  void item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip);  // item들 그리기
  void control_item();

  vector<items> itm;
};
class Upgrade_item2 //레이저 아이템
{
public:
  SDL_Surface *item;

  ~Upgrade_item2();
  void add_itm(int x, int y, int ply_x, int ply_y);                                      //x,y는 item 방향성, ply_x,y는 item의 현재 위치
  void item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip);  // item들 그리기
  void control_item();

  vector<items> itm;
};


class special
{
public:
    special(int x, int SA) {
        pos_x1=x;
        if(SA == 0) sa1 = load_image("assets/sa1.png");
        else if (SA == 1) sa1 = load_image("assets/sa2.png");// gochuya ham
        else if (SA == 2) sa1 = load_image("assets/sa3.png");
        else if (SA == 3) sa1 = load_image("assets/sa4.png");
        else if (SA == 4) sa1 = load_image("assets/sa5.png");
        SDL_SetColorKey(sa1, SDL_SRCCOLORKEY, SDL_MapRGB(sa1->format,255,255,255));
  };
  void apply_surface(SDL_Surface * destination, SDL_Rect* clip)//총알들 그리기
  {
      SDL_Rect offset;
      offset.x = pos_x1;
      offset.y = pos_y1;
      SDL_BlitSurface(sa1, clip, destination, &offset);
  };

  void control_bullet()
  {
    pos_y1 -= 4;
    if(pos_y1==0)
    {
      if(Mix_PausedMusic)//정지되어 있는 음악이 있으면
        Mix_ResumeMusic();//음악을 다시 재생
      Mix_HaltChannel(-1);
    }
  };

  int pos(){
      return pos_y1;
  }
    int pos_y1=480;
private:
    int pos_x1;
    SDL_Surface *sa1;
    Mix_Chunk* special_sound;//특수기 효과음
};

class Obstacle
{
public:
    Obstacle(int x) {
        pos_x1=x;
        obs = load_image("assets/obstacle.png");
        SDL_SetColorKey(obs, SDL_SRCCOLORKEY, SDL_MapRGB(obs->format,255,255,255));
  };
  void apply_surface(SDL_Surface *destination,SDL_Rect* clip){
      SDL_Rect offset;
      offset.x=pos_x1;
      offset.y=pos_y1;

      SDL_BlitSurface(obs, clip, destination, &offset);
  };

  void control_bullet()
  {
    pos_y1 += 4;
  };

  int pos(){
      return pos_y1;
  }
    int pos_y1=0;
private:
    int pos_x1;
    SDL_Surface *obs;
};


class _bullets
{
  
public:
  void add_blt(int x, int y, int ply_x, int ply_y)//x,y는 총알 방향성, ply_x,y는 총알의 현재 위치
  {
    bullets tmp(x,y,ply_x,ply_y);
    blt.push_back(tmp);
  }
    void add_blt(int x, int y, int ply_x, int ply_y,double angle)//x,y는 총알 방향성, ply_x,y는 총알의 현재 위치 double은 회전 각도이다.
  {
    bullets tmp(x,y,ply_x,ply_y,angle);
    blt.push_back(tmp);
  }
  void set_offNmove(int x, int y,int w,int h){
    for(vector<bullets>::iterator iter = blt.begin(); iter != blt.end(); iter++)
      {
        iter->offset.w =w; iter->offset.h=h;
        iter->offset.x =x; iter->offset.y=y;   
      }
  }
  void bullet_apply_surface(SDL_Surface *bullet,SDL_Surface* destination, SDL_Rect* clip)//총알들 그리기
  {
    for(vector<bullets>::iterator iter = blt.begin(); iter!= blt.end(); iter++)
    {
      if(iter->angle ==0)
        SDL_BlitSurface( bullet, clip, destination, &(*iter).offset);
      else
      {
       
        SDL_BlitSurface( rotozoomSurface(bullet,iter->angle,1.0,SMOOTHING_OFF), clip, destination, &(*iter).offset);
      }
      
    }
  }

  void control_bullet()
  {
    vector<bullets> temp;
    for(vector<bullets>::iterator iter = blt.begin(); iter != blt.end(); iter++)
    {
      bullets tmp((*iter).move_x,(*iter).move_y,(*iter).offset.x + (*iter).move_x,(*iter).offset.y + (*iter).move_y,(*iter).angle);
      if( -1 < tmp.offset.x && tmp.offset.x< SCREEN_WIDTH && 0 <= tmp.offset.y  && tmp.offset.y < SCREEN_HEIGHT){
        temp.push_back(tmp);
      }
    }

    blt = temp;
  }

  void eliminate (special spc){
      vector<bullets> temp;
      for(vector<bullets>::iterator iter = blt.begin(); iter != blt.end(); iter++)
      {
          bullets tmp((*iter).move_x,(*iter).move_y,(*iter).offset.x + (*iter).move_x,(*iter).offset.y + (*iter).move_y);
          if(spc.pos_y1>tmp.offset.y+30||spc.pos_y1+180 < tmp.offset.y)temp.push_back(tmp);
      }
      blt = temp;
  }
 
  vector<bullets> blt;
};

class AirPlane
{
private:

  Mix_Chunk* shooting_sound;//총알 발사 사운드
  Mix_Chunk* get_sound;//아이템 획득 사운드
  Mix_Chunk* hit_sound;//피격음
  
  SDL_Rect offset;
  int pos_x,pos_y;// 비행기 x,y 좌표

public:
  AirPlane(Mix_Chunk* shooting,Mix_Chunk* get,Mix_Chunk* hit);//생성자를 통해 클래스의 사운드 청크를 지정한다.
  ~AirPlane();
  bool Got_shot(_bullets &A,_bullets &B,_bullets &C);
  bool Got_item(vector<items>& I);
  bool detect_collision(list<SDL_Rect> C);
  bool detect_collision(SDL_Rect C);
  bool check_in_border(SDL_Rect C,bool& flag);
  void shooting(_bullets &A,laser_bullet &player_laser_bullet);
  void increaseLife();
  void increaseSA();
  void Got_shiled(SDL_Surface *plane);
  void plane_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(int x, int y);
  void invisible(SDL_Surface *plane);
  SDL_Rect Get_plane();//plane 변수 getter
  void set_offset(int w,int h){offset.w=w,offset.h=h;}
  void set_pos(int x, int y){pos_x=x;pos_y=y;}

  short bullet_mode;// 업글 아이템을 먹었을 시 불릿 모드를 저장할 변수 1이 기본 발사 모드 2가 3방향 발사 모드
  int invisible_mode;
  int life;
  int SA_count;
};

class Enemy_standard_2
{
private:
  SDL_Surface *enemy;

  int pos_x, pos_y;
  int life;
  int mode;
  int count = 0;
  bool first_exe = true;   // to initialize count in control for only one time
  int pos;  // enemy's movement location

public:

  SDL_Rect offset;

  Enemy_standard_2(int mode);
  ~Enemy_standard_2();
  bool Got_shot(_bullets &A);
  bool Got_shot(laser_bullet A);
  bool eliminate ( int y);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  SDL_Rect  control_plane(_bullets &A);
  SDL_Rect Get_plane();
  void set_offset(int w,int h){offset.w=w,offset.h=h;}
  void set_pos(int x, int y){pos_x=x;pos_y=y;}

};


class Enemy_standard
{
private:
   
    int life;
    int count=0;//루프문 반복할 변수
    int mode;// 좌,우 나타날 장소를 정하는 변수
    bool first_exe = true;
    int pos;
  public:
    SDL_Rect offset;

    int pos_x,pos_y;// 비행기 x,y 좌표;
    Enemy_standard(int mode);
    ~Enemy_standard();
    bool Got_shot(_bullets &A);
    bool Got_shot(laser_bullet A);
    bool eliminate ( int y);
    void shooting(_bullets &A);
    void enemy_apply_surface(SDL_Surface* source[], SDL_Surface* destination, SDL_Rect* clip);
    SDL_Rect  control_plane(_bullets &enemey);
    SDL_Rect Get_plane();
    void set_offset(int w,int h){offset.w=w,offset.h=h;}
    void set_pos(int x, int y){pos_x=x;pos_y=y;}

    
};
/*
class Obstacle
{
private:
    SDL_Rect offset;
    //int life;
    int count=0;//루프문 반복할 변수
    bool first_exe = true;
    int pos;
  public:
    int pos_x,pos_y;// x,y 좌표;
    Obstacle();
    ~Obstacle();
    bool Got_shot(_bullets &A);
    void obstacle_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
    SDL_Rect  move_obstacle();
    SDL_Rect Get_obstacle();
};
*/
class Mini_Boss
{
public:
  SDL_Surface *mini_boss;
  
  Mix_Chunk* hit_sound;//피격음
  

  int pos_x, pos_y;
  int count = 0;
  int direction = 0;
  int cont_shoot = 0;
  int life;

public:
  SDL_Rect offset;

  Mini_Boss(Mix_Chunk* sound);
  ~Mini_Boss();
  bool Got_shot(_bullets &A, int &x);
  bool Got_shot(laser_bullet A, int &x,short RNG);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  SDL_Rect  control_plane(_bullets &A);
  void loss_life(int& score,Mix_Chunk* sound);
  SDL_Rect Get_plane();

  void set_offset(int w,int h){offset.w=w,offset.h=h;}
  void set_pos(int x, int y){pos_x=x;pos_y=y;}

  

  int amount = 1;
};

class Boss
{
private:
  SDL_Surface *mini_boss;
  
  Mix_Chunk* hit_sound;//피격음

  int pos_x, pos_y;
  int life;
  int count = 0;
  int direction = 0;
  int cont_shoot = 0;

public:

  SDL_Rect offset;

  Boss(Mix_Chunk* sound);
  ~Boss();
  bool Got_shot(_bullets &A,  int& x);
  bool Got_shot(laser_bullet A, int& x,short RNG);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  SDL_Rect  control_plane(_bullets &A);
  void loss_life(int& score,Mix_Chunk* sound);
  SDL_Rect Get_plane();

  void set_offset(int w,int h){offset.w=w,offset.h=h;}
  void set_pos(int x, int y){pos_x=x;pos_y=y;}

  

  int amount = 1;
};
