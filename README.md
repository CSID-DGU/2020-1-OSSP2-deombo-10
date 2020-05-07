# 2020-1-OSSP2-deombo-10
************변경사항************
적들의 충돌 판정을 추가했습니다. 이제 적한테 닿으면 데미지를 받습니다. 사운드 안나오는 문제도 해결했습니다.
특수기 사운드 효과를 수정했습니다. 이제 특수기를 쓰면 스테이지 음악을 중지시키고 효과음만 나오게 만들었습니다.
보스 피격음과 보스 사망시 폭팔음을 추가했습니다.
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

