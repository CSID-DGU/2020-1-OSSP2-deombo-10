
#include "AirPlane.h"
#include <string>
#include <sstream>

SDL_Surface *screen;//화면
SDL_Surface *background;//배경화면
SDL_Surface *background2;
SDL_Surface *background3;
SDL_Surface *explosion; //보스 몹 맞을 때 폭팔
SDL_Surface *life;
SDL_Surface *sapoint;
SDL_Surface *bullet;//총알 이미지
SDL_Surface *bullet_basic;
SDL_Surface *bullet_mini;
SDL_Surface *bullet_boss;
SDL_Surface *message;
SDL_Surface *message2;
SDL_Surface *message3;
SDL_Surface *message4;
SDL_Surface *message5;
SDL_Surface *title_message;
SDL_Surface *plane;// 사용자 비행기 이미지
SDL_Surface *plane2;
SDL_Surface *plane3;
SDL_Surface *plane4;
SDL_Surface *plane5;
SDL_Surface *plane_1p;
SDL_Surface *plane_2p;
SDL_Surface *enemy[4];//회전하는 비행기 이미지
SDL_Surface *boom[11];// 폭발 이미지
SDL_Surface *frame;
SDL_Surface *frame2;
SDL_Surface *arrow;
SDL_Surface *pick1;
SDL_Surface *pick2;

SDL_Surface *enemy2;

SDL_Event event;
TTF_Font *font;
TTF_Font *font2;
TTF_Font *font3;
SDL_Color textColor = {0, 0, 0};
SDL_Color textColor2 = {0, 0, 0};


Uint8 *keystates;

const int INITIAL_MODE = 10;
int EXIT = -1;
int Continue = 0;
int craft;
int SA;
int SA2;
int mode;

void sprite_surface(SDL_Surface* source, SDL_Rect tmp, SDL_Surface* destination, int w, int h, int step,int mode);
bool init();//변수들 초기화 함수
bool load_files();//이미지, 폰트 초기화 함수
bool SDL_free();// sdl 변수들 free 함수
void menu();
void menu2();
void menu3();
void game_over();
void stage_clear();
void special_ability(int SA);

