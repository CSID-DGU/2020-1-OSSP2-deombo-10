# 2020-1-OSSP2-deombo-10
************변경사항************
화면 밖으로 나갔을 시 데미지를 입고 초기 위치로 돌아오게 되는 기능을 추가했습니다.
임시로 쉴드 스프라이트를 사용하는 총알 업그레이드 아이템을 추가함 습득 시 3방향으로 총알이 발사됨
총알 스프라이트를 회전시켜 3방향 발사가 자연스럽게 이루어지도록 함 
********************************

Starwars

Space Shooting game (Developed by team "deombo")
Description

    An enhanced version of the MSG project
    Original Open Source : https://github.com/CSID-DGU/2018-1-OSSP-MSG-7
    Written in C++

How To Run

    Install SDL library

sudo apt-get install libsdl1.2-dev

sudo apt-get install libsdl-image1.2-dev

sudo apt-get install libsdl-ttf2.0-dev

sudo apt-get install libsdl-mixer1.2-dev


    Install g++


sudo apt-get install g++

    Pull or clone our github

git clone https://github.com/CSID-DGU/2020-1-OSSP2-deombo-10.git

    Type the things in "make" file and compile

g++ -o main main.cpp helpers.h helpers.cpp AirPlane.cpp AirPlane.h define.h -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -std=c++14

    Run the "main"

./main

using some code from SDL_gfx


scale surface 함수에 대한 레퍼런스
http://www.sdltutorials.com/sdl-scale-surface

http://cse.csusb.edu/tongyu/courses/cs420/notes/sdl.php

https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface
