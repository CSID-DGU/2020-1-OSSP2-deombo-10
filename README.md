# 2020-1-OSSP2-deombo-10
************변경사항************
보스를 추가하였습니다. 이제 2000 / 8000 / 15000 주기로 보스가 생성됩니다.

********************************

Starwars

Space Shooting game (Developed by team "deombo")

* Description

    An enhanced version of the MSG project
    Original Open Source : https://github.com/CSID-DGU/2018-1-OSSP-MSG-7
    Written in C++
    
* * *
* How To Run

1. Install SDL library

    sudo apt-get install libsdl1.2-dev
    
    sudo apt-get install libsdl-image1.2-dev
    
    sudo apt-get install libsdl-ttf2.0-dev
    
    sudo apt-get install libsdl-mixer1.2-dev

2. Install g++

    sudo apt-get install g++

3. Pull or clone our github

    git clone https://github.com/CSID-DGU/2020-1-OSSP2-deombo-10.git

4. Type the things in "make" file and compile

    g++ -o main main.cpp helpers.h helpers.cpp AirPlane.cpp AirPlane.h define.h -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -std=c++14

5. Run the "main"

    ./main

* * *
* using some code from SDL_gfx

scale surface 함수에 대한 레퍼런스
http://www.sdltutorials.com/sdl-scale-surface

http://cse.csusb.edu/tongyu/courses/cs420/notes/sdl.php

https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface

obstacle.png source
The molten rock planet PNG was designed by 千图网, and originated from 千图网 and downloaded from pngtree.com.
https://kor.pngtree.com/freepng/cartoon-lava-rock-planet-is-a-commercial-element_4074202.html