int main(){
  loop:
 _bullets enemy_bullets;
 _bullets player_bullets;
 _bullets boss_bullets;
 _bullets mini_bullets;
 //_special special_one;
  init();//초기화 함수
  load_files();//이미지,폰트,bgm 로드하는 함수
  menu();
  if(EXIT == 1)
  {
    return 0;
  }
  menu3();
  menu2();

  Continue = 0;
  srand(time(NULL));

  int score = 0;
  int start_time = 0;
  int delay = 0;
  int count = 0;
  int shootcnt = 0;
  int shootcnt2 = 0;
  int background_count = 0;               //background 움직임 count
  int boom_mode = 0;
  int flag = 0;
  int flag2 = 0;
  int flag3 = 0;
  int flag_sa = 0;
  int flag_sa2 = 0;
  int bound = -100;
  bool dead = false;
  bool dead2 = false;

  vector<Enemy_standard_2>::iterator it2;
  vector<Enemy_standard>::iterator it;
  vector<BOOM>::iterator B_it;
  vector<special>::iterator it_sa;

  vector<BOOM> Boss_B;//보스 폭발
  vector<BOOM> Boss_B4;//보스 폭발
  vector<BOOM> B;//폭발
  vector<Enemy_standard> E;//기본1형 비행기
  vector<Enemy_standard_2> E2;// 2nd standard enemy
  vector<special> sa_1;

  AirPlane A;//사용자 비행기
  AirPlane A2;
  AirPlane A3;
  Mini_Boss tmp3;
  Boss tmp4;
  Item I;
  Item2 I2;
  Item I3;

  while(true){
    if(flag_sa < 10) flag_sa++;
    if(flag_sa2 <10) flag_sa2++;
    vector<special> t;
    it_sa = sa_1.begin();
    for(it_sa; it_sa != sa_1.end();it_sa++){
        if((*it_sa).pos() > -130) t.push_back(*it_sa);
    }
    sa_1= t;

    if(t.size()>0){
        vector<special>:: iterator ta;
        ta= (t.begin());
        bound = (*ta).pos();
    }

    if(bound < -130 )bound = -100;
    if(count % 5 == 0) shootcnt = 0;
    if(count % 5 == 0) shootcnt2 = 0;
    if(count % 50 == 0)//100count마다 1기씩 생성
    {
      int i = rand()%2;
      int j = rand()%2;
      Enemy_standard tmp(i);
      Enemy_standard_2 tmp2(j);
      E.push_back(tmp);
      E2.push_back(tmp2);
  }

    start_time = SDL_GetTicks();//나중에 프레임 계산할 변수

    if(player_bullets.blt.size() > 0 )//총알들 위치 이동
      player_bullets.control_bullet();

    if(enemy_bullets.blt.size() > 0)//적 총알들 위치 이동
      enemy_bullets.control_bullet();

    if(I.itm.size() > 0)
      I.control_item();

    if(I2.itm.size() > 0)
      I2.control_item();

    if(I3.itm.size() > 0)
      I3.control_item();

    if(boss_bullets.blt.size()>0)
      boss_bullets.control_bullet();

    if(mini_bullets.blt.size() > 0)
      mini_bullets.control_bullet();


    if(dead != true && A.Got_shot(enemy_bullets,boss_bullets,mini_bullets) && A.invisible_mode == 0)      //사용자 피격 판정
    {
      A.life--;
      A.invisible_mode = 1;
    }

    if(dead2 != true && mode == 2 && A2.Got_shot(enemy_bullets,boss_bullets,mini_bullets) && A2.invisible_mode == 0)      //사용자 피격 판정
    {
      A2.life--;
      A2.invisible_mode = 1;
    }

    if(E.size() > 0)
    {
      vector<Enemy_standard> v_tmp;


      for(it = E.begin(); it != E.end(); it++)//적 비행기들 피격 판정
      {
        Enemy_standard tmp(0);
        if((*it).Got_shot(player_bullets) || (bound < (*it).pos_y+32) && (bound+30 > (*it).pos_y))//비행기가 격추 당하면
        {
          if(I.itm.size() == 0)
          {
            I.add_itm((*it).pos_x, (*it).pos_y, (*it).pos_x, (*it).pos_y + 20);
            flag = (rand() % 3);
          }
          else if(I3.itm.size() == 0)
          {
            I3.add_itm((*it).pos_x, (*it).pos_y, (*it).pos_x, (*it).pos_y + 20);
            flag3 = (rand() % 4);
          }
          BOOM B_tmp((*it).Get_plane());
          B.push_back(B_tmp);
          (*it).~Enemy_standard();
          score += 100;
        }
        else
        {
          tmp = *it;
          v_tmp.push_back(tmp);
        }
      }

      E = v_tmp;

    }
    if(E2.size()>0)
    {
        vector<special> t;
        vector<Enemy_standard_2> v_tmp;
        it_sa = sa_1.begin();
        for(it2 = E2.begin(); it2 != E2.end(); it2++)//적 비행기들 피격 판정
        {
          Enemy_standard_2 tmp(0);
          if((*it2).Got_shot(player_bullets) || (bound < (*it).pos_y+32) && (bound+30 > (*it).pos_y))
          {
            BOOM B_tmp((*it2).Get_plane());
            B.push_back(B_tmp);
            (*it2).~Enemy_standard_2();
            score += 100;
          }
          else
          {
            tmp = *it2;
            v_tmp.push_back(tmp);
          }
        }

        E2=v_tmp;
    }

    if(tmp3.amount == 1 && tmp3.Got_shot(player_bullets, boom_mode) && score >= 500) {
        BOOM tmp(tmp3.Get_plane());
        tmp.three = boom_mode;
        Boss_B.push_back(tmp);
        tmp3.loss_life(score);
        if(I2.itm.size() == 0 && tmp3.life == 0)
        {
          I2.add_itm(tmp3.pos_x, tmp3.pos_y, tmp3.pos_x, tmp3.pos_y + 20);
          //flag2 = (rand() % 2);
          flag2 = 1;
        }

        if(I2.itm.size() == 0 && tmp3.life == 0)
        {
          I3.add_itm(tmp3.pos_x, tmp3.pos_y, tmp3.pos_x, tmp3.pos_y + 20);
          flag3 = (rand() % 2);
          //flag3 = 1;
        }
    }   // have to add the condition when the mini boss appear

    if(tmp4.amount == 1 && tmp4.Got_shot(player_bullets, boom_mode) && score >= 5000) // have to add the condition when the mini boss appear
    {
      BOOM tmp(tmp4.Get_plane());
      tmp.three = boom_mode;
      Boss_B4.push_back(tmp);
      tmp4.loss_life(score);
    }

    if(A.Got_item(I.itm))
    {
      if(A.life < 3)
      {
        A.increaseLife();
      }
      flag = 0;
    }

    if(A.Got_item(I2.itm))
    {
      if(A.SA_count < 3)
      {
        A.increaseSA();
      }
      flag2 = 0;
    }

    if(A.Got_item(I3.itm))
    {
      A.Got_shiled(plane);
      flag3 = 0;
    }

    if(tmp4.amount == 0)
    {
      stage_clear();
      break;
    }

    if(sa_1.size()>0){
        it_sa = sa_1.begin();
        enemy_bullets.eliminate(*it_sa);
        boss_bullets.eliminate(*it_sa);
        mini_bullets.eliminate(*it_sa);
    }

    if(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT)//버튼 누르면 꺼저야 되는데 안 꺼짐 수정 사항
			   break;
    }

    keystates = SDL_GetKeyState(NULL);

    if(keystates[SDLK_ESCAPE])
      break;
    if(E.size() > 0)//적 비행기 이동 및 발사
    {
      for(it = E.begin(); it != E.end(); it++)
      {
        (*it).control_plane(enemy_bullets);
      }
    }
    if(E2.size() >0){
      for(it2 = E2.begin(); it2 != E2.end(); it2++)
      {
        (*it2).control_plane(enemy_bullets);
      }
    }

    if(tmp3.amount == 1 && score >= 500)tmp3.control_plane(mini_bullets); // have to add the condition when the mini boss appear

    if(tmp4.amount == 1 && score >= 5000)tmp4.control_plane(boss_bullets); // have to add the condition when the mini boss appear

    if(sa_1.size() >0)
    {
        for(it_sa = sa_1.begin(); it_sa != sa_1.end(); it_sa++){
            (*it_sa).control_bullet();
        }
    }

    if(keystates[SDLK_o] && dead != true)
    {
      if(shootcnt == 0) {
          A.shooting(player_bullets);
          shootcnt = 1;
      }
    }
    if(mode ==2&&keystates[SDLK_f] && dead2 != true)
      {
        if(shootcnt2 == 0) {
            A2.shooting(player_bullets);
            shootcnt2 = 1;
        }
      }

    if(keystates[SDLK_p] && flag_sa == 10 && dead != true)    /// SHOULD HAVE FLAG TO AVOID SPECIAL ABILITY IS USED NUMEROUS TIMES BY PRESSING ONCE.
    {
        if(A.SA_count >0){
           A.SA_count --; //// Put image for SA
           flag_sa = 0;
           switch (SA){
           case 0:
               {
                   special tmp(0,0);
                   special tmp2(100,0);
                   special tmp3(200,0);
                   special tmp4(300,0);
                   special tmp5(400,0);
                   special tmp6(500,0);
                   special tmp7(600,0);
                   special tmp8(700,0);
                   sa_1.push_back(tmp);
                   sa_1.push_back(tmp2);
                   sa_1.push_back(tmp3);
                   sa_1.push_back(tmp4);
                   sa_1.push_back(tmp5);
                   sa_1.push_back(tmp6);
                   sa_1.push_back(tmp7);
                   sa_1.push_back(tmp8);
               break;
              }
               case 1:
              {
                  special tmp(0,1);
                  special tmp2(100,1);
                  special tmp3(200,1);
                  special tmp4(300,1);
                  special tmp5(400,1);
                  special tmp6(500,1);
                  special tmp7(600,1);
                  special tmp8(700,1);
                  sa_1.push_back(tmp);
                  sa_1.push_back(tmp2);
                  sa_1.push_back(tmp3);
                  sa_1.push_back(tmp4);
                  sa_1.push_back(tmp5);
                  sa_1.push_back(tmp6);
                  sa_1.push_back(tmp7);
                  sa_1.push_back(tmp8);
                  break;
              }
               case 2:
              {
                  special tmp(0,2);
                  special tmp2(100,2);
                  special tmp3(200,2);
                  special tmp4(300,2);
                  special tmp5(400,2);
                  special tmp6(500,2);
                  special tmp7(600,2);
                  special tmp8(700,2);
                  sa_1.push_back(tmp);
                  sa_1.push_back(tmp2);
                  sa_1.push_back(tmp3);
                  sa_1.push_back(tmp4);
                  sa_1.push_back(tmp5);
                  sa_1.push_back(tmp6);
                  sa_1.push_back(tmp7);
                  sa_1.push_back(tmp8);
                   break;
              }
               case 3:
              {
                  special tmp(0,3);
                  special tmp2(100,3);
                  special tmp3(200,3);
                  special tmp4(300,3);
                  special tmp5(400,3);
                  special tmp6(500,3);
                  special tmp7(600,3);
                  special tmp8(700,3);
                  sa_1.push_back(tmp);
                  sa_1.push_back(tmp2);
                  sa_1.push_back(tmp3);
                  sa_1.push_back(tmp4);
                  sa_1.push_back(tmp5);
                  sa_1.push_back(tmp6);
                  sa_1.push_back(tmp7);
                  sa_1.push_back(tmp8);
                  break;
              }
               case 4:
              {
                  special tmp(0,4);
                  special tmp2(100,4);
                  special tmp3(200,4);
                  special tmp4(300,4);
                  special tmp5(400,4);
                  special tmp6(500,4);
                  special tmp7(600,4);
                  special tmp8(700,4);
                  sa_1.push_back(tmp);
                  sa_1.push_back(tmp2);
                  sa_1.push_back(tmp3);
                  sa_1.push_back(tmp4);
                  sa_1.push_back(tmp5);
                  sa_1.push_back(tmp6);
                  sa_1.push_back(tmp7);
                  sa_1.push_back(tmp8);
                  break;
              }
           }
        }
    }
    if(keystates[SDLK_KP8])
        A.control_plane(0,-4);

      if(keystates[SDLK_KP5])
        A.control_plane(0, 4);

      if(keystates[SDLK_KP4])
        A.control_plane(-4, 0);

      if(keystates[SDLK_KP6])
        A.control_plane(4, 0);
      if(mode == 2 && dead2 != true)
      {
        if(keystates[SDLK_f])
          {
            if(shootcnt == 0) {
                A2.shooting(player_bullets);
                shootcnt = 1;
            }
          }
          if(mode == 2 && keystates[SDLK_g])    /// SHOULD HAVE FLAG TO AVOID SPECIAL ABILITY IS USED NUMEROUS TIMES BY PRESSING ONCE.
          {
              if(A2.SA_count >0 && flag_sa2 == 10){
                 A2.SA_count --; //// Put image for SA
                 flag_sa2= 0;
                 switch (SA2){
                 case 0:
                     {
                         special tmp(0, 0);
                         special tmp2(100, 0);
                         special tmp3(200, 0);
                         special tmp4(300, 0);
                         special tmp5(400, 0);
                         special tmp6(500, 0);
                         special tmp7(600, 0);
                         special tmp8(700, 0);
                         sa_1.push_back(tmp);
                         sa_1.push_back(tmp2);
                         sa_1.push_back(tmp3);
                         sa_1.push_back(tmp4);
                         sa_1.push_back(tmp5);
                         sa_1.push_back(tmp6);
                         sa_1.push_back(tmp7);
                         sa_1.push_back(tmp8);
                     break;
                    }
                     case 1:
                    {
                        special tmp(0, 1);
                        special tmp2(100, 1);
                        special tmp3(200, 1);
                        special tmp4(300, 1);
                        special tmp5(400, 1);
                        special tmp6(500, 1);
                        special tmp7(600, 1);
                        special tmp8(700, 1);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                     case 2:
                    {
                        special tmp(0, 2);
                        special tmp2(100, 2);
                        special tmp3(200, 2);
                        special tmp4(300, 2);
                        special tmp5(400, 2);
                        special tmp6(500, 2);
                        special tmp7(600, 2);
                        special tmp8(700, 2);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                         break;
                    }
                     case 3:
                    {
                        special tmp(0, 3);
                        special tmp2(100, 3);
                        special tmp3(200, 3);
                        special tmp4(300, 3);
                        special tmp5(400, 3);
                        special tmp6(500, 3);
                        special tmp7(600, 3);
                        special tmp8(700, 3);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                     case 4:
                    {
                        special tmp(0, 4);
                        special tmp2(100, 4);
                        special tmp3(200, 4);
                        special tmp4(300, 4);
                        special tmp5(400, 4);
                        special tmp6(500, 4);
                        special tmp7(600, 4);
                        special tmp8(700, 4);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                 }
              }
          }

          if(keystates[SDLK_w])
            A2.control_plane(0,-0);

          if(keystates[SDLK_s])
            A2.control_plane(0, 0);

          if(keystates[SDLK_a])
            A2.control_plane(-0, 0);

          if(keystates[SDLK_d])
            A2.control_plane(0, 0);
      }

          if(mode ==2&&keystates[SDLK_g])    /// SHOULD HAVE FLAG TO AVOID SPECIAL ABILITY IS USED NUMEROUS TIMES BY PRESSING ONCE.
          {
              if(A2.SA_count >0&& flag_sa2==10){
                 A2.SA_count --; //// Put image for SA
                 switch (SA2){
                 case 0:
                     {
                         special tmp(0, 0);
                         special tmp2(100, 0);
                         special tmp3(200,0);
                         special tmp4(300,0);
                         special tmp5(400,0);
                         special tmp6(500,0);
                         special tmp7(600,0);
                         special tmp8(700,0);
                         sa_1.push_back(tmp);
                         sa_1.push_back(tmp2);
                         sa_1.push_back(tmp3);
                         sa_1.push_back(tmp4);
                         sa_1.push_back(tmp5);
                         sa_1.push_back(tmp6);
                         sa_1.push_back(tmp7);
                         sa_1.push_back(tmp8);
                     break;
                    }
                     case 1:
                    {
                        special tmp(0,1);
                        special tmp2(100,1);
                        special tmp3(200,1);
                        special tmp4(300,1);
                        special tmp5(400,1);
                        special tmp6(500,1);
                        special tmp7(600,1);
                        special tmp8(700,1);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                     case 2:
                    {
                        special tmp(0,2);
                        special tmp2(100,2);
                        special tmp3(200,2);
                        special tmp4(300,2);
                        special tmp5(400,2);
                        special tmp6(500,2);
                        special tmp7(600,2);
                        special tmp8(700,2);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                     case 3:
                    {
                        special tmp(0,3);
                        special tmp2(100,3);
                        special tmp3(200,3);
                        special tmp4(300,3);
                        special tmp5(400,3);
                        special tmp6(500,3);
                        special tmp7(600,3);
                        special tmp8(700,3);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                     case 4:
                    {
                        special tmp(0,4);
                        special tmp2(100,4);
                        special tmp3(200,4);
                        special tmp4(300,4);
                        special tmp5(400,4);
                        special tmp6(500,4);
                        special tmp7(600,4);
                        special tmp8(700,4);
                        sa_1.push_back(tmp);
                        sa_1.push_back(tmp2);
                        sa_1.push_back(tmp3);
                        sa_1.push_back(tmp4);
                        sa_1.push_back(tmp5);
                        sa_1.push_back(tmp6);
                        sa_1.push_back(tmp7);
                        sa_1.push_back(tmp8);
                        break;
                    }
                 }
              }
          }

          if(mode ==2&&keystates[SDLK_w])
            A2.control_plane(0,-4);

          if(mode ==2&&keystates[SDLK_s])
            A2.control_plane(0, 4);

          if(mode ==2&&keystates[SDLK_a])
            A2.control_plane(-4, 0);

          if(mode ==2&&keystates[SDLK_d])
            A2.control_plane(4, 0);


    if(A.invisible_mode == 1)//투명화 상태, 투명도 조절
      A.invisible(plane_1p);

    if( mode ==2&&A2.invisible_mode == 1)//투명화 상태, 투명도 조절
      A2.invisible(plane_2p);

      if(background_count++ != 480);
      else
        background_count = 0;

    //이미지 그리는 부분
    apply_surface(0, -480 + background_count, background2,screen,NULL);//백그라운드 그리는거
    apply_surface(0, 0 + background_count, background,screen,NULL);//백그라운드 그리는거
    enemy_bullets.bullet_apply_surface(bullet_basic, screen,NULL);//적 총알들
    boss_bullets.bullet_apply_surface(bullet_boss, screen, NULL);
    mini_bullets.bullet_apply_surface(bullet_mini, screen, NULL);
    player_bullets.bullet_apply_surface(bullet, screen, NULL);//사용자 총알들
    if(dead != true)
    {
      A.plane_apply_surface(plane_1p, screen, NULL); //사용자 비행기
    }
    else if (dead == true) {
      A.~AirPlane();
    }

    if(mode == 2 && dead2 != true)  A2.plane_apply_surface(plane_2p, screen,NULL); //사용자 비행기

    if(flag == 1)
    {
      I.item_apply_surface(I.item, screen, NULL);
    }

    if(flag2 == 1)
    {
      I2.item_apply_surface(I2.item, screen, NULL);
    }

    if(flag3 == 1)
    {
      I3.item_apply_surface(I3.item, screen, NULL);
    }

    if( E.size() > 0)//적 비행기
    {
      for( it = E.begin(); it != E.end(); it++)
      {
        (*it).enemy_apply_surface(enemy, screen, NULL);
      }
    }
    if( E2.size() > 0)
    {
      for( it2 = E2.begin(); it2 != E2.end(); it2++)
      {
        (*it2).enemy_apply_surface(screen, NULL);
      }
    }

    if(sa_1.size() >0)
    {
        for(it_sa = sa_1.begin(); it_sa != sa_1.end(); it_sa++){
            (*it_sa).apply_surface(screen, NULL);
        }
    }

    if(tmp3.amount ==1 && score >= 500) tmp3.enemy_apply_surface(screen, NULL); // have to add the condition when the mini boss appear

    if(tmp4.amount == 1 && score>= 5000) tmp4.enemy_apply_surface(screen, NULL); // have to add the condition when the mini boss appear

    if( B.size() > 0)//폭발
    {
      vector<BOOM> B_tmp;

      for(B_it = B.begin(); B_it != B.end(); B_it++)
      {
        if((*B_it).b.count <  11)
        {
          (*B_it).boom_apply_surface(boom,screen,NULL);
          B_tmp.push_back(*B_it);
        }
        else
        {
          (*B_it).~BOOM();
        }
      }
      B = B_tmp;
    }

    if(Boss_B.size() > 0)                                    //보스 맞을 때 폭발 구현
    {
      vector<BOOM> B_tmp;

      for(B_it = Boss_B.begin(); B_it != Boss_B.end(); B_it++)
      {
        if((*B_it).b.count <  8)
        {
          sprite_surface(screen,tmp3.Get_plane(), explosion, 8, 1, (*B_it).b.count, (*B_it).three);
          (*B_it).b.count++;
          B_tmp.push_back(*B_it);
        }

        else
        {
          (*B_it).~BOOM();
        }
      }
      Boss_B = B_tmp;
    }

    if(Boss_B4.size() > 0)                                    //보스 맞을 때 폭발 구현
    {
      vector<BOOM> B_tmp;

      for(B_it = Boss_B4.begin(); B_it != Boss_B4.end(); B_it++)
      {
        if((*B_it).b.count <  8)
        {
          sprite_surface(screen, tmp4.Get_plane(), explosion, 8, 1, (*B_it).b.count,(*B_it).three);
          (*B_it).b.count++;
          B_tmp.push_back(*B_it);
        }
        else
        {
          (*B_it).~BOOM();
        }
      }
      Boss_B4 = B_tmp;
    }


    if(A.life == 0 && mode == 1)//생명력 0
    {
      game_over();
      if (Continue == 1)
      {
        goto loop;
      }
      break;
    }

    if(A.life == 1)//생명력 1
      apply_surface(550, 10, life, screen,NULL);
    else if(A.life == 2)
    {
      apply_surface(550, 10, life, screen,NULL); apply_surface(580, 10, life, screen,NULL);
    }
    else if(A.life == 3)
    {
      apply_surface(550, 10, life, screen,NULL); apply_surface(580, 10, life, screen,NULL); apply_surface(610, 10, life, screen,NULL);
    }


    if(mode == 2)
    {
      if(A.life == 0 && A2.life == 0)
      {
        game_over();
        if (Continue == 1)
        {
          goto loop;
        }
        break;
      }
      else if(A.life == 0 && A2.life > 0)//생명력 0
      {
        dead = true;
      }

      else if(A2.life == 0 && A.life > 0)//생명력 0
      {
        dead2 = true;
      }

      if(A2.life == 1)//생명력 1
        apply_surface(550, 30, life, screen,NULL);
      else if(A2.life == 2)
      {
        apply_surface(550, 30, life, screen,NULL); apply_surface(580, 30, life, screen,NULL);
      }
      else if(A2.life == 3)
      {
        apply_surface(550, 30, life, screen,NULL); apply_surface(580, 30, life, screen,NULL); apply_surface(610, 30, life, screen,NULL);
      }
    }

    if (mode == 1) {
      if(A.SA_count == 1)//생명력 1
        apply_surface(550, 450, sapoint, screen,NULL);
        else if(A.SA_count == 2)
        {
          apply_surface(550, 450, sapoint, screen,NULL); apply_surface(580, 450, sapoint, screen,NULL);
        }
        else if(A.SA_count == 3)
        {
          apply_surface(550, 450, sapoint, screen ,NULL); apply_surface(580, 450, sapoint, screen,NULL); apply_surface(610, 450, sapoint, screen,NULL);
        }
      }

    if (mode == 2)
    {
      if(A.SA_count == 1)//생명력 1
        apply_surface(550, 430, sapoint, screen,NULL);
      else if(A.SA_count == 2)
      {
        apply_surface(550, 430, sapoint, screen,NULL); apply_surface(580, 430, sapoint, screen,NULL);
      }
      else if(A.SA_count == 3)
      {
        apply_surface(550, 430, sapoint, screen ,NULL); apply_surface(580, 430, sapoint, screen,NULL); apply_surface(610, 430, sapoint, screen,NULL);
      }

      if(A2.SA_count == 1)//생명력 1
        apply_surface(550, 450, sapoint, screen,NULL);
      else if(A2.SA_count == 2)
      {
        apply_surface(550, 450, sapoint, screen,NULL); apply_surface(580, 450, sapoint, screen,NULL);
      }
      else if(A2.SA_count == 3)
      {
        apply_surface(550, 450, sapoint, screen ,NULL); apply_surface(580, 450, sapoint, screen,NULL); apply_surface(610, 450, sapoint, screen,NULL);
      }
    }


    ostringstream sc;
    sc<< score;
    message5 = TTF_RenderText_Solid(font3, sc.str().c_str(), textColor);
    apply_surface(0, 0, message5, screen, NULL);

    //fps 계산
    delay = 1000/40 - (SDL_GetTicks() - start_time);
    if(delay > 0)
      SDL_Delay(delay);

      SDL_Flip(screen);
      count ++;
  }
  SDL_free();
  return 0;
}




bool init()
{//고칠 것: if문 추가해서 init했을 때 실패하면 false반환하게끔
  SDL_Init(SDL_INIT_EVERYTHING);//SDL initialize
  TTF_Init();
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF |SDL_RESIZABLE);
  //SDL_RESIZABLE 추가하여 윈도우 크기 조절을 가능하게 함
  SDL_WM_SetCaption("MSG", NULL);
  return true;
}
//return true;

bool load_files()
{//고칠 것: if문 추가해서 init했을 때 실패하면 false반환하게끔
  explosion = load_image("assets/explosion.png");
  life = load_image("assets/life.gif");                   //life
  background = load_image("assets/background.png");//배경화면
  background2 = load_image("assets/background2.png");//배경화면
  bullet = load_image("assets/BULLET.png");// 총알 이미지
  bullet_basic = load_image("assets/bullet.gif");
  bullet_boss = load_image("assets/bossbullet.png");
  bullet_mini = load_image("assets/bossbullet.png");
  plane = load_image("assets/p2.gif");// 사용자 비행기 이미지
  plane2 = load_image("assets/aircraft1.png");
  plane3 = load_image("assets/aircraft3.png");
  plane4 = load_image("assets/aircraft5.png");
  plane5 = load_image("assets/aircraft6.png");
  plane_2p = load_image("assets/aircraft3.png");
  pick1 = load_image("assets/p2.png");
  pick2 = load_image("assets/aircraft6.png");
  frame = load_image("assets/blueframe.png");
  frame2 = load_image("assets/redframe.png");
  arrow = load_image("assets/arrow.png");
  font = TTF_OpenFont("assets/Terminus.ttf", 24);//작은 안내문 폰트
  font2 = TTF_OpenFont("assets/Starjout.ttf", 84);//제목 폰트
  font3 = TTF_OpenFont("assets/Starjout.ttf",24);
  sapoint = load_image("assets/sapoint1.png");
  for(int i = 0 ; i < 4; i++)
  {
    string str = "assets/E_";
    string str1 = to_string(i + 1);
    string str2 = ".gif";
    string str3 = str + str1 + str2;
    enemy[i] = load_image(str3);
    SDL_SetColorKey(enemy[i], SDL_SRCCOLORKEY,SDL_MapRGB(enemy[i]->format,255,255,255));
  }
  for(int i = 0 ; i < 11; i++)//폭발 이미지
  {
    string str = "assets/explosion/";
    string str1 = to_string(i);
    string str2 = ".gif";
    string str3 = str + str1 + str2;
    boom[i] =load_image(str3);
    SDL_SetColorKey(boom[i], SDL_SRCCOLORKEY,SDL_MapRGB(boom[i]->format,255,255,255));
  }
  SDL_SetColorKey(explosion, SDL_SRCCOLORKEY,SDL_MapRGB(explosion->format,0,0,0));
  SDL_SetColorKey(life, SDL_SRCCOLORKEY,SDL_MapRGB(life->format,255,255,255));
  SDL_SetColorKey(bullet_boss, SDL_SRCCOLORKEY, SDL_MapRGB(bullet_boss->format,0,0,0));
  SDL_SetColorKey(bullet_boss, SDL_SRCCOLORKEY, SDL_MapRGB(bullet_mini->format,0,0,0));
  SDL_SetColorKey(frame, SDL_SRCCOLORKEY,SDL_MapRGB(frame->format,0,0,0));
  SDL_SetColorKey(frame2, SDL_SRCCOLORKEY,SDL_MapRGB(frame2->format,0,0,0));
  SDL_SetColorKey(bullet, SDL_SRCCOLORKEY,SDL_MapRGB(bullet->format,0,0,0));
  SDL_SetColorKey(bullet_basic, SDL_SRCCOLORKEY, SDL_MapRGB(bullet_basic->format,255,255,255));
  SDL_SetColorKey(arrow, SDL_SRCCOLORKEY,SDL_MapRGB(arrow->format,0,0,0));
  SDL_SetColorKey(sapoint, SDL_SRCCOLORKEY,SDL_MapRGB(sapoint->format,255,255,255));
  return true;
}

bool SDL_free()
{//올바르게 free하면 true 반환하게 수정
  SDL_FreeSurface(plane);
  SDL_FreeSurface(bullet);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  for(int i =0 ; i < 4; i++)
    SDL_FreeSurface(enemy[i]);
  for(int i = 0; i < 11; i++)
    SDL_FreeSurface(boom[i]);

  SDL_Quit();//init한 SDL 변수들 닫아주는겅 일걸,위의 freesurface랑 차이 모름

  return true;
}

void menu()   // 처음 시작 메뉴
{
  textColor = {204, 255, 204};  // 안내 폰트 색깔
  textColor2 = {255, 255, 255}; // 제목 폰트 색깔
	bool quit = false;
	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
      message = TTF_RenderText_Solid(font, "Press space to start, esc key to quit", textColor); // space키는 시작 esc키는 종료
      message2 = TTF_RenderText_Solid(font2, "Starwars", textColor2);  // 제목
      background = load_image("assets/menu3.jpg");  // 배경
			apply_surface(0, 0, background, screen, NULL);
      apply_surface((640 - message->w) / 2, 280, message, screen, NULL);
      apply_surface((640 - message2->w) / 2, 100, message2, screen, NULL);
			SDL_Flip(screen);


			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          quit = true;
          background = load_image("assets/background.png");
          break;
        }
        case SDLK_ESCAPE:  // esc 키 누르면 종료
        {
          EXIT = 1;
          quit = true;
          break;
        }
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

void menu2()   // 비행기 고르는 메뉴
{
  int selectx = 25;
  int selectx2 = 525;
	bool quit = false;
  bool quit2 = false;
  bool choosen = false;
  bool choosen2 = false;
	while (quit == false || quit2 == false)
	{
		if (SDL_PollEvent(&event))
		{
      font = TTF_OpenFont("assets/Terminus.ttf", 36);//작은 안내문 폰트
      message = TTF_RenderText_Solid(font, "Choose your Aircraft", textColor); // space키는 시작 esc키는 종료
      message2 = TTF_RenderText_Solid(font3, "1P", textColor);
      message3 = TTF_RenderText_Solid(font3, "2P", textColor);
      message4 = TTF_RenderText_Solid(font3, "1p              2p", textColor);
      background = load_image("assets/background.png");  // 배경
			apply_surface(0, 0, background, screen, NULL);
      apply_surface((640 - message->w) / 2, 90, message, screen, NULL);
      apply_surface(selectx, 220, frame, screen, NULL);
      apply_surface(selectx+30, 180, message2, screen, NULL);
      if(mode == 2)
      {
        apply_surface(selectx2, 220, frame2, screen, NULL);
        apply_surface(selectx2+30, 315, message3, screen, NULL);
        apply_surface(200, 430, message4, screen, NULL);
        apply_surface(202, 400, pick1, screen, NULL);
        SDL_SetColorKey(pick1, SDL_SRCCOLORKEY,SDL_MapRGB(pick1->format,0,0,0));
        apply_surface(387, 400, pick2, screen, NULL);
        SDL_SetColorKey(pick2, SDL_SRCCOLORKEY,SDL_MapRGB(pick2->format,0,0,0));
      }
      SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,255,255,255));
      apply_surface(57, 255, plane, screen, NULL);
      SDL_SetColorKey(plane2, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
      apply_surface(182, 255, plane2, screen, NULL);
      SDL_SetColorKey(plane3, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
      apply_surface(307, 255, plane3, screen, NULL);
      SDL_SetColorKey(plane4, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
      apply_surface(432, 255, plane4, screen, NULL);
      SDL_SetColorKey(plane5, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
      apply_surface(557, 255, plane5, screen, NULL);
			SDL_Flip(screen);

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{

        case SDLK_SPACE:
        {
          if(choosen && choosen2)
          {
            quit = true;
            quit2 = true;
          }
          else
          {}
          break;
        }

				case SDLK_o:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          choosen = true;
          quit = true;
          if(selectx == 25){
            plane_1p = load_image("assets/p2.png");
            pick1 = load_image("assets/p2.png");
            SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,255,255,255));
            SA = 0;
          }

          else if(selectx == 150){
            plane_1p = load_image("assets/aircraft1.png");
            pick1 = load_image("assets/aircraft1.png");
            SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
            SA = 1;
          }
          else if(selectx == 275){
            plane_1p = load_image("assets/aircraft3.png");
            pick1 = load_image("assets/aircraft3.png");
            SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
            SA = 2;
          }
          else if(selectx == 400){
            plane_1p = load_image("assets/aircraft5.png");
            pick1 = load_image("assets/aircraft5.png");
            SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
            SA = 3;
          }
          else if(selectx == 525){
            plane_1p = load_image("assets/aircraft6.png");
            pick1 = load_image("assets/aircraft6.png");
            SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,0,0,0));
            SA = 4;
          }
          if(mode == 1)
            quit2 = true;
          break;
        }

        case SDLK_f:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          choosen2 = true;
          if(selectx2 == 25){
            plane_2p = load_image("assets/p2.png");
            pick2 = load_image("assets/p2.png");
            SDL_SetColorKey(plane_2p, SDL_SRCCOLORKEY,SDL_MapRGB(plane_2p->format,255,255,255));
            SA2 = 0;
          }

          else if(selectx2 == 150){
            plane_2p = load_image("assets/aircraft1.png");
            pick2 = load_image("assets/aircraft1.png");
            SDL_SetColorKey(plane_2p, SDL_SRCCOLORKEY,SDL_MapRGB(plane_2p->format,0,0,0));
            SA2 = 1;
          }
          else if(selectx2 == 275){
            plane_2p = load_image("assets/aircraft3.png");
            pick2 = load_image("assets/aircraft3.png");
            SDL_SetColorKey(plane_2p, SDL_SRCCOLORKEY,SDL_MapRGB(plane_2p->format,0,0,0));
            SA2 = 2;
          }
          else if(selectx2 == 400){
            plane_2p = load_image("assets/aircraft5.png");
            pick2 = load_image("assets/aircraft5.png");
            SDL_SetColorKey(plane_2p, SDL_SRCCOLORKEY,SDL_MapRGB(plane_2p->format,0,0,0));
            SA2 = 3;
          }
          else if(selectx2 == 525){
            plane_2p = load_image("assets/aircraft6.png");
            pick2 = load_image("assets/aircraft6.png");
            SDL_SetColorKey(plane_2p, SDL_SRCCOLORKEY,SDL_MapRGB(plane_2p->format,0,0,0));
            SA2 = 4;
          }


          break;
        }


        case SDLK_KP4:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          if (selectx == 25)
          {}
          else
          {
            selectx -= 125;
          }
          break;
        }
        case SDLK_KP6:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          if(selectx == 525)
          {}
          else
          {
            selectx += 125;
          }
          break;
        }
        case SDLK_a:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          if (selectx2 == 25)
          {}
          else
          {
            selectx2 -= 125;
          }
          break;
        }
        case SDLK_d:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          if(selectx2 == 525)
          {}
          else
          {
            selectx2 += 125;
          }
          break;
        }


        case SDLK_ESCAPE:  // esc 키 누르면 종료
        {
          EXIT = 1;
          quit = true;
          break;
        }
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

