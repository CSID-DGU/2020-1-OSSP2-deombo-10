# 2020-1-OSSP2-deombo-10
************변경사항*************
feature branch와 병합했습니다. 총 발사음, 아이템 습득 효과음,특수기를 사용할 때 효과음 추가했고 메뉴 음악이 안나오는 문제를 수정했고
몇가지 효과음을 변경했습니다. 다음에는 보스가 피격 당할 때 효과음을 추가해야하고 특수기 효과음이 배경음악에 묻혀서 안들리는 문제를 수정할 생각입니다.
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

