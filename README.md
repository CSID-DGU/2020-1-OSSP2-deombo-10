# 2020-1-OSSP2-deombo-10
************변경사항************
버퍼를 하나 더 만들어서 이를 SDL_gfx를 이용하여 확대하고 이 확대시킨 Surface를 
screen에 그린 다음 flip하는 방식으로 화면의 크기에 따른 이미지 변화를 구현했습니다.
stage_clear 사운드를 추가하였고 발생하던 몇가지 오류를 수정하였습니다.
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