void menu3()   // 비행기 고르는 메뉴
{
  int selecty=210;
	bool quit = false;
	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
      font = TTF_OpenFont("assets/Terminus.ttf", 36);//작은 안내문 폰트
      message = TTF_RenderText_Solid(font, "Choose the game mode", textColor); // space키는 시작 esc키는 종료
      message2 = TTF_RenderText_Solid(font3, "Single play", textColor);
      message3 = TTF_RenderText_Solid(font3, "Multi play", textColor);
      background = load_image("assets/background.png");  // 배경
			apply_surface(0, 0, background, screen, NULL);
      apply_surface((640 - message->w) / 2, 100, message, screen, NULL);
      apply_surface((640 - message2->w) / 2, 210, message2, screen, NULL);
      apply_surface((640 - message3->w) / 2, 300, message3, screen, NULL);
      apply_surface(170, selecty-20, arrow, screen, NULL);

			SDL_Flip(screen);

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{

				case SDLK_o:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          quit = true;
          if(selecty == 210)
            mode = 1;
          else if(selecty == 300)
            mode = 2;

          break;
        }
        case SDLK_KP8:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          if (selecty == 210)
          {}
          else
          {
            selecty -= 90;
          }
          break;
        }
        case SDLK_KP5:  // space 키가 눌리면 게임 배경 가져오고 게임 시작
        {
          if(selecty == 300)
          {}
          else
          {
            selecty += 90;
          }
          break;
        }

        case SDLK_ESCAPE:  // esc 키 누르면 종료
        {
          EXIT = 1;
          quit = true;
          break;
        }
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

void game_over()  // 사용자 죽었을 시 나타나는 게임오버 창
{
  font = TTF_OpenFont("assets/Terminus.ttf", 24);//작은 안내문 폰트
	bool quit = false;
  background = load_image("assets/background.png");
  message2 = TTF_RenderText_Solid(font2, "Game over", textColor2);
  apply_surface(0, 0, background, screen, NULL);
  message = TTF_RenderText_Solid(font, "Press space to restart, esc key to quit", textColor);
  apply_surface((640 - message->w) / 2, 280, message, screen, NULL);
  apply_surface((640 - message2->w) / 2, 100, message2, screen, NULL);
  SDL_Flip(screen);

	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE://esc 키가 눌리면 종료
        {
          quit = true;
          break;
        }
        case SDLK_SPACE:
        {
          Continue = 1;
          quit = true;
          break;
        }
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

void stage_clear()  // 나중에 bosscounter == 0 되면 stage clear 되도록 창 띄우기
{
	bool quit = false;

  message = TTF_RenderText_Solid(font, "Stage Clear!", textColor);
  background = load_image("assets/background.png");
  apply_surface(0, 0, background, screen, NULL);
  apply_surface((640 - message->w) / 2, 480/2 - message->h, message, screen, NULL);
  SDL_Flip(screen);

	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE://esc 키가 눌리면 종료
        {
          quit = true;
          break;
        }
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
}

void sprite_surface( SDL_Surface *screen, SDL_Rect tmp, SDL_Surface* surface, int w, int h, int step , int mode1)
{
	SDL_Rect rectDst, rectSrc;
  if(mode1 == 0)
  {
    rectDst = tmp;
    rectDst.x -= 10;
  }

  else if(mode1 == 1)
  {
    rectDst = tmp;
    rectDst.x += 60;
    rectDst.y += 18;
  }

  else if(mode1 == 2)
  {
    rectDst = tmp;
    rectDst.x += 110;
    rectDst.y += 32;
  }
  else if(mode1 == 3)
  {
    rectDst = tmp;
    rectDst.x += 160;
    rectDst.y += 18;
  }
  else if(mode1 == 4)
  {
    rectDst = tmp;
    rectDst.x += 210;
  }

  rectSrc.x = (step % w) * surface->w/w;      //분할된 이미지 선택
  rectSrc.y = (step / w) * surface->h/h;
  rectSrc.w = surface->w/w;                   //분할된 이미지 선택
  rectSrc.h = surface->h/h;
  SDL_BlitSurface(surface, &rectSrc, screen, &rectDst);
}
